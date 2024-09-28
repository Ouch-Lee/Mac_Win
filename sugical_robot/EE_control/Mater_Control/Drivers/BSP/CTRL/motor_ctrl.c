#include "./SYSTEM/sys/sys.h"
#include "./BSP/CAN/can.h"
#include "./BSP/CTRL/motor_ctrl.h"
#include "./BSP/ADC/adc.h"
#include "./SYSTEM/tim/tim.h"
#include <stdbool.h>
#include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "./BSP/CAN/can.h"


/***	CONSTANT VALUE	***/


/***	TYPE DEFINE	***/



/***	SPECIFIC INIT CONFIGURATION	***/
uint8_t motor_IDs[8] = {1, 2, 3, 4, 5, 6, 7, 8};
float init_angle[8] = {108.00f, 168.00f, -95.00f, 10.00f, 100.00f, 130.00f, 180.00f, 60.00f} ; // change the para to change init angle {160.00f, 0.00f, -110.00f, -115.00f, 0.00f, 20.00f, 0.00f, 186.00f}
float offset_angle[8] = {0.0f, -173.0f, -90.00f, 10.00f, -25.0f, 77.0f, 0.00f, 60.00f};
// about encoder
float encoder_angle[6];  // 实际需要的角度是第2 3 4 5个元素
// encoder + adc 相关参数
extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0, 未完成; 1, 已完成 */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */
uint16_t adcx;

/***	EXTERNAL VARIABLES	***/


/***	APIs	***/
void motor_close(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x80;	
		can_send_msg(motor_address + DEVICE_STD_ID, msg_v,8);
}

void motor_stop(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x81;	
		can_send_msg(motor_address + DEVICE_STD_ID, msg_v,8);
}


void motor_start(uint8_t motor_address)
{
		uint8_t msg_v2[8] = {0};
		msg_v2[0] = 0x88;	
		can_send_msg(motor_address + DEVICE_STD_ID, msg_v2,8);
}	


void motor_torque_control(uint8_t motor_address, double iqValue)
{
		uint16_t IQ = 0;	//·¢ËÍ¸øµç»úµÄ²ÎÊý
		if (iqValue < 0) {
				IQ = 65536 - (uint16_t)(-iqValue);
		} else {
				IQ = (uint16_t)iqValue;
		}
	
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0xA1;	/* ¹¦ÄÜÂë */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = *(uint8_t *)(&IQ) ;	/* µÍ×Ö½Ú */
		msg_v[5] = *((uint8_t *)&IQ + 1);	/*¸ß×Ö½Ú*/
		msg_v[6] = 0x00;
		msg_v[7] = 0x00;
		
    can_send_msg(motor_address + DEVICE_STD_ID, msg_v,8);
}


void motor_speed_control(uint8_t motor_address, double speedValue)
{
	uint16_t speed = 0;
	if (speedValue < 0) {
				speed = 65536 - (uint16_t)(-speedValue);
		} else {
				speed = (uint16_t)speedValue;
		}
		
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0xA2;	/* ¹¦ÄÜÂë */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = *( uint8_t *)&(speed );	/* µÍ×Ö½Ú */
		msg_v[5] = *((uint8_t *)(&speed) + 1);	/*¸ß×Ö½Ú*/
		msg_v[6] = *((uint8_t *)(&speed) + 2);
		msg_v[7] = *((uint8_t *)(&speed) + 3);
		
    can_send_msg(motor_address,msg_v,8);
}

/**********************************************************
主机发送该命令以控制电机的位置（多圈角度）
1. 控制值 angleControl 为 int32_t 类型，对应实际位置为 0.01degree/LSB，即 36000 代表 360°，
电机转动方向由目标位置和当前位置的差值决定。
2. 控制值 maxSpeed 限制了电机转动的最大速度，为 uint16_t 类型，对应实际转速 1dps/LSB，
即 360 代表 360dps。
**********************************************************/	
void motor_multi_angl_control(uint8_t motor_address, int32_t angleControl, uint16_t maxSpeed)
{
		
		uint8_t command[8];
    
    // 命令字节
    command[0] = 0xA4;
    // NULL 字节
    command[1] = 0x00;
    // 速度限制低字节和高字节
    command[2] = *(uint8_t *)&maxSpeed;
    command[3] = *(uint8_t *)((uint8_t *)&maxSpeed + 1);
    // 位置控制的低字节到高字节
    command[4] = *(uint8_t *)&angleControl;
    command[5] = *(uint8_t *)((uint8_t *)&angleControl + 1);
    command[6] = *(uint8_t *)((uint8_t *)&angleControl + 2);
    command[7] = *(uint8_t *)((uint8_t *)&angleControl + 3);
    can_send_msg(motor_address + DEVICE_STD_ID,command,8);
}

