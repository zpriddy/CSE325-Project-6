//*******************************************************************************************************
// main.c
//
// Date: 2013-11-14 10:49:08
//
// DESCRIPTION:
//
// AUTHORS:
//  Abdulla Al Braiki (ayalbrai@asu.edu)
//  Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// 
//*******************************************************************************************************
#include <stdio.h>

#include "support_common.h"
#include "dtim.h"
#include "pit.h"
#include "dtim.h"
#include "i2c.h"
#include "oct_nunchuk.h"
#include "utils.h"


int pos_x, pos_y, acc_x, acc_y, acc_z, b_c, b_z;

static volatile int g_console_update;



static void uart_callback()
{

	
}

static void pb1_callback()
{
	

	
}

static void pb2_callback()
{

	
}

static void pit0_callback(int r1, int r2, int r3, int r4, int r5, int c, int z)
{
	pos_x = r1;
	pos_y = r2; 
	acc_x = r3; 
	acc_y = r4; 
	acc_z = r5;
	b_c = c;
	b_z = z;
	//g_console_update = 1;
	 
}

static void console_update()
{
	g_console_update = 1;
}




static void hw_init()
{
	int_inhibit_all();
	//dtim0_init();
	pit0_init(console_update, 9);
	nunchuk_init();
	
	
	
	
	int_uninhibit_all();
	g_console_update = 1;
	nunchuk_set_input_callback(pit0_callback);
	
	
	pit0_enable();
	//pit1_enable();
	
	

}



	
	





static void run()
{
	while(1)
	{
		printf("%d %d %d %d %d %d %d\n",
				pos_x,
				pos_y,
				acc_x,
				acc_y,
				acc_z,
				b_c,
				b_z
	);
		g_console_update = 1;
		
		
	}
}


__declspec(noreturn) int main()
{
	hw_init();
	run();
}