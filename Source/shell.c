/**
 ******************************************************************************
 * @Author: ThanNT
 * @Date:   13/08/2016
 ******************************************************************************
**/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../common/cmd_line.h"
#include "../common/xprintf.h"

/*****************************************************************************/
/*  command function declare
 */
/*****************************************************************************/
static int32_t shell_reset(uint8_t* argv);
static int32_t shell_ver(uint8_t* argv);
static int32_t shell_help(uint8_t* argv);
static int32_t shell_reboot(uint8_t* argv);
static int32_t shell_ram(uint8_t* argv);
static int32_t shell_flash(uint8_t* argv);
static int32_t shell_fatal(uint8_t* argv);

static int32_t shell_cfg(uint8_t* argv);
static int32_t shell_pop(uint8_t* argv);
static int32_t shell_out(uint8_t* argv);
static int32_t shell_mode(uint8_t* argv);
static int32_t shell_sensor(uint8_t* argv);
static int32_t shell_set_calib(uint8_t* argv);
static int32_t shell_modbus_rs485(uint8_t* argv);

static char* str_parser_get_attr(uint8_t index);
static uint8_t str_parser(char* str);

/*****************************************************************************/
/*  local declare
 */
/*****************************************************************************/
#define STR_LIST_MAX_SIZE		10
#define STR_BUFFER_SIZE			128

static char cmd_buffer[STR_BUFFER_SIZE];
static char* str_list[STR_LIST_MAX_SIZE];
static uint8_t str_list_len;

static uint8_t str_parser(char* str);
static char* str_parser_get_attr(uint8_t);

/*****************************************************************************/
/*  command table
 */
/*****************************************************************************/
cmd_line_t lgn_cmd_table[] = {

	/*************************************************************************/
	/* system command */
	/*************************************************************************/
	{(const int8_t*)"reset",	shell_reset,			(const int8_t*)"reset terminal"},
	{(const int8_t*)"ver",		shell_ver,				(const int8_t*)"version info"},
	{(const int8_t*)"help",		shell_help,				(const int8_t*)"help command info"},
	{(const int8_t*)"reboot",	shell_reboot,			(const int8_t*)"reboot system"},
	{(const int8_t*)"ram",		shell_ram,				(const int8_t*)"ram"},
	{(const int8_t*)"fatal",	shell_fatal,			(const int8_t*)"fatal test"},
	{(const int8_t*)"cfg",		shell_cfg,				(const int8_t*)"configure system"},
	{(const int8_t*)"flash",	shell_flash,			(const int8_t*)"flash device"},
	{(const int8_t*)"pop",		shell_pop,				(const int8_t*)"pop temperature control"},
	{(const int8_t*)"out",		shell_out,				(const int8_t*)"pop general output control"},
	{(const int8_t*)"mode",		shell_mode,				(const int8_t*)"pop mode switch"},
	{(const int8_t*)"sen",		shell_sensor,			(const int8_t*)"display sensors data"},
	{(const int8_t*)"set",		shell_set_calib,		(const int8_t*)"set sensor calib"},

	{(const int8_t*)"mbs",		shell_modbus_rs485	,	(const int8_t*)"RS485 Modbus interface "},

	/*************************************************************************/
	/* debug command */
	/*************************************************************************/

	/* End Of Table */
	{(const int8_t*)0,(pf_cmd_func)0,(const int8_t*)0}
};

/*****************************************************************************/
/*  parser function definaion
 */
/*****************************************************************************/
uint8_t str_parser(char* str) {
	strcpy(cmd_buffer, str);
	str_list_len = 0;

	uint8_t i = 0;
	uint8_t str_list_index = 0;
	uint8_t flag_insert_str = 1;

	while (cmd_buffer[i] != 0 && cmd_buffer[i] != '\n' && cmd_buffer[i] != '\r') {
		if (cmd_buffer[i] == ' ') {
			cmd_buffer[i] = 0;
			flag_insert_str = 1;
		}
		else if (flag_insert_str) {
			str_list[str_list_index++] = &cmd_buffer[i];
			flag_insert_str = 0;
		}
		i++;
	}

	cmd_buffer[i] = 0;

	str_list_len = str_list_index;
	return str_list_len;
}

char* str_parser_get_attr(uint8_t index) {
	if (index < str_list_len) {
		return str_list[index];
	}
	return NULL;
}

/*****************************************************************************/
/*  command function definaion
 */
