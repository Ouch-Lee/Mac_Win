# embedded_testing_log



  ```
  目前可以接收数据帧，但是，不知道电机的数据帧在哪里;
  看样子，我自己也没搞明白，can是怎么进行接收数据的
  下午具体看看can是怎么接收的吧，先把接收原理搞明白
  
  1-18 8点
  尝试替换学长的can.c文件
  先将之前的进行备份
  
  失败，连信号都没有
  成功——是之前底层参数没有设置好的原因
  9点，成功将学长can代码融合，替换掉正点原子自带代码，解决了bug，但是不知道具体原因是什么
  
  但是目前还是没有实现接收
  试一下用can分析仪发送能不能实现——成功接收分析仪发来的消息；因为之前是loop模式
  但是学长的代码无法实现接收——因为开启了CAN1中断？
  
  ```

  ```
  逐一排查哪个函数的问题：
  初始化：对了一遍，大概没问题吧
  HAL_CAN_MspInit() ： 没有问题
  滤波器——有重大嫌疑
  实锤了，滤波器里面的id；是他妈的141
  
  __ NIV ___
  同样的，不知道为什么开了中断就接收不到了
  试一下不开中断，电机能不能正常收指令，如果可以，那中断就不开——测试，没有中断电机正常工作
  
  ___ Filter___
  现在搞明白啦，你那个标识符不对的话，根本是识别不到你发过来的信号的；
  比如
  ```


```
1. 确定一下电机是绝对编码还是增量编码（也即上电为0还是0位永远不变）——真牛逼两个都行
2. 确定一下正反返回的速度是不是一样的——逆时针为正

```

4-24 :尝试将我这边读取的数据存储在一个数组里面后通过CAN发送到亦达的单片机

首先数据都可以直接存在CAN_sending_para这个1维数组中

```c
				CAN_sending_para[3] = motor_pitch_para[2];
				for (int i = 0; i < 5; i++) {
						printf("%f ", CAN_sending_para[i]);
				}
				printf("\n"); // 换行
```

也成功通过send_CAN_array(motorId_yaw);函数向目标地址发送了信息

接下来尝试在F1上实现CAN通讯，但是目前的问题是HAL_CAN_AddTxMessage(&hcan, &g_canx_txheader, msg, &TxMailbox) != HAL_OK



目前的问题是，单挑数据发送可以收到，但是数据多了，是不是有冲突的问题？

看一下同时发5个，是接收5个还是一个  = 》不是1也不是5，是4？？？

**尝试在发的时候加一个delay，可能发的太快了，接收方来不及接收**

既然不能在一个循环中收完，那我就尝试循环5次接收完(没用)

* 尝试在一帧中发5个double：不可能实现，因为一个double就占了8个字节；后面可以换成更小的数据类型
* 尝试打开中断：打开中断以后，连正常的接收都接收不了了（玩锤子；=》中断可以！
* 把double换成了float（不是重点），成功实现了数据的转码=》发送=》解码（存在一个问题就是id和数据偏移）



使用正点原子的历程成功实现了发送，再试一下接收

```C
		send_CAN_array(1);
		for ( i = 0; i < 8; i++)
            {
                canbuf[i] = cnt + i; /* 填充发送缓冲区 */
						}
            res = can_send_msg(0X12, canbuf, 8); /* ID = 0X12, 发送8个字节 */
						

            if (res)
            {
                printf("send failed. \r\n");
            }
            else
            {
                printf("already send \r\n");
            }
            								
		rxlen = can_receive_msg(0X141, canbuf); /* CAN ID = 0X12, 接收数据查询 */

        if (rxlen) /* 接收到有数据 */
        {

            printf("\r\n already receive the msg \r\n");
            for (i = 0; i < rxlen; i++)
            {
								usart_show_xnum(canbuf[i], rxlen);
            }
        }
```



ok！发送和接收都能成功实现，接下来尝试一下连接两块单片机

