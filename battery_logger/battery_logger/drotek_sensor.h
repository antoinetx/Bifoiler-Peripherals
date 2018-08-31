#pragma once

float drotek_volts_from_adc(int adc)
{
  const float battery_divider = 15.55;
  const float vcc = 5.0;

  return adc * (vcc / 1024) * battery_divider;
}

float drotek_amps_from_adc(int adc)
{
  const float amps_per_volt = 151.5;

  /* Voltage output when the current is zero */
  const float offset = 1.65;
  const float vcc = 5.0;

  return ((adc * vcc / 1024) - offset) * amps_per_volt;
}
