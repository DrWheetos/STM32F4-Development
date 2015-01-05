/*
 * debug.h
 *
 *  Created on: 29 Oct 2014
 *      Author: nigel
 */

#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#include "stdint.h"


void ConfigureDebugOutputPin(void);
void PulseDebugHighLow(void);
void SetDebugPinHigh();
void SetDebugPinLow();


#endif /* INC_DEBUG_H_ */
