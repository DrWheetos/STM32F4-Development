
#include "usart.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"

//#ifndef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  //#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
  //#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif /* __GNUC__ */


/*******************************************************************************
* Function Name  : USART3_Configuration
* Description    : Configure Port_USART 
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void USART3_Configuration(void)
{ 												
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;

  // Enable clocks for port C and USART3
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  // RX and TX gpio pins
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // Set PC10 (TX) and PC11 (RX) to alternate function.
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

/*
   USART3 configured as follows:
     - BaudRate = 115200 baud
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - Hardware flow control disabled (RTS and CTS signals)
     - Receive and transmit
 */
  USART_InitStructure.USART_BaudRate            = 115200 * 25 / 8;
  USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits            = USART_StopBits_1;
  USART_InitStructure.USART_Parity              = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);

  // Enable USART3 Transmit interrupt.
  // This interrupt is generated when the USART3 transmit data register is empty.
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

  /* Enable the USART3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Switch USART3 on.
  USART_Cmd(USART3, ENABLE);
}

// ************************************************************************************************
// Sends a character to the usart transmit queue.
// Returns 0 for success, -1 if the queue is full.
// ************************************************************************************************
char USART3_SendCharacter(char c)
{
  USART3_qIndex i, j;

  // head points to the top of the queue, the next character to be sent out.
  // If head is at the end of the buffer, bring it back to the start of the buffer.
  i = USART3_head + 1;
  if (i >= USART3_TXBUFFERSIZE) i = 0;

  // Find out if the queue is full.
  // We have to copy this to a local variable as an interrupt could come along at the same
  // time which could change the tail.
  j = USART3_tail;
  if (i == j) return -1;

  // OK to add the character to the tx queue.
  USART3_TxBuffer[USART3_head] = c;
  USART3_head = i;

  // As there's now at least one character sitting in the tx queue waiting to be sent, enable
  // the TXE interrupt that gets fired when the USART3's tx buffer is empty.  This interrupt
  // signals that the next character in the queue can be sent.
  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

  // Signal success to the caller.
  return 0;
}

// ************************************************************************************************
// Sends a string (character array) to the usart transmit queue.
// ************************************************************************************************
void USART3_SendText(char* charBuffer, unsigned long numberOfChars)
{
  // Loop while there are more characters to send.
  do
  {
    // Add each character to USART3's tx fifo buffer.
    char result = USART3_SendCharacter(*charBuffer++);

    // Might want to rethink this.  If the buffer's full, it skips the remaining text to send.
    if (result != 0) return;
  }
  while (numberOfChars--);
}

// ************************************************************************************************
// Interrupt handler for handling TX and RX data.
// ************************************************************************************************
void USART3_IRQHandler(void)
{
  // Local holding buffer for received characters to build a line of characters
  static char rxLocalBuffer[USART3_RXLINEMAX];
  static int rxIndex = 0;
  USART3_qIndex i;

  // **********************************************************************************************
  // TRANSMIT
  // The USART is now able to transmit a character out so if there's one in the Tx buffer, send it.
  // **********************************************************************************************
  if (USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {
    // If the head and tail indices are different, we have some data in the tx fifo queue to send.
    i = USART3_tail;
    if (i != USART3_head)
    {
      // Drop the character from the fifo buffer into USART3's tx data register.  The hardware
      // will take over to send it.
      USART_SendData(USART3, (uint16_t)USART3_TxBuffer[i++]);

      // When we get to the end of the tx fifo queue, wrap the tail round to the start of it.
      if (i >= USART3_TXBUFFERSIZE) i = 0;
      USART3_tail = i;
    }
    else
    {
      // No data to send.
      // Switch off handling of the TXE interrupt.
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    }
  }

  // **********************************************************************************************
  // RECEIVE
  // If we've received a character, grab it.
  // **********************************************************************************************
  if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    // Grab the received character
    char rx = USART_ReceiveData(USART3);

    // First check whether we're within the receive buffer's limits.
    if (rxIndex == USART3_RXLINEMAX) rxIndex = 0;

    // Add the received character to the local receive buffer
    rxLocalBuffer[rxIndex++] = rx;

    // Is it an end of line character?
    if (rx == '\n')
    {
      // Copy the characters from the local receive buffer into the line buffer for onward
      // processing.  We don't use memcpy here to try and reduce dependencies on the stdio
      // libraries and hence code footprint.
      int i;
      char* source = rxLocalBuffer;
      char* dest = USART3_RxBuffer;
      for (i=0; i<rxIndex; i++)
      {
        *dest++ = *source++;
      }

      // Add the terminating character to the line buffer
      USART3_RxBuffer[rxIndex] = 0;

      // Flag that the line can be processed by the main routines.
      USART3_IsLineValid = 1;

      // Reset the index into the local receive buffer for the next set of characters to be
      // received.
      rxIndex = 0;
    }
  }
}
