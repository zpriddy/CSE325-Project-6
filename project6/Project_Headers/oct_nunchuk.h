/*
 * oct_nunchuk.h
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */

#ifndef OCT_NUNCHUK_H_
#define OCT_NUNCHUK_H_

#include "pit.h"
#include "i2c.h"

// I2C constants
#define NUNCHUK_I2C_ADDR 0x52 // Nunchuk address
#define NUNCHUK_I2C_DELAY_US 150 // Time between I2C reads/writes

// Input constants
#define NUNCHUK_INPUT_Z 0x00
#define NUNCHUK_INPUT_C 0x01
#define NUNCHUK_INPUT_UP 0x02
#define NUNCHUK_INPUT_DOWN 0x03
#define NUNCHUK_INPUT_LEFT 0x04
#define NUNCHUK_INPUT_RIGHT 0x05

// Controller input callback that accepts a byte as the input command
//extern int_isr g_callback_input;

void nunchuk_init();
void nunchuk_set_input_callback(int_isr p_callback);
void nunchuk_read();
void nunchuk_xmit_cmd(uint8 reg, uint8 cmd);

#endif /* OCT_NUNCHUK_H_ */
