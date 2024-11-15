/**
  ******************************************************************************
  * @FileName
  * @Description ���ڻ�ȡ��������������ݣ���ʵ����������Ƭ��/PCֱ�����ݽ���
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
float CAN_sending_para[12];  // �洢Ҫ�����Ӷ˵�12���Ƕ� 0-3��Ӧ����4�������4,5Ϊ�����������룻6-11��Ӧ����
float received_data[8]; // store message from motor
float motor_encoder_angles[10]; // ��Ϊ����ӳ�䲻��Ҫ�õ�rolling�ؽڣ��������ֻ��10��������û�й�����rolling�ؽ�
uint8_t output[24];   // ��������λ������24λ����

/* ��ȡ10����ȡ����ĹؽڽǶ� */
void get_all_motor_angles(void)
{
					// �������forѭ������ȡ��8������ĽǶȲ�����received_data[8]��
				for(int i=0; i<8; i++){
					read_multi_angle(motor_IDs[i]);
//					HAL_Delay(5); // �ȿ������͵�CAN�����Ƿ���ȷ=>ͨ��
				}
				// ��Ҫ����һ����ʼƫ��  TODO;
				float motor_anlge_offset[8];
				for(int i = 0; i < 8; i++) {
						motor_anlge_offset[i] = received_data[i] - offset_angle[i]; // ִ��A[i] - B[i]�Ĳ���
					}
				// ��motor_anlge_offset��ֵ��sending_para��
				for (int i = 0; i < 4; ++i) {
					motor_encoder_angles[i] = motor_anlge_offset[i];
				}
				for (int i = 4, j = 5; i < 8; ++i, ++j) {
					 motor_encoder_angles[j] = motor_anlge_offset[i];
				}
				// ��encoder_angle����ĵ�3�͵�4��Ԫ�ظ�ֵ��CAN_sending_para�ĵ�4
				motor_encoder_angles[4] = encoder_angle[0]; //  roll_1 ������
				// ��encoder_angle����ĵ�5�͵�6��Ԫ�ظ�ֵ��CAN_sending_para�ĵ�10�͵�11��Ԫ��
				motor_encoder_angles[9] = encoder_angle[2];  // PA1���������Ըĳ�PA2

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
		// ��motor_encoder_angles��ֵ��CAN_sending_para
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
* ���ã����յ���6֡CAN���ݽ���Ϊԭ����float����
* input : CAN_received_data���յ���CAN���ݣ�output_floats�����ڴ���������
* ��Ҫ��main�ж���һ���ֲ�������Ϊ���δ��� output_floats
* Ŀǰ��Ҫ�Ĳ����� output_floats[1],output_floats[2],output_floats[3](\alpha,\beta,\gama)
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
    // ��Ϊÿ��floatֵ��Ҫ2���ֽ����洢�������ܹ���Ҫ24���ֽ�
    for (int i = 0; i < 12; ++i) {
        // �������뵽���������
//				printf("\r\n");
        int rounded_value = (int)round(CAN_sending_para[i]);
//			printf("%d : %d  ", i, rounded_value);
				int rounded_value_abs = abs(rounded_value);
        // ������ת��Ϊ�����ֽ�
        // ���������ִ洢�ڵ�һ���ֽ�
        output[2 * i] = (uint8_t)(rounded_value_abs >> 8); // �洢��8λ
        // ���������ֵ�ʣ�ಿ�ִ洢�ڵڶ����ֽ�
        output[2 * i + 1] = (uint8_t)(rounded_value_abs & 0xFF); // �洢��8λ

        // ��������Ǹ����������λ����Ϊ1
        if (rounded_value < 0) {
            output[2 * i] |= 0x80; // �������λ
        }
    }
}

