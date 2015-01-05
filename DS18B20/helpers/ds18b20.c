/*
 * ds18b20.c
 *
 *  Created on: 8 Nov 2014
 *      Author: nigel
 */

#include "onewire.h"
#include "ds18b20.h"
#include <stdio.h>


// Raw temperature reading from the DS18B20 device.
// This can be converted into Fahrenheit or Celsius values by
// applying a conversion factor.
static uint16_t rawTemperature;



void DS18B20_Init()
{
  OW_Init();
  rawTemperature = 0;
  tempSampleInterval = TEMP_SAMPLING_INTERVAL;
}

// ************************************************************************************************
// This should be called after every second in the main loop.
//
//  - Check whether temperature reading is enabled
//  - If the TempSampleInterval counter != 0, decrement the counter
// - If counter > 0, exit
//  - If counter == 0,
//      - Check the status flag.
//      - if it's Idle, call the start process
//      - if it's Conversion_Started, check whether the DS18B20 is busy.
//          - If it is, just return.
//          - If it isn't, execute the read process function
//      - if it's Temperature_Available,
//          - convert temperature to celsius and display it
//          - set status flag to Idle
//          - reload the TempSampleInterval counter
// ************************************************************************************************
void DS18B20ReadTemperature()
{
  uint8_t TL, TH;

  if (DS18B20_ENABLED)
  {
    // Don't read the temperature if the interval hasn't timed out yet.
    if (tempSampleInterval != 0)
    {
      tempSampleInterval--;
      return;
    }

    // Check the status flag
    if (DS18B20Status == IDLE)
    {
      // Tell the DS18B20 to start reading the temperature
      OW_Reset();
      OW_WriteByte(OW_CMD_ROM_SKIP);
      OW_WriteByte(OW_CMD_CONVERT_TEMPERATURE);

      // Bump the status on to the next stage.
      DS18B20Status = CONVERSION_STARTED;
    }
    else if (DS18B20Status == CONVERSION_STARTED)
    {
      // Check whether the DS18B20 chip has finished reading the temperature.
      // If not, leave it to the next call of this function.
      if (OW_ReadByte() == 0) return;

      // Temperature conversion has completed.  It's time to read it from the chip.
      OW_Reset();

      OW_WriteByte(OW_CMD_ROM_SKIP);
      OW_WriteByte(OW_CMD_READ_SCRATCHPAD);

      TL= OW_ReadByte();
      TH= OW_ReadByte();

      rawTemperature = (uint16_t)(TL) | ((uint16_t)TH<<8);

      // Bump the status on to the next stage.
      DS18B20Status = TEMPERATURE_AVAILABLE;
    }
    else if (DS18B20Status == TEMPERATURE_AVAILABLE)
    {
      // Reset the sample interval.
      tempSampleInterval = TEMP_SAMPLING_INTERVAL;
      DS18B20Status = IDLE;
    }
  }
}


float GetTemperatureCelsius()
{
  return 0.0625 * (float)rawTemperature;
}

float GetTemperatureFahrenheit()
{
  return 0.1125 * (float)(rawTemperature + 32);
}


/*
 * Read the temperature from a DS18B20 device.
 *
 * It blocks the processor while it's reading the device.
 * It takes about 700us.
 */
uint16_t BlockAndReadRawTemperature()
{
  uint8_t TL, TH;

  OW_Reset();
  OW_WriteByte(OW_CMD_ROM_SKIP);
  OW_WriteByte(OW_CMD_CONVERT_TEMPERATURE);

  while (OW_ReadByte() == 0);   // wait while busy

  OW_Reset();

  OW_WriteByte(OW_CMD_ROM_SKIP);
  OW_WriteByte(OW_CMD_READ_SCRATCHPAD);

  TL= OW_ReadByte();
  TH= OW_ReadByte();

  rawTemperature = (int16_t)(TH << 8) | ((int16_t)TL);

  return rawTemperature;
}


void ShowROMCodesOfDevices()
{
  uint8_t devices, i, j, count, device[2][8];
  count = 0;

  // Search for devices on the OneWire bus.
  devices = OW_First();

  // Enumerate through each device found.
  while (devices)
  {
    count++;

    // Read the OneWire device lasered ROM code (8 bytes).
    for (i = 0; i < 8; i++)
    {
      device[count - 1][i] = OW_GetROM(i);
    }

    // Move to the next device found on the OneWire bus.
    devices = OW_Next();
  }

  // Show the lasered ROM code (8 bytes) for each device found on the bus.
  if (count > 0)
  {
    printf("Devices found on OneWire bus: %d\r", count);

    // Show the lasered ROM code for each device found.
    for (j = 0; j < count; j++)
    {
      for (i = 0; i < 8; i++)
      {
        printf("%02X ", device[j][i]);
      }
    }
  }
  else
  {
    printf("No devices found.");
  }

}

