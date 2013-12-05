/*
 * oct_nunchuk.h
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */

#ifndef OCT_NUNCHUK_H_
#define OCT_NUNCHUK_H_

void nunchuk_init();
void nunchuk_onBtnC();
void nunchuk_onBtnZ();
void nunchuk_onStickDown();
void nunchuk_onStickLeft();
void nunchuk_onStickRight();
void nunchuk_onStickUp();
void nunchuk_onStickAtRest();
void nunchuk_xmit_cmd(int reg, int cmd);
void nunchuk_read();

#endif /* OCT_NUNCHUK_H_ */
