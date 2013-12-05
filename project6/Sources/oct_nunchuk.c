/*
 * oct_nunchuk.c
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */

#include "support_common.h"
#include "exceptions.h"
#include "dtim.h"
#include "oct_nunchuk.h"
#include "i2c.h"
#include "utils.h"
#include <stdio.h>



// Globals
static int_isr g_callback_input = 0;

/*
 * Initializes nunchuk facilities and starts reading input from the controller
 */
void nunchuk_init() {
        g_callback_input = NULL;
        dtim3_init();
        i2c_init();
        pit1_init(); // 250ms period, calls nunchuk_read() on interrupt
        
}

/*
 * Set a callback function for when a unique Nunchuk input is read
 * @param Function pointer that accepts a uint8_t representing the Nunchuk input command
 */
void nunchuk_set_input_callback(int_isr p_callback) {
	g_callback_input = p_callback;
}

/*
 * Called every 250ms by PIT1's ISR. Reads input from the controller over I2C and sends to the appropriate handler
 */
void nunchuk_read() {
		int c_bt = 0;
		int z_bt = 0;
        // Don't do anything if the callback hasnt been set yet
        if(g_callback_input == NULL) {
                return;
        }
        
        // Transmit initialization commands for unencrypted mode
        nunchuk_xmit_cmd(0xF0, 0x55);
        nunchuk_xmit_cmd(0xFB, 0x00);
        nunchuk_xmit_cmd(0x00, 0x00);
        //nunchuk_xmit_cmd(0x40, 0x00); // Authentic nintendo only
        
        // Read controller state (6 bytes)
        uint8 state[6];
        i2c_rx(NUNCHUK_I2C_ADDR, 6, state, NUNCHUK_I2C_DELAY_US);
        
        // Send the individual inputs to the callback function
        /*
        // Left / Right joystick movement
        if(state[0] < 30) {
                g_callback_input(NUNCHUK_INPUT_LEFT);
        } else if(state[0] > 200) {
                g_callback_input(NUNCHUK_INPUT_RIGHT);
        }
        
        // Up / Down joystick movement
        if(state[1] < 30) {
                g_callback_input(NUNCHUK_INPUT_DOWN);
        } else if(state[1] > 208) {
                g_callback_input(NUNCHUK_INPUT_UP);
        }*/
        
        // C button
        if((state[5] & (1 << 1)) == 0) {
        	//g_callback_input();
        	//printf("BUTTON Z\n");
        	c_bt = 1;
        }
        
        // Z button
        if((state[5] & (1 << 0)) == 0) {
        	//g_callback_input();
        	z_bt = 1;
        }
        
        g_callback_input(state[0],state[1],state[2],state[3],state[5],c_bt,z_bt);
        
        
}

/*
 * Sends a command to a register on the Nunchuk
 * 
 * @param reg Register to send cmd to. If 0x00, only send cmd
 * @param cmd Command byte to send to the nunchuk
 */
void nunchuk_xmit_cmd(uint8 reg, uint8 cmd) {
        uint8 data[2];
        int size = 0;
        if(reg != 0x00) { // Reg and command sent to nunchuck register
                size = 2;
                
                data[0] = reg;
                data[1] = cmd;
        } else { // Command send to a nunchuk register
                size = 1;
                
                data[0] = cmd;
        }
        
        i2c_tx(NUNCHUK_I2C_ADDR, size, data, NUNCHUK_I2C_DELAY_US);
        
        dtim3_delay_us(2 * NUNCHUK_I2C_DELAY_US);
       
}