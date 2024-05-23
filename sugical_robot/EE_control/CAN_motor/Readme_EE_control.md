# Readme_EE_control

这部分代码用于主端下位机STM32的控制；代码主要的目标是读取电机状态，控制电机运动，使用DMA读取多个传感器的信息



控制逻辑如下：

预动作：先关闭后开启（**搞定**）

上电后电机回零到初始位置[a1, 0, 0, 0] （需要写位置控制代码）**已经实现了**

是否需要检查一下电机是否正常工作？



用手捏pincher两次，作为开始控制的信号；当检测到gripper端编码器两次大幅度运动时（写检测和判断代码）

先实现DMA，然后写一下这个判断逻辑

* 成功实现DMA功能，现在将其移至到整体代码中-成功整合，遇到报错link 找不到函数的问题，因为没有添加对应=》成功整合代码；
* 



开始工作，进入while循环 ；首先使用50Hz的频率采样读取电机角度，编码器角度

* 电机角度读取的原理是CAN的中断，向电机发送命令帧后会自动返回回复帧，并通过中断获取；所以重点是处理函数：在处理函数里面根据第一帧的数据进入不同函数处理：
  * 多圈角度：0x92
  * 单圈角度：0x94
  * 编码器一堆字节：0x90
  * 电机状态：0x9C
* 将读取的12个角度编码，通过CAN发送到从端单片机（这里写好了，但是需要整理）
  * 将8+4存在同一个数组中，并使用CAN_send_函数发送（已经写好了，测一下延迟）





## 电机控制

需要借助电机实现的功能如下：

```C
float theta_0[2] = {0.0, 0.0}; // 假设两个编码器的初始角度都为 0 度
float theta_1[2] = {45.0, 55.0}; // 假设两个编码器的目标角度分别为 45 度和 55 度

// 编码器状态枚举
typedef enum {
    AT_THETA_0,
    MOVING_TO_THETA_1,
    AT_THETA_1,
    RETURNING_TO_THETA_0
} EncoderState;

// 用于记录每个编码器达到theta_1的次数
int theta_1_reached_count[2] = {0, 0};

// 检测编码器是否到达目标角度，考虑误差范围
bool is_at_theta(float current, float target, float error_range) {
    return fabs(current - target) < error_range;
}

int main() {
    printf("Starting encoder movement detection.\n");

    // 初始化编码器状态
    EncoderState state[2] = {AT_THETA_0, AT_THETA_0};

    // 无限循环，直到两个编码器都达到theta_1两次
    while (true) {
        for (int encoder_id = 0; encoder_id < 2; encoder_id++) {
            float current_angle = read_encoder_angle(encoder_id);

            switch (state[encoder_id]) {
                case AT_THETA_0:
                    if (current_angle > theta_0[encoder_id] + (theta_1[encoder_id] - theta_0[encoder_id]) / 2) {
                        state[encoder_id] = MOVING_TO_THETA_1;
                    }
                    break;
                case MOVING_TO_THETA_1:
                    if (is_at_theta(current_angle, theta_1[encoder_id], 0.1)) { // 假设误差范围为0.1度
                        state[encoder_id] = AT_THETA_1;
                        theta_1_reached_count[encoder_id]++;
                    }
                    break;
                case AT_THETA_1:
                    if (current_angle < theta_1[encoder_id] - (theta_1[encoder_id] - theta_0[encoder_id]) / 2) {
                        state[encoder_id] = RETURNING_TO_THETA_0;
                    }
                    break;
                case RETURNING_TO_THETA_0:
                    if (is_at_theta(current_angle, theta_0[encoder_id], 0.1)) {
                        state[encoder_id] = AT_THETA_0;
                    }
                    break;
            }

            // 检查两个编码器是否都已达到theta_1两次
            if (theta_1_reached_count[0] >= 2 && theta_1_reached_count[1] >= 2) {
                printf("Both encoders reached theta_1 twice. Exiting loop.\n");
                return 0; // 正常退出程序
            }
        }
    }
}
```

```C
    // 电机数据解码
    if (rxbuf[0] == 0xA1) {
        int16_t tau = (int16_t)(rxbuf[2] | (rxbuf[3] << 8));
        int16_t speed = (int16_t)(rxbuf[4] | (rxbuf[5] << 8));
        uint16_t position = (uint16_t)(rxbuf[6] | (rxbuf[7] << 8));

        // 根据接收到的ID更新电机角度值
        if (id > DEVICE_STD_ID && id <= (DEVICE_STD_ID + 5)) {
            // 更新received_data数组中的角度值
						switch (id) {
								case 0x141: {
										received_data[id - DEVICE_STD_ID - 1] = (double)position / 65535.0 * 360.0 - 185;
										break;
								}
								case 0x142: {
										received_data[id - DEVICE_STD_ID - 1] = (double)position / 65535.0 * 360.0 - 322;
										break;
								}
								// 可以根据需要添加更多的case语句
								default:
										// 可以在这里处理未匹配到ID的情况
										break;
		}
            
        } else {
            printf("Received message with unexpected ID: 0x%03X\n", id);
        }
    } else {
        printf("Received message with wrong header byte: 0x%02X\n", rxbuf[0]);
    }
```

使用读取多圈角度的命令，出现bug：当角度为负数时不是负数而是

* 该问题已经得到解决，但是原理我并不懂（后面需要继续搞明白这一块





