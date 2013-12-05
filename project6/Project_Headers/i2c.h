/*
 * i2c.h
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */

#include "support_common.h"

#ifndef IC2_H_
#define IC2_H_

#define I2C_ADDR 0xBE // Unique I2C address identifying the board
#define I2C_READ 0x01
#define I2C_WRITE 0x00

void i2c_init();
void i2c_acquire_bus();
void i2c_reset();
void i2c_rx(uint8 addr, int size, uint8 *data, int delay_us);
uint8 i2c_rx_byte(int delay_us);
void i2c_rxtx_end();
void i2c_tx(uint8 addr, int size, uint8 *data, int delay_us);
void i2c_tx_addr(uint8 addr, uint8 rw, int delay_us);
void i2c_tx_byte(uint8 data, int delay_us);
int i2c_tx_complete();

#endif /* IC2_H_ */
