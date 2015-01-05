/*
 * debug.c
 *
 *  Created on: 29 Oct 2014
 *      Author: nigel
 */

#include "stdint.h"
#include "stm32f4xx_gpio.h"
#include "debug.h"
#include "stm32f4xx_rcc.h"


/**
  * Pulses a debug pin high then low.  Used for debugging with the logic analyzer.
  *
*/
void PulseDebugHighLow(void)
{
  GPIO_SetBits(GPIOH, GPIO_Pin_4);
  GPIO_ResetBits(GPIOH, GPIO_Pin_4);
}

void SetDebugPinHigh()
{
  GPIO_SetBits(GPIOH, GPIO_Pin_4);
}

void SetDebugPinLow()
{
  GPIO_ResetBits(GPIOH, GPIO_Pin_4);
}


void ConfigureDebugOutputPin(void)
{
  // Switch the clocks on for GPIO port H.
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

  // Configure PH2 and PH4 as an output for debug tracing with the logic analyzer
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOH, &GPIO_InitStructure);

  // Set the output pins low
  GPIO_ResetBits(GPIOH, GPIO_Pin_4);
}
