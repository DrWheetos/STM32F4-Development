/*
* Onewire library for DS18B20 Temperature sensor
*
*/
#ifndef ONEWIRE_H
#define ONEWIRE_H

/*
 * Includes
 */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#define OW_RCC            RCC_AHB1Periph_GPIOB
#define OW_GPIO_PORT      GPIOB
#define OW_GPIO_PIN_NO    15
#define OW_GPIO_PIN       1 << OW_GPIO_PIN_NO

#define OW_DELAY(x)       Delay(x)
#define OW_OUTPUT_LOW     OW_GPIO_PORT->BSRRH = OW_GPIO_PIN;
#define OW_OUTPUT_HIGH    OW_GPIO_PORT->BSRRL = OW_GPIO_PIN;
#define OW_PIN_INPUT      OW_GPIO_PORT->MODER &= ~(GPIO_MODER_MODER0 << (OW_GPIO_PIN_NO * 2)); OW_GPIO_PORT->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (OW_GPIO_PIN_NO * 2));
#define OW_PIN_OUTPUT     OW_GPIO_PORT->MODER |= (1 << (OW_GPIO_PIN_NO * 2));

/*
 * OneWire commands
 */
// Function commands
#define OW_CMD_CONVERT_TEMPERATURE  0x44    // Initiates a single temperature conversion
#define OW_CMD_READ_SCRATCHPAD      0xBE    // Read contents of scratchpad
#define OW_CMD_WRITE_SCRATCHPAD     0x4E    // Write 3 bytes to scratchpad
#define OW_CMD_COPY_SCRATCHPAD      0x48    // Copy scratchpad to EEPROM
#define OW_CMD_RECALL_EEPROM        0xB8    // Copy EEPROM back to scratchpad
#define OW_CMD_READ_POWER_SUPPLY    0xB4    // Any devices using parasite power?

// ROM commands
#define OW_CMD_ROM_SEARCH           0xF0
#define OW_CMD_ROM_READ             0x33
#define OW_CMD_ROM_MATCH            0x55
#define OW_CMD_ROM_SKIP             0xCC
#define OW_CMD_ALARM_SEARCH         0xEC



/*
 * Initialize the GPIO port and pin used to connect to the OneWire device.
 */
void OW_Init(void);


/*
 * Reset the OneWire device.
 */
uint8_t OW_Reset(void);


/*
 * Read the bit state from the OneWire device.
 */
uint8_t OW_ReadBit(void);


/*
 * Read a byte of data from the OneWire device.
 */
uint8_t OW_ReadByte(void);


/*
 * Write a bit to the OneWire device.
 */
void OW_WriteBit(uint8_t bit);


/*
 * Write a byte of data to the OneWire device.
 */
void OW_WriteByte(uint8_t byte);


/*
 * Search for OneWire device on the bus.
 *
 * command    Search command
 */
uint8_t OW_Device_Search(uint8_t command);


/*
 * Reset OneWire search.
 */
void OW_ResetSearch(void);


/*
 * Find the first device on the OneWire bus in a search.
 */
uint8_t OW_First(void);


/*
 * Move to the next device on the OneWire bus.
 */
uint8_t OW_Next(void);


/**
* Get rom from device from search
*
* Parameters
* - uint8_t index:
* because each device has 8bytes long rom, you have to call this 8 times, to get rom bytes from 0 to 7
* Returns ROM byte for index (0 to 7) at current found device
*/
uint8_t OW_GetROM(uint8_t index);


/**
* Get all 8 bytes ROM value from device from search
*
* Parameters
* - uint8_t *firstIndex:
* Pointer to first location for first byte, other bytes are automatically incremented
*/
void OW_GetFullROM(uint8_t *firstIndex);


/**
* Select specific slave on bus
*
* Parameters:
* - uint8_t addr[]
* 8 bytes ROM address
*/
void OW_Select(uint8_t addr[]);


/**
* Select specific slave on bus with pointer address
*
* Parameters:
* - uint8_t *ROM
* pointer to first byte of ROM address
*/
void OW_SelectWithPointer(uint8_t *ROM);


#endif
