#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>


/* The serial port we'll send console output to.  The one connected to your PC. */
#define DEBUG_USART_PORT    USART3
