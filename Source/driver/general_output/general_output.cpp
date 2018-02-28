#include "general_output.h"

void general_ouput_init() {
//	DRIVER_DBG("general_ouput_init() \n");
//	uint8_t status;
//	io_gpo_cfg();
//	io_gpo_trans_pin_reset();
//	for (uint8_t i = 1; i <= 4; ++i) {
//		status = read_backup_gpo(i);
//		if (status == 1) {
//			io_gpo_pin_set(i);
//		}
//		else {
//			io_gpo_pin_reset(i);
//		}
//	}
//	io_gpo_trans_pin_set();
//	sys_ctrl_delay_us(10);
//	io_gpo_trans_pin_reset();
}

void set_general_output_status(uint8_t pin, uint8_t status) {
//	if (status == 1) {
//		io_gpo_pin_set(pin);
//	}
//	else if (status == 0) {
//		io_gpo_pin_reset(pin);
//	}
//	else if(status == 255);

//	else {
//		return;
//	}
//	write_backup_gpo(pin, status);
//	io_gpo_trans_pin_set();
//	sys_ctrl_delay_us(10);
//	io_gpo_trans_pin_reset();
}

uint8_t get_general_output_status(uint8_t pin) {
	//return io_gpo_pin_get_status(pin);
	return (0);
}
