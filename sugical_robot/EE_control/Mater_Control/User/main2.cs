update_encoder_angle();
get_all_motor_angles();
// 编码5帧数据
send_CAN_array_0(motor_encoder_angles)
print_sent_data(motor_encoder_angles, 5);

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
        HAL_Delay(2); // Uncomment this line in actual hardware code
    }

}