/*****************************************************************************/
int32_t shell_reset(uint8_t* argv) {
	(void)argv;
	xprintf("\033[2J\r");
	return 0;
}

int32_t shell_ver(uint8_t* argv) {
	(void)argv;
	xprintf("app ver 1.0\n");
	return 0;
}

int32_t shell_fatal(uint8_t* argv) {
	xprintf("fatal not support\n");
	return 0;
}

int32_t shell_help(uint8_t* argv) {
	return 0;
}

int32_t shell_reboot(uint8_t* argv) {
}

int32_t shell_flash(uint8_t* argv) {
	return 0;
}

/* CMD format:
 * + "pop i" -> output pop ctl infor
 * + "pop 1  -> turn on air condition, turn off cooling fans
 * + "pop 2  -> turn off air condition, turn on cooling fans
 */
int32_t shell_pop(uint8_t* argv) {
	return 0;
}

/* CMD format:
 * + "out i j"-> output infor pin[1 -> 4]
 * + "out 1 1 -> general out 1 -> high
 * + "out 1 0 -> general out 1 -> low
 */
int32_t shell_out(uint8_t* argv) {
	uint8_t pin = 0;
	switch (*(argv + 6)) {

	// + "out x 0 -> general out x -> low
	case '0': {
		pin = *(argv + 4) - 48;
		if (pin > 0 && pin < 5) {
		}
		else goto exception;
	}
		break;

		// + "out x 1 -> general out x -> high
	case '1': {
		pin = *(argv + 4) - 48;
		if (pin > 0 && pin < 5) {
		}
		else goto exception;
	}
		break;

exception:
	default:
		break;
	}
	return 0;
}

/* CMD format:
 * + "mode a/m"-> mode switch -> [a: auto | m: manual]
 */
int32_t shell_mode(uint8_t* argv) {
	switch (*(argv + 5)) {
	case 'a':{
	}
		break;

	case 'm':{
	}
		break;

	case '?':{
	}
		break;

	default:
		break;
	}
	return 0;
}

/* CMD format:
 * + "sen"
 */
int32_t shell_sensor(uint8_t* argv) {
	return 0;
}

/* CMD format:
 * + "cfg p"
 */
int32_t shell_cfg(uint8_t* argv) {
	return 0;
}

/* set t1 +01 */
/* set h1 +01 */

int32_t shell_set_calib(uint8_t* argv){
	return 0;
}

int32_t shell_modbus_rs485(uint8_t* argv) {

	uint8_t	num_str = str_parser((char*)argv);
	char*	cmd;
	int8_t	addr = 0;
	uint16_t	value = 0;
	uint8_t slaveid = 0;

	switch (num_str) {

	case 5: {
		xprintf("MODBUS_DBG_WRITE_SINGLE_REGISTER_REQ\n");

		cmd		= str_parser_get_attr(2);
		addr	= atoi(str_parser_get_attr(3)); // check addrs
		slaveid = atoi(str_parser_get_attr(1));

		if ((addr < 0) || (addr > 12)) {
			goto exception;
		}

		if (strcmp((const char *)cmd, (const char *)"w") == 0) {
			value	= atoi(str_parser_get_attr(4));

			if ((value < 0) || (value > 1) ) {
				goto exception;
			}

			uint16_t reg_data;

			if(value == 0)
				reg_data = 0xFF00;
			else if(value == 1)
				reg_data = 0x0000;
			else
				goto exception;

			{
				;
			}
		}
		else if (strcmp((const char *)cmd, (const char *)"t") == 0) {
			xprintf("modbus reset single coil\n");
			value	= atoi(str_parser_get_attr(4));
			uint16_t reg_data;

			if(value < 50 || value > 100000) {
				goto exception;
			}
			else {
				reg_data = value;
			}

			{
				;
			}
		}
		else
			goto exception;
	}
		break;
exception:
	default:
		xprintf("\n");
		xprintf("mbs i to get slave list info\n");
		xprintf("mbs r to read all status coil\n");
		xprintf("mbs <slave addr>  w  < reg >  < value >  1:on 0:off\n");
		xprintf("mbs <slave addr>  t  < reg >  < (50ms < (time_toggle)  < 500000ms) > \n");
		xprintf("mbs <slave addr>  s  restart modbus slave\n");
		xprintf("\n");
		break;
	}
	return 0;
}
\
int32_t shell_ram(uint8_t* argv) {
	return 0;
}





