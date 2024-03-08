# motor testing log

### 2024_3_2

* 将读取的数据传入到motor_para数组中

  ```c
  			cnt++;
  			test_param_tran(cnt, motor_para);
  			printf("State array: [t: %u, tau: %u, v: %u, P; %u]\n", 
             motor_para[0], motor_para[1], motor_para[2], motor_para[3]);
  ```

  通过验证，该函数可以将motor_ctrl中读取电机状态的函数传递到main函数中

  目前已经可以读取电机数据了

* 使用很小的力矩，读取编码器的数据P，并找到P和角度之间的关系

  读取的四个数据，前三个都没有问题，感觉位置有很大问题

  1622550009861 State array in motor_ctrl: [t: 25, tau: 5, v: 0, P; 98]

  1622570002462 State array in motor_ctrl: [t: 25, tau: 7, v: 0, P; 24]

  162251004019862State array in motor_ctrl: [t: 25, tau: 10, v: 4, P; 198]

  编码器虽然精度不太行，但是至少逻辑没问题

  因此**解码的函数**有很大问题

* 







### tmp_code

```
//				printf("\r\n read to use USART to test CAN \r\n");
//			HAL_CAN_RxFifo0MsgPendingCallback(&g_canx_handler);
//			uint8_t rx_data_length = can_receive_msg(1, rx_buffer); /* recieve 88 00 00  */
////					
//					if (rx_data_length != 0)
//					{
//						printf("\r\n already receive the msg \r\n");
//						for (i = 0; i < rx_data_length; i++)
//            {
//								usart_show_xnum(rx_buffer[i], rx_data_length);
//            }
////						uint8_t command_byte = rx_buffer[0];
////						if (command_byte == 0xA1)
////            {
////                uint8_t temperature = rx_buffer[1];
////                int16_t iq = rx_buffer[2] + (rx_buffer[3] << 8) ;
////                int16_t speed = rx_buffer[4] + (rx_buffer[5] << 8);
////                uint16_t encoder = rx_buffer[6] + (rx_buffer[7] << 8);
////								 printf("Temperature: %d C, IQ: %d, Speed: %d dps, Encoder: %u\n",
////                       temperature, iq, speed, encoder);
////								
////                // ????? motor_temperature, motor_iq, motor_speed, encoder_position ????????
////            }
//					}
			
//        key = key_scan(0);

//        if (key == KEY0_PRES)           /* KEY0°´ÏÂ,·¢ËÍÒ»´ÎÊý¾Ý */
//        {
//						printf("\r\n torque1 \r\n");
//						
//					
//            start_res = can_send_msg(motorId, torque_control, 8);    /* ID = 0x12, ·¢ËÍ8¸ö×Ö½Ú */
//					
//					// recieve the data from motor 
//						uint8_t rx_data_length = can_receive_msg(motorId, rx_buffer); /* recieve 88 00 00  */
//					
//					if (rx_data_length != 0)
//					{
//						uint8_t command_byte = rx_buffer[0];
//						if (command_byte == 0xA1)
//            {
//                uint8_t temperature = rx_buffer[1];
//                int16_t iq = rx_buffer[2] + (rx_buffer[3] << 8) ;
//                int16_t speed = rx_buffer[4] + (rx_buffer[5] << 8);
//                uint16_t encoder = rx_buffer[6] + (rx_buffer[7] << 8);
//								 printf("Temperature: %d C, IQ: %d, Speed: %d dps, Encoder: %u\n",
//                       temperature, iq, speed, encoder);
//								
//                // ????? motor_temperature, motor_iq, motor_speed, encoder_position ????????
//            }
//					}
//            if (start_res)
//            {
////                lcd_show_string(30 + 80, 170, 200, 16, 16, "Failed", BLUE); /* ÌáÊ¾·¢ËÍÊ§°Ü */
//							 usart_show_string("Faild");
//							
//            }
//            else
//            {
////                lcd_show_string(30 + 80, 170, 200, 16, 16, "OK    ", BLUE); /* ÌáÊ¾·¢ËÍ³É¹¦ */
//							usart_show_string("OK");
//            }
//        }
//        else if (key == WKUP_PRES)      /* WK_UP°´ÏÂ, ¸Ä±äCANµÄ¹¤×÷Ä£Ê½ */
//        {
//            mode = 0;
//            /* CAN³õÊ¼»¯, ÆÕÍ¨(0)/»Ø»·(1)Ä£Ê½, ²¨ÌØÂÊ500Kbps */
//            if (mode == 0)  /* ÆÕÍ¨Ä£Ê½, ÐèÒª2¸ö¿ª·¢°å */
//            {
//							printf("\r\n start motor \r\n");
//							start_res = can_send_msg(motorId, start_motor, 8);
//							start_res = can_send_msg(motorId, start_motor, 8);
//							show_res(start_res);							
//            }
//            else            /* »Ø»·Ä£Ê½,Ò»¸ö¿ª·¢°å¾Í¿ÉÒÔ²âÊÔÁË. */
//            {
//							printf("\r\n close motor \r\n");
//							stop_res = can_send_msg(motorId, stop_motor, 8);
//							show_res(stop_res);
//            }
//        }
//				else if (key == KEY1_PRES)
//				{
//					printf("\r\n stop motor \r\n");
//					stop_res = can_send_msg(motorId, stop_motor, 8);
//					stop_res = can_send_msg(motorId, stop_motor, 8);
//					show_res(torque_res);
//				}
//				else if (key == KEY2_PRES)
//				{
//					printf("\r\n close motor \r\n");
//					torque_res = can_send_msg(motorId, close_motor, 8);
//					torque_res = can_send_msg(motorId, close_motor, 8);
//					show_res(torque_res);
//				}

			                    	
//        rxlen = can_receive_msg(0x12, canbuf);  /* CAN ID = 0x12, ½ÓÊÕÊý¾Ý²éÑ¯ */

//        if (rxlen) /* ½ÓÊÕµ½ÓÐÊý¾Ý */
//        {
////            lcd_fill(30, 270, 130, 310, WHITE); /* Çå³ýÖ®Ç°µÄÏÔÊ¾ */

//            for (i = 0; i < rxlen; i++)
//            {
//                if (i < 4)
//                {
////                    lcd_show_xnum(30 + i * 32, 250, canbuf[i], 3, 16, 0X80, BLUE);          /* ÏÔÊ¾Êý¾Ý */
//									usart_show_xnum(canbuf[i], 3);
//                }
//                else
//                {
////                    lcd_show_xnum(30 + (i - 4) * 32, 270, canbuf[i], 3, 16, 0X80, BLUE);    /* ÏÔÊ¾Êý¾Ý */
//										usart_show_xnum(canbuf[i], 3);
//                }
//            }
//        }
//				torque_res = can_send_msg(motorId, torque_control_2, 8);
//        t++;
//        delay_ms(10);

//        if (t == 20)
//        {
//            LED0_TOGGLE();  /* ÌáÊ¾ÏµÍ³ÕýÔÚÔËÐÐ */
//            t = 0;
//            cnt++;
////            lcd_show_xnum(30 + 48, 150, cnt, 3, 16, 0X80, BLUE);                            /* ÏÔÊ¾Êý¾Ý */
////						usart_show_xnum(cnt, 3);
//        }
```

