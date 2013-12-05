/*
 * i2c.c
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */

#include "i2c.h"
#include "int.h"
#include "gpio.h"
#include "dtim.h"
#include "support_common.h"
#include "utils.h"

// reset the registers for i2c
void i2c_reset()
{
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_IEN; 		// Set IEN to enable the I2C module.
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_IIEN; 	// Clear IIEN to disable I2C interrupts. We're going to use polling to determine when transfers complete.
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_MSTA;		// Clear MSTA to make the MCF52259 a slave.
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_MTX; 		// Clear MTX to make the MCF52259 a receiver. Now we're in slave-receiver mode.
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_TXAK;		// Clear TXAK so received data/address bytes will be automatically ACKed.
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_RSTA;		// Clear RSTA so Repeated Start bits will not be generated.
}

// initialize the i2c registers
void i2c_init()
{
	int dummy;
	MCF_GPIO_PASPAR |= MCF_GPIO_PASPAR_SCL0_SCL0;		// set pin 0 to the primary (I2C) function
	MCF_GPIO_PASPAR |= MCF_GPIO_PASPAR_SDA0_SDA0;		// set pin 1 to the primary (I2C) function
	
	MCF_I2C0_I2ADR |= 0x08 << 1;
	MCF_I2C0_I2FDR |= 0x3A; // IC = 896 //89.29KHz
	
	// call i2c reset
	i2c_reset();
	
	if(getBit(MCF_I2C0_I2SR, 5) == 1)
	{
		MCF_I2C0_I2CR = 0x00;
		MCF_I2C0_I2CR = 0xA0;
		dummy = MCF_I2C0_I2DR; // fake read...
		MCF_I2C0_I2SR = 0x00;
		MCF_I2C0_I2CR = 0x00;
		MCF_I2C0_I2CR = 0x80;
	}
}

// acquire the i2c bus
void i2c_acquire_bus()
{
	while ((MCF_I2C0_I2SR & 0x20) > 0) {} // Busy-wait until bus is free.
}

// check if the message is complete
int i2c_tx_complete()
{
	return getBit(MCF_I2C0_I2SR, 1);
}

// receive a byte from the i2c
uint8 i2c_receive_byte(int delay)
{
	uint8 byte = MCF_I2C0_I2DR;
	
	while(!i2c_tx_complete()) {}
	
	MCF_I2C0_I2SR &= ~MCF_I2C_I2SR_IIF;
	
	// call a DMA timer delay
	dtim0_busy_delay_us(delay);
	
	return byte;
}

// called on end receive or end send in the i2c
void i2c_rxtx_end()
{
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_MSTA;
	i2c_reset();
}

// send a byte through the i2c module
void i2c_tx_byte(uint8 byte, int delay)
{
	int_inhibit_all();
	MCF_I2C0_I2DR = byte;
	while(!i2c_tx_complete()) { }
	MCF_I2C0_I2SR &= ~MCF_I2C_I2SR_IIF;
	int_uninhibit_all();
	
	// call a DMA timer delay
	dtim0_busy_delay_us(delay);
}

// send an address through the i2c module
void i2c_tx_addr(int addr, int rw, int delay)
{
	uint8 tmp = 0;
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_MTX;
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_MSTA;
	
	tmp |= addr << 1;
	tmp |= rw;
	i2c_tx_byte(tmp, delay);
}

// send a command through the i2c with the address and data
void i2c_tx(int addr, int count, int data[], int delay)
{
	int i;
	i2c_acquire_bus();
	i2c_tx_addr(addr, 0x00, delay);
	
	for(i=0; i < count; i++)
	{
		i2c_tx_byte((unsigned char)data[i], delay);
	}
	i2c_rxtx_end();
}

// receive from the i2c module 
void i2c_rx(int addr, int count, int data[], int delay)
{
	int i;
	// acquire bus 
	i2c_acquire_bus();
	i2c_tx_addr(addr, 0x01, delay);
	
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_MTX;
	MCF_I2C0_I2CR &= ~MCF_I2C_I2CR_TXAK;
	
	// receive the data
	i2c_receive_byte(delay);
	
	// store the data
	for(i=0; i <count-1; i++)
	{
		data[i] = i2c_receive_byte(delay);
	}
	
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_TXAK;
	data[count-1] = i2c_receive_byte(delay);
	i2c_rxtx_end();
}