void motor_pause(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0};
		msg_v[0] = 0x81;	/* ¹¦ÄÜÂë */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
		
    can_send_msg(motor_address,msg_v,8);
}



//}
void read_motor_Accelerate(uint8_t motor_address)
{

		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x33;	/* ÃüÁî×Ö½Ú */
		msg_v[1] = 0x00;
		msg_v[2] = 0x00;	
		msg_v[3] = 0x00;	
		msg_v[4] = 0x00;	
		msg_v[5] = 0x00;	
		msg_v[6] = 0x00;	
		msg_v[7] = 0x00;	
    can_send_msg(motor_address,msg_v,8);	
}

/**********************************************************
 these functions are used to read the params about motor

**********************************************************/	
void read_multi_angle(uint8_t motor_address)
{
		uint8_t msg_v[8] = {0}; 
		msg_v[0] = 0x92;
		can_send_msg(motor_address + DEVICE_STD_ID, msg_v, 8);	
}

void read_motor_State2(uint8_t motor_address, double *state)
{
/**********************************************************
		DATA[0] ÃüÁî×Ö½Ú 0x9C 
		DATA[1] = *(uint8_t *)(&temperature) 
		DATA[2] = *(uint8_t *)(&iq) 
		DATA[3] = *((uint8_t *)(&iq)+1)  
		DATA[4] = *(uint8_t *)(&speed) 
		DATA[5] = *((uint8_t *)(&speed)+1)
		DATA[6] = *(uint8_t *)(&encoder) 
		DATA[7] = *((uint8_t *)(&encoder)+1) 
**********************************************************/	
		uint8_t msg_v[8]; 
    uint8_t rxlen = can_receive_msg(motor_address + DEVICE_STD_ID, msg_v);
        if (rxlen)
        {
//						printf("\r\n already receive the msg \r\n");

						int16_t tau = (int16_t)(msg_v[2] | (msg_v[3] << 8)); //iq
						int16_t speed  = (int16_t)(msg_v[4] | (msg_v[5] << 8)); // speed
						uint16_t position = (uint16_t)(msg_v[6] | (msg_v[7] << 8));  //encoder = position
						state[0] = (double) tau *16.5 / 2048;
						state[1] =  (double) speed * 360 / (1 << 16);
						state[2] = (double) position / 65535.0 * 360.0;
//									printf("State array for motor %d in motor_ctrl: [tau: %f, v: %f, P; %f]\n", motor_address,
//           state[0], state[1], state[2]);
						printf("%.2f ", state[2]);
				}
			
 }

/**
 * @brief       初始化主端电机,并运行到固定位置
 *   @note      
 * @param       void
 * @retval      void
 */
void prepare_working(float *init_angle)
{	
	int32_t init_angle_32[8];
	for(int q=0; q<8;q++){
			init_angle_32[q] = (int32_t)(init_angle[q] * 100.0f);
			motor_multi_angl_control(motor_IDs[q], init_angle_32[q], 100);
			HAL_Delay(20);
	}
}



/**********************************************************
 these functions are used to read the params about encoders
**********************************************************/	

/**
 * @brief       调试过程中用于显示编码器角度
 *   @note      
 * @param       void
 * @retval      void
 */
void display_encoder_angle() {
    int i;
    printf("Encoder Angles:\n");
    for (i = 0; i < 6; ++i) {
        printf("Channel %d: %.2f degrees\n", i, encoder_angle[i]);
    }
}

