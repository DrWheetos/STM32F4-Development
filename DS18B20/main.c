/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30 October 2014
  * @brief   The main file for the Rotary Encoder demo/test project.
  ******************************************************************************
*/

#include "main.h"
#include "usart.h"
#include "stm32f4xx_usart.h"
#include <stdio.h>
#include <string.h>
//#include "onewire.h"
#include "ds18b20.h"
#include "delay.h"
#include "debug.h"
#include "formatters.h"
#include <math.h>

/*
 * Function prototypes.
 */





int main()
{
  /* Initialize system */
  SystemInit();

  /* Initialize delay */
  TM_DELAY_Init();

  // Pin GPIO H4 for use by logic analyser.
  ConfigureDebugOutputPin();

  USART3_Configuration();
  printf("\r***************************************************************\r");
  printf("* DS18B20 Temperature Controller                              *\r");
  printf("***************************************************************\r");

  // Setup the GPIO port and pin to talk to OneWire devices.
  DS18B20_Init();

  //Search for devices and show their ROM codes.
  ShowROMCodesOfDevices();
  printf(" \r");


  char buffer[80];
  while (1)
  {
    // Read the temperature.  Blocks the processor for 700us or so.
    //BlockAndReadRawTemperature();

    // Read the temperature.  Non-blocking.
    DS18B20ReadTemperature();

    if (DS18B20Status == TEMPERATURE_AVAILABLE)
    {
      //float celsius = (float)roundf(GetTemperatureCelsius() * 100) / 100;
      float celsius = GetTemperatureCelsius();
      printf("Temp:  %s\r", FormatFloatToString(celsius, buffer, 2));
    }

    Delayms(500);
  }
}

