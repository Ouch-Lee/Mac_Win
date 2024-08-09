#ifndef _DATA_TRAN
#define _DATA_TRAN
#include "./SYSTEM/sys/sys.h"

void get_all_motor_angles(void);
void send_CAN_array(float this_CAN_sending_para[12], float input_para[10]); 
void send_CAN_num(uint32_t can_id);
void print_sent_data(float *data, int size);
void float_2_uint16(float *CAN_sending_para, uint8_t *output);


#endif
