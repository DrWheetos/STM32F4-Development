#include "onewire.h"
#include "delay.h"
#include "debug.h"

GPIO_InitTypeDef OW_GPIO_InitDef;

uint8_t OW_ROM_NO[8];

// Search state
uint8_t OW_LastDiscrepancy;
uint8_t OW_LastFamilyDiscrepancy;
uint8_t OW_LastDeviceFlag;

/*
 * Initialise the GPIO port and pin for talking to OneWire devices.
 */
void OW_Init(void)
{
  RCC_AHB1PeriphClockCmd(OW_RCC, ENABLE);

  OW_GPIO_InitDef.GPIO_Pin = OW_GPIO_PIN;
  OW_GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
  OW_GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
  OW_GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
  OW_GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(OW_GPIO_PORT, &OW_GPIO_InitDef);

  GPIO_ResetBits(OW_GPIO_PORT, OW_GPIO_PIN);
}


/*
 * Reset the OneWire device.
 *
 * All communication with the DS18B20 begins with an initialization sequence
 * that consists of a reset pulse from the master followed by a presence
 * pulse from the DS18B20.
 *
 */
uint8_t OW_Reset(void)
{
  uint8_t retries = 125;

  // Wait until the wire is high... just in case.
  // We'll only wait for 125 * 2 = 250us.
  OW_PIN_INPUT;
  do
  {
    if (--retries == 0) return 1;
    OW_DELAY(2);
  } while (!GPIO_ReadInputDataBit(OW_GPIO_PORT, OW_GPIO_PIN));

  // OneWire Initialization sequence
  // The bus master transmits (TX) the reset pulse by pulling the 1-Wire bus
  // low for a minimum of 480µs.  The bus master then releases the bus and
  // goes into receive mode (RX).
  OW_OUTPUT_LOW;
  OW_PIN_OUTPUT;
  OW_DELAY(500);
  OW_PIN_INPUT;

  // When the bus is released, the 5kΩ pullup resistor pulls the 1-Wire bus high.
  // When the DS18B20 detects this rising edge, it waits 15µs to 60µs and then
  // transmits a presence pulse by pulling the 1-Wire bus low for 60µs to 240µs.
  // So the DS18B20 should have started its presence pulse within 70us.
  OW_DELAY(70);

  // Read the presence pulse.  0 = OK, 1 = Error or no device.
  uint8_t presenceState = GPIO_ReadInputDataBit(OW_GPIO_PORT, OW_GPIO_PIN);

  // Allow time for the sensor to complete it's 480us reset period.
  OW_DELAY(450);

  // Return whether the sensor is present or not.
  return presenceState;
}


uint8_t OW_ReadBit(void)
{
  uint8_t bit = 0;

  // Initiate the bus sequence to tell the OneWire device to
  // send a bit on the bus.
  OW_OUTPUT_LOW;
  OW_PIN_OUTPUT;    // master takes bus low for 3us
  OW_DELAY(3);
  OW_PIN_INPUT;     // master releases the bus.

  // Wait a few microseconds before reading the bus.
  OW_DELAY(8);
  if (GPIO_ReadInputDataBit(OW_GPIO_PORT, OW_GPIO_PIN) == Bit_SET)
  {
    bit = 1;
  }

  // Wait 45us to complete the 60us period
  OW_DELAY(45);

  return bit;
}


uint8_t OW_ReadByte(void)
{
  uint8_t i = 8, byte = 0;
  while (i--)
  {
    byte >>= 1;
    byte |= (OW_ReadBit() << 7);
  }
  return byte;
}

/*
 * Writes a bit onto the bus (takes 60us)
 */
void OW_WriteBit(uint8_t bit)
{

  if (bit & 1)
  {
    // Write logic 1
    // Take bus low for 5us, then high for 55us.
    OW_OUTPUT_LOW;
    OW_PIN_OUTPUT;
    OW_DELAY(5);
    OW_OUTPUT_HIGH;
    OW_DELAY(55);
  }
  else
  {
    // Write logic 0
    // Take bus low for 55us, then high for 5us.
    OW_OUTPUT_LOW;
    OW_PIN_OUTPUT;
    OW_DELAY(55);
    OW_OUTPUT_HIGH;
    OW_DELAY(5);
  }
}

/*
 * Write a data byte to the device, LSB first.
 *
 */
void OW_WriteByte(uint8_t byte)
{
  uint8_t i = 8;
  while (i--)
  {
    OW_WriteBit(byte & 0x01);
    byte >>= 1;
  }
}


/*
 * Start a new search for devices on the bus.
 */
uint8_t OW_First(void)
{
  OW_ResetSearch();
  return OW_Device_Search(OW_CMD_ROM_SEARCH);
}


/*
 * Search for the next device on the bus.
 */
uint8_t OW_Next(void)
{
  // leave the search state alone
  return OW_Device_Search(OW_CMD_ROM_SEARCH);
}


/*
 * Reset the search state.
 */
void OW_ResetSearch(void)
{
  OW_LastDiscrepancy = 0;
  OW_LastDeviceFlag = 0;
  OW_LastFamilyDiscrepancy = 0;
}


