/**
  ******************************************************************************
  * @FileName
  * @Description 用于获取电机、编码器数据，并实现与其它单片机/PC直接数据交换
  * @author Neo
  * @note
  ******************************************************************************
  *
  * Copyright (c) 2024 Team HUST
  * All rights reserved.
  *
  ******************************************************************************
**/

#include "./SYSTEM/sys/sys.h"
#include "./Inc/DataTransmission.h"
#include "./BSP/CAN/can.h"
#include "./SYSTEM/usart/usart.h"
#include <math.h>
#include "./BSP/CTRL/motor_ctrl.h"
#include "./BSP/MAPPING/mapping.h"
#include <string.h>

/***	SPECIFIC INIT CONFIGURATION	***/
float CAN_sending_para[12];  // 存储要发给从端的12个角度 0-3对应左手4个电机，4,5为左手两个编码；6-11对应右手
float received_data[8]; // store message from motor
float motor_encoder_angles[10]; // 因为后续映射不需要用到rolling关节，因此这里只用10个数，而没有管两个rolling关节
uint8_t output[24];   // 用于向上位机发送24位数据

/* 获取10个夹取以外的关节角度 */
void get_all_motor_angles(void)
{
					// 经过这个for循环，获取了8个电机的角度并存在received_data[8]中
				for(int i=0; i<8; i++){
					read_multi_angle(motor_IDs[i]);
//					HAL_Delay(5); // 先看看发送的CAN数据是否正确=>通过
				}
				// 需要处理一个初始偏置  TODO;
				float motor_anlge_offset[8];
				for(int i = 0; i < 8; i++) {
						motor_anlge_offset[i] = received_data[i] - offset_angle[i]; // 执行A[i] - B[i]的操作
					}
				// 将motor_anlge_offset赋值到sending_para中
				for (int i = 0; i < 4; ++i) {
					motor_encoder_angles[i] = motor_anlge_offset[i];
				}
				for (int i = 4, j = 5; i < 8; ++i, ++j) {
					 motor_encoder_angles[j] = motor_anlge_offset[i];
				}
				// 将encoder_angle数组的第3和第4个元素赋值给CAN_sending_para的第4
				motor_encoder_angles[4] = encoder_angle[0]; //  roll_1 编码器
				// 将encoder_angle数组的第5和第6个元素赋值给CAN_sending_para的第10和第11个元素
				motor_encoder_angles[9] = encoder_angle[2];  // PA1犯病，所以改成PA2

}


void send_CAN_array_0(float input_para[10]) {
		uint8_t data_to_send[8]; // Buffer for two floats (8 bytes)
    
    for (int i = 0; i < 10; i += 2) {
        uint32_t can_id = MASTER_PC_ID + i / 2; // Construct unique CAN ID

        // Copy the first float
        memcpy(data_to_send, &input_para[i], sizeof(float));
        // Copy the second float
        memcpy(data_to_send + 4, &input_para[i + 1], sizeof(float));

        // Call can_send_msg to send the data
        if (can_send_msg(can_id, data_to_send, sizeof(data_to_send)) != 0) {
            // Handle failure to send
            printf("Failed to send CAN message with ID %x\n", can_id);
            break;
        }
        // Introduce a delay between CAN messages
        HAL_Delay(1); // Uncomment this line in actual hardware code
    }
}

void send_CAN_array(float this_CAN_sending_para[12], float input_para[10]) {
		// 将motor_encoder_angles赋值到CAN_sending_para
		for (int i = 0; i < 5; ++i) {
				this_CAN_sending_para[i] = input_para[i];
		}
		for (int i = 5, j = 6; i < 10; ++i, ++j) {
				this_CAN_sending_para[j] = input_para[i];
		}
		this_CAN_sending_para[5] = encoder_angle[4];
		this_CAN_sending_para[11] = encoder_angle[5];
		uint8_t data_to_send[8]; // Buffer for two floats (8 bytes)
    
    for (int i = 0; i < 12; i += 2) {
        uint32_t can_id = MASTER_SLAVE_ID + i / 2; // Construct unique CAN ID

        // Copy the first float
        memcpy(data_to_send, &this_CAN_sending_para[i], sizeof(float));
        // Copy the second float
        memcpy(data_to_send + 4, &this_CAN_sending_para[i + 1], sizeof(float));

        // Call can_send_msg to send the data
        if (can_send_msg(can_id, data_to_send, sizeof(data_to_send)) != 0) {
            // Handle failure to send
            printf("Failed to send CAN message with ID %x\n", can_id);
            break;
        }
        // Introduce a delay between CAN messages
        HAL_Delay(2); // Uncomment this line in actual hardware code
    }

}

/**
* 作用：将收到的6帧CAN数据解码为原来的float数组
* input : CAN_received_data：收到的CAN数据，output_floats：用于存解码的数据
* 需要在main中定义一个局部变量作为传参传入 output_floats
* 目前需要的参数是 output_floats[1],output_floats[2],output_floats[3](\alpha,\beta,\gama)
* output: void
*/

void receive_CAN_array(uint8_t CAN_received_data[6][8], float this_output_floats[12]) {
    // Buffer for a single float
    float temp_float;
    
    // Process each CAN data frame
    for (int i = 0; i < 6; ++i) {
        // Extract the first float from the current frame
        memcpy(&temp_float, CAN_received_data[i], sizeof(float));
        this_output_floats[i * 2] = temp_float;
        
        // Extract the second float from the current frame
        memcpy(&temp_float, CAN_received_data[i] + 4, sizeof(float));
        this_output_floats[i * 2 + 1] = temp_float;
    }
}


void print_sent_data(float *data, int size) {
		printf("Data: ");
    for (int i = 0; i < size; ++i) {
        printf("%f ", data[i]);
    }
		printf(" . \n");
		
}


void float_2_uint16(float *CAN_sending_para, uint8_t *output) {
    // 因为每个float值需要2个字节来存储，所以总共需要24个字节
    for (int i = 0; i < 12; ++i) {
        // 四舍五入到最近的整数
//				printf("\r\n");
        int rounded_value = (int)round(CAN_sending_para[i]);
//			printf("%d : %d  ", i, rounded_value);
				int rounded_value_abs = abs(rounded_value);
        // 将整数转换为两个字节
        // 将整数部分存储在第一个字节
        output[2 * i] = (uint8_t)(rounded_value_abs >> 8); // 存储高8位
        // 将整数部分的剩余部分存储在第二个字节
        output[2 * i + 1] = (uint8_t)(rounded_value_abs & 0xFF); // 存储低8位

        // 如果整数是负数，将最高位设置为1
        if (rounded_value < 0) {
            output[2 * i] |= 0x80; // 设置最高位
        }
    }
}

