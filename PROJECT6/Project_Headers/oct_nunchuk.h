//*******************************************************************************************************
// oct_nunchuk.h
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
// Date: Dec 2, 2013
//
//********************************************************************************************************

#ifndef OCT_NUNCHUK_H
#define OCT_NUNCHUK_H

void oct_nunchuk_init();
int oct_nunchuk_pos_x();
int oct_nunchuk_pos_y();
int oct_nunchuk_accel_x();
int oct_nunchuk_accel_y();
int oct_nunchuk_accel_z();
int oct_nunchuk_button_c();
int oct_nunchuk_button_z();
 
#endif OCT_NUNCHUK_H