成功对接单片机；接下来就是将数据整理好发去（实际上已经整理好了，不过是一组发5个



4-28：

现在存在的问题是，ID和数组存在错位的问题

* 尝试一：发送单条数据，看会不会错位：单条数据不错位。。。

```
//	uint16_t TH = 65535; //反转阈值用来将获取到的参数修正为负数
//  uint16_t iq;		//力矩电流
//  uint16_t speed; //速度
//	int32_t Speed;
//	uint16_t state[3]; 
	

//		iq =(uint16_t)(((uint8_t)rxbuf[3]<<8)
//									|((uint8_t)rxbuf[2]<<0));
//		if(iq > 60000) {
//			IQ = -(TH-iq);
//			printf("{motorTnfo}%d",IQ);
//			printf(",");
//		}else{
//			IQ = iq;
//			printf("{motorTnfo}%d",iq);
//			printf(",");
//		}

//	//	printf("%d",iq);
//	//	printf(",");
//		
//		speed =(uint16_t)(((uint8_t)rxbuf[5]<<8)
//										 |((uint8_t)rxbuf[4]<<0));
//		if(speed > 60000) {
//			Speed = -(TH-speed);
//			printf("%d",Speed);
//			printf("\n");
//		}else{
//			printf("%d",speed);
//			printf("\n");
//		}
```



## 6-3：购买完电机

* 首先给所有的标ID：

  | ID   | 位置     | 备注 |
  | ---- | -------- | ---- |
  | 1    | 左；纵   |      |
  | 2    | 左；横   |      |
  | 3    | 左；俯仰 |      |
  | 4    | 左；偏航 |      |
  | 5    | 右；纵   |      |
  | 6    | 右；横   |      |
  | 7    | 右；俯仰 |      |
  | 8    | 右；偏航 |      |

  为了测试Id是否成功设置，使用如下代码检查：

  可以给一个很小的力矩值，也可以开\关交替（选择后者）

  ```c#
  		while(1)
  		{
  			
  			for(int test_id = 0; test_id < 8; test_id++)
  			{
  				motor_stop(motor_IDs[test_id]);
  				HAL_Delay(3000); // 观察现象
  			}
  //			if (motor_state == 1)
  //			{
  //				motor_close(motor_IDs[test_id]);
  //					motor_state = 0;
  //					HAL_Delay(3000); // 观察现象
  //			}
  //			else if(motor_state == 0) {
  //				motor_start(motor_IDs[test_id]);
  //				motor_state = 1;
  //				HAL_Delay(3000);
  //			}
  		}			
  ```
  
  成功设置了ID，并验证了8个通道的可行性；中间遇到了一个问题，就是连接在总线上数目超过两个时就会出现接收不到信号的问题，后面了解到只需要打开起始端和终点端的电阻即可。
  
* 接下来试一下读取8个电机的角度；

  * 不能使用start函数，会卡死，毒瘤函数，所以就不要先断电然后上电的步骤了

  * 初始位置终于搞定了，对于纵向的电机，需要注意，由于初始多圈角度是取决于单圈角度，满足

    theta_mul = theta_sig , theta_sig < 180

    theta_mul = theta_sig - 360, theta_sig >180

    因此，要养成用完以后拉回最后面的习惯



## 6-6 将角度发到上位机

目前我有一个长度为12的float的数组，我要将其用 2 x 12个bytes 的数据表示：

对于每个数，首先我需要将其转化为整数（四舍五入），然后使用两个字节存储这个整数，为了区分正负号，使用最高位作为标识符

12个角度对应的范围：

| id   | range   |
| ---- | ------- |
| 1    | [0,500] |
| 2    | [-]     |
| 3    |         |
| 4    |         |
| 5    |         |
| 6    |         |
| 7    |         |
| 8    |         |
| 9    |         |
| 10   |         |
| 11   |         |
| 12   |         |



