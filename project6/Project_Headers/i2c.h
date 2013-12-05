/*
 * i2c.h
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */

#include "support_common.h"

#ifndef IC2_H_
#define IC2_H_

void i2c_init();
void i2c_reset();
void i2c_acquire_bus();
int i2c_tx_complete();
uint8 i2c_receive_byte(int delay);
void i2c_rxtx_end();
void i2c_tx_byte(uint8 byte, int delay);
void i2c_tx_addr(int addr, int rw, int delay);
void i2c_tx(int addr, int count, int data[], int delay);
void i2c_rx(int addr, int count, int data[], int delay);

#endif /* IC2_H_ */
