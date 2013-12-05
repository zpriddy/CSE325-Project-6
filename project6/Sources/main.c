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

static void pit0_callback()
{
	g_console_update = 1;
	 
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
	
	
	
	pit0_enable();
	//pit1_enable();
	
	

}



	
	





static void run()
{
	while(1)
	{
		nunchuk_read();
		if(g_console_update == 1)
		{
			printf("TEST OUTPUT\n");
			g_console_update = 0;
		}
		
		
	}
}


__declspec(noreturn) int main()
{
	hw_init();
	run();
}