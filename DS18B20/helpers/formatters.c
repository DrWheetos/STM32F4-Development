/*
 * formatters.c
 *
 *  Created on: 8 Nov 2014
 *      Author: nigel
 */

#include "formatters.h"
#include <stdio.h>

/*
 * Formats a float into a string to help with printing it out
 * to a serial port.
 *
 * value      the float value to format
 * buffer     a character buffer the formatted number is put into
 * precision  the number of decimal places you require
 */
char* FormatFloatToString(float value, char* buffer, uint8_t precision)
{
  uint8_t i;
  uint32_t factor = 1;
  for(i=0; i<precision; i++)
    factor *= 10;

  int d2 = (value - (int)value) * factor;
  if (d2 < 0) d2 = -d2;
  sprintf(buffer, "%d.%d", (int)value, d2);
  return buffer;
}


