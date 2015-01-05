#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

/**
 * @brief Definition for COM port1, connected to USART3
 */ 
#define Open_USART                        USART3
#define Open_USART_CLK                    RCC_APB1Periph_USART3

#define Open_USART_TX_PIN                 GPIO_Pin_10
#define Open_USART_TX_GPIO_PORT           GPIOC
#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define Open_USART_TX_SOURCE              GPIO_PinSource10
#define Open_USART_TX_AF                  GPIO_AF_USART3


#define Open_USART_RX_PIN                 GPIO_Pin_11
#define Open_USART_RX_GPIO_PORT           GPIOC
#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define Open_USART_RX_SOURCE              GPIO_PinSource11
#define Open_USART_RX_AF                  GPIO_AF_USART3

#define Open_USART_IRQn                   USART3_IRQn
#define USARTx_IRQHANDLER                 USART3_IRQHandler


// Maximum number of characters expected on a line of received text
#define USART3_RXLINEMAX       200

// Size of the output transmit circular buffer.
#define USART3_TXBUFFERSIZE    200

typedef unsigned char USART3_qIndex;
volatile USART3_qIndex USART3_head;
volatile USART3_qIndex USART3_tail;

char USART3_TxBuffer[USART3_TXBUFFERSIZE];
char USART3_RxBuffer[USART3_RXLINEMAX + 1];


// Flag that indicates we have a line of characters to process.
char USART3_IsLineValid;

void USART3_Configuration(void);

//void USART3_Setup(USART_InitTypeDef* settings);
char USART3_SendCharacter(char c);
void USART3_SendText(char* charBuffer, unsigned long numberOfChars);

#endif /*_USART_H*/
