/*
 * ds18b20.h
 *
 *  Created on: 8 Nov 2014
 *      Author: nigel
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include <stdint.h>


// Interval in seconds between reading the temperature
#define TEMP_SAMPLING_INTERVAL   5

// Set this flag to 1 to enable temperature measurements
#define DS18B20_ENABLED   1

// Temperature units.
typedef enum
{
  CELSIUS,
  FAHRENHEIT
} TemperatureUnitsTypeDef;

TemperatureUnitsTypeDef temperatureUnits;

// Identifies the different stages of reading the current temperature.
typedef enum
{
  // DS18B20 is not doing anything
  IDLE,

  // DS18B20 has been instructed to read the temperature.
  // It could be busy, or it may have finished reading it,
  // in which case the temperature can be read.
  CONVERSION_STARTED,

  // The temperature has been read and is available in private
  // variables for conversion.  The caller can call the appropriate
  // function to get the temperature in Fahrenheit or Celsius.
  TEMPERATURE_AVAILABLE
} DS18B20StatusTypeDef;

DS18B20StatusTypeDef DS18B20Status;
uint8_t tempSampleInterval;


void DS18B20ReadTemperature();
void DS18B20_Init();
float GetTemperatureCelsius();
float GetTemperatureFahrenheit();
uint16_t BlockAndReadRawTemperature();
void ShowROMCodesOfDevices();


#endif /* INC_DS18B20_H_ */