/**
 * @brief       最新版的模拟量编码器更新函数，用于更新并储存最新的角度
 *   @note      
 * @param       具体引脚分布见<STM32 IO表.md>
 * @retval      void
 */
void update_encoder_angle() {
    if (g_adc_dma_sta == 1) {
        int j, i;
        int sum;
        float adcx, temp;
        for (j = 0; j < 6; j++) {  // 遍历个通道
            sum = 0; /* 清零 */
            for (i = 0; i < ADC_DMA_BUF_SIZE / 6; i++) {  // 每个通道采集了10次数据,进行10次累加
                sum += g_adc_dma_buf[( 6 * i) + j];  /* 相同通道的转换数据累加 */
            }
            adcx = sum / (ADC_DMA_BUF_SIZE / 6);    /* 取平均值 */
            temp = (adcx / 4096) * 360;      /* 获取计算后的带小数的实际电压值 */
            encoder_angle[j] = temp;  // 更新数组元素
        }

        g_adc_dma_sta = 0;  /* 清除DMA采集完成状态标志 */
        adc_nch_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动下一次ADC DMA多通道采集 */
    }
}

/**
 * @brief       通过检测操纵者手指两次闭合动作检测是否准备就绪
 *   @note      
 * @param       void
 * @retval      void
 */
void ready_work()
{
    uint8_t trigger_count_arr[2] = {0, 0};  // 记录到达最大量程的次数
    float range[2] = {30.00, 30.00}; // pincher 最大的运动角度行程
    float theta_0[2] = {0.00, 0.00}; // 初始位置对应凹槽对准电线
    update_encoder_angle();
    theta_0[0] = encoder_angle[4];
    theta_0[1] = encoder_angle[5];
    float theta_1[2];
    theta_1[0] = theta_0[0] - range[0];
    theta_1[1] = theta_0[1] - range[1];
    EncoderState state[2] = {AT_THETA_0, AT_THETA_0};

    printf("Starting encoder movement detection.\n");
    printf("\r\n init angles for 4 encoders: %f, %f, %f, %f", encoder_angle[0], encoder_angle[1], encoder_angle[4], encoder_angle[5]);

    while (1) {
        update_encoder_angle();  // 用于更新两个编码器的角度
        for (int encoder_id = 0; encoder_id < 2; encoder_id++) {
            float current_angle = encoder_angle[encoder_id + 4];
            // 通过四个状态切换，判断编码器是否两次触发
            switch(state[encoder_id]) {
                case AT_THETA_0:
                    if (current_angle < theta_0[encoder_id] - (theta_0[encoder_id] - theta_1[encoder_id]) / 2) {
                        state[encoder_id] = MOVING_TO_THETA_1;
                    }
                    break;
                case MOVING_TO_THETA_1:
                    if (is_at_theta(current_angle, theta_1[encoder_id], 4)) { // 假设误差范围为4度
                        state[encoder_id] = AT_THETA_1;
                        trigger_count_arr[encoder_id]++;
                    }
                    break;
                case AT_THETA_1:
                    if (current_angle > theta_1[encoder_id] + (theta_0[encoder_id] - theta_1[encoder_id]) / 2) {
                        state[encoder_id] = MOVING_TO_THETA_0; // 逆向转动，从THETA_1向THETA_0移动
                    }
                    break;
                case MOVING_TO_THETA_0:
                    if (is_at_theta(current_angle, theta_0[encoder_id], 4)) {
                        state[encoder_id] = AT_THETA_0;
                    }
                    break;
            }
        }
        // 检查两个编码器是否都已达到theta_1两次
        if (trigger_count_arr[0] >= 2 && trigger_count_arr[1] >= 2) {
            // 同时将8个电机都切换为自由模式
            for (int i = 0; i < 8; i++) {
                motor_torque_control(motor_IDs[i], 0);
                HAL_Delay(50);
            }
            break;
        }
    }
}

uint8_t is_at_theta(float current, float target, float error_range) {
    return fabs(current - target) < error_range ? TRUE : FALSE;
}

uint8_t simu_spring_damping(uint8_t K, uint8_t C, uint8_t p, uint8_t v)
{
	uint8_t F_out = -(K * p + C * v);
	return F_out;
}


