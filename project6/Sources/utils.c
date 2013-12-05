/*
 * utils.c
 *
 *  Created on: Dec 4, 2013
 *      Author: zpriddy
 */
#include "utils.h"

void setBit(int number, int pos)
{
        number |= 1 << pos;
}

// Sets the bit at a specific position to 0
void clearBit(int number, int pos)
{
        number &= ~(1 << pos);
}

// returns the bit at a specific position
int getBit(int number, int pos)
{
    return (number & ( 1 << pos )) >> pos;
}