uint8_t OW_Device_Search(uint8_t command)
{
  uint8_t id_bit_number;
  uint8_t last_zero, rom_byte_number, search_result;
  uint8_t id_bit, cmp_id_bit;
  uint8_t rom_byte_mask, search_direction;

  // initialize for search
  id_bit_number = 1;
  last_zero = 0;
  rom_byte_number = 0;
  rom_byte_mask = 1;
  search_result = 0;

  // if the last call was not the last one
  if (!OW_LastDeviceFlag)
  {
    // 1-Wire reset
    if (OW_Reset())
    {
      // reset the search
      OW_LastDiscrepancy = 0;
      OW_LastDeviceFlag = 0;
      OW_LastFamilyDiscrepancy = 0;
      return 0;
    }

    // issue the search command
    PulseDebugHighLow();
    OW_WriteByte(command);
    PulseDebugHighLow();

    // loop to do the search
    do
    {
      // read a bit and its complement
      id_bit = OW_ReadBit();
      cmp_id_bit = OW_ReadBit();

      // check for no devices on 1-wire
      if ((id_bit == 1) && (cmp_id_bit == 1))
      {
        break;
      }
      else
      {
        // all devices coupled have 0 or 1
        if (id_bit != cmp_id_bit)
        {
          search_direction = id_bit; // bit write value for search
        }
        else
        {
          // if this discrepancy is before the Last Discrepancy
          // on a previous next then pick the same as last time
          if (id_bit_number < OW_LastDiscrepancy)
          {
            search_direction = ((OW_ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
          }
          else
          {
            // if equal to last pick 1, if not then pick 0
            search_direction = (id_bit_number == OW_LastDiscrepancy);
          }

          // if 0 was picked then record its position in LastZero
          if (search_direction == 0)
          {
            last_zero = id_bit_number;
            // check for Last discrepancy in family
            if (last_zero < 9)
            {
              OW_LastFamilyDiscrepancy = last_zero;
            }
          }
        }

        // set or clear the bit in the ROM byte rom_byte_number
        // with mask rom_byte_mask
        if (search_direction == 1)
        {
          OW_ROM_NO[rom_byte_number] |= rom_byte_mask;
        }
        else
        {
          OW_ROM_NO[rom_byte_number] &= ~rom_byte_mask;
        }

        // serial number search direction write bit
        OW_WriteBit(search_direction);

        // increment the byte counter id_bit_number
        // and shift the mask rom_byte_mask
        id_bit_number++;
        rom_byte_mask <<= 1;

        // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
        if (rom_byte_mask == 0)
        {
          //docrc8(ROM_NO[rom_byte_number]); // accumulate the CRC
          rom_byte_number++;
          rom_byte_mask = 1;
        }
      }
    } while(rom_byte_number < 8); // loop until through all ROM bytes 0-7

    // if the search was successful then
    if (!(id_bit_number < 65))
    {
      // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
      OW_LastDiscrepancy = last_zero;

      // check for last device
      if (OW_LastDiscrepancy == 0)
      {
        OW_LastDeviceFlag = 1;
      }
      search_result = 1;
    }
  }

  // if no device found then reset counters so next 'search' will be like a first
  if (!search_result || !OW_ROM_NO[0])
  {
    OW_LastDiscrepancy = 0;
    OW_LastDeviceFlag = 0;
    OW_LastFamilyDiscrepancy = 0;
    search_result = 0;
  }
  return search_result;
}


int OW_Verify()
{
  unsigned char rom_backup[8];
  int i,rslt,ld_backup,ldf_backup,lfd_backup;

  // keep a backup copy of the current state
  for (i = 0; i < 8; i++)
    rom_backup[i] = OW_ROM_NO[i];

  ld_backup = OW_LastDiscrepancy;
  ldf_backup = OW_LastDeviceFlag;
  lfd_backup = OW_LastFamilyDiscrepancy;

  // set search to find the same device
  OW_LastDiscrepancy = 64;
  OW_LastDeviceFlag = 0;

  if (OW_Device_Search(OW_CMD_ROM_SEARCH))
  {
    // check if same device found
    rslt = 1;
    for (i = 0; i < 8; i++)
    {
      if (rom_backup[i] != OW_ROM_NO[i])
      {
        rslt = 1;
        break;
      }
    }
  }
  else
  {
    rslt = 0;
  }

  // restore the search state
  for (i = 0; i < 8; i++)
  {
    OW_ROM_NO[i] = rom_backup[i];
  }

  OW_LastDiscrepancy = ld_backup;
  OW_LastDeviceFlag = ldf_backup;
  OW_LastFamilyDiscrepancy = lfd_backup;

  // return the result of the verify
  return rslt;
}


void OW_TargetSetup(uint8_t family_code)
{
  uint8_t i;

  // set the search state to find SearchFamily type devices
  OW_ROM_NO[0] = family_code;

  for (i = 1; i < 8; i++)
  {
    OW_ROM_NO[i] = 0;
  }

  OW_LastDiscrepancy = 64;
  OW_LastFamilyDiscrepancy = 0;
  OW_LastDeviceFlag = 0;
}


void OW_FamilySkipSetup()
{
  // set the Last discrepancy to last family discrepancy
  OW_LastDiscrepancy = OW_LastFamilyDiscrepancy;
  OW_LastFamilyDiscrepancy = 0;

  // check for end of list
  if (OW_LastDiscrepancy == 0)
  {
    OW_LastDeviceFlag = 1;
  }
}


uint8_t OW_GetROM(uint8_t index)
{
  return OW_ROM_NO[index];
}


void OW_Select(uint8_t addr[])
{
  uint8_t i;
  OW_WriteByte(OW_CMD_ROM_MATCH);
  for (i = 0; i < 8; i++)
  {
    OW_WriteByte(*(addr + i));
  }
}


void OW_SelectWithPointer(uint8_t *ROM)
{
  uint8_t i;
  OW_WriteByte(OW_CMD_ROM_MATCH);
  for (i = 0; i < 8; i++)
  {
    OW_WriteByte(*(ROM + i));
  }
}


void OW_GetFullROM(uint8_t *firstIndex)
{
  uint8_t i;
  for (i = 0; i < 8; i++)
  {
    *(firstIndex + i) = OW_ROM_NO[i];
  }
}
