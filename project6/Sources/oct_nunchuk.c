/*
 * oct_nunchuk.c
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */

#include "support_common.h"
#include "dtim.h"
#include "oct_nunchuk.h"
#include "i2c.h"
#include "utils.h"
#include <stdio.h>

// initialize the nunchuk controls
void nunchuk_init()
{
	dtim0_init();
	i2c_init(100);
	printf("nunchuk init\n");
}

// called with the nunchuk button c is pressed
void nunchuk_onBtnC()
{
	
}

// called with the nunchuk button z is pressed
void nunchuk_onBtnZ()
{
	
}

// called with the nunchuk stick is reset
void nunchuk_onStickAtRest()
{
	//game_change_dir(NONE);
}

// called with the nunchuk stick is down
void nunchuk_onStickDown()
{
	//game_change_dir(DOWN);
}

// called with the nunchuk stick is left
void nunchuk_onStickLeft()
{
	//game_change_dir(LEFT);
}

// called with the nunchuk stick is right
void nunchuk_onStickRight()
{
	//game_change_dir(RIGHT);
}

// called with the nunchuk stick is up
void nunchuk_onStickUp()
{
	//game_change_dir(UP);
	printf("up");
}

// sets up the command to the nunchuk to initialize it for transfer
void nunchuk_xmit_cmd(int reg, int cmd)
{
	int data[2] = {0,0};
	int count = 0;
	if(reg != 0x00)
	{
		data[0] = reg;
		data[1] = cmd;
		count =2;
	}
	else 
	{
		data[0] = cmd;
		count = 1;
	}
	
	i2c_tx(0x52, count, data, 150);
	
	// Delay DMA timer
	dtim0_busy_delay_us(300);
}

// read data from the nunchuck and call the interrupt functions
void nunchuk_read()
{
	int data[6] = {0x80,0x80,0,0,0,0};
	
	nunchuk_xmit_cmd(0xF0, 0x55);
	nunchuk_xmit_cmd(0xFB, 0x00);
	nunchuk_xmit_cmd(0x00, 0x00);
	
	i2c_rx(0x52, 6, data, 150);
	
	if(data[0] < 75)
		nunchuk_onStickLeft();
	else if(data[0] > 175)
		nunchuk_onStickRight();
	
	else if(data[1] < 75)
		nunchuk_onStickDown();
	else if(data[1] > 175)
		nunchuk_onStickUp();
	
	else if(data[0] > 100 && data[0] < 150 && data[1] > 100 && data[1] < 150)
		nunchuk_onStickAtRest();
	
	if(getBit(data[5],1) == 0)
		nunchuk_onBtnC();
	
	if(getBit(data[5],0) == 0)
		nunchuk_onBtnZ();
	
	// game button update
	//game_ButtonUpdate(~getBit(data[5],0));
		
}
