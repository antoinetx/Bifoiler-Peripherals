#include "drotek_sensor.h"
#include "LowPassFilter.h"

const float sample_freq = 1000;

// We are recording at 1 Hz, so we need to cutoff below 1/2 Hz to
// respect Shannon limit
const float cutoff_freq = 0.25;

LowPassFilter current_lpf(sample_freq, cutoff_freq);
LowPassFilter voltage_lpf(cutoff_freq, cutoff_freq);

void setup() {
  Serial.begin(115200);
  Serial.println("time_s,current_a,voltage_v");
}

void loop() {
  static int sample_index = 0;
  int v_adc = analogRead(0);
  int i_adc = analogRead(1);

  float i = current_lpf(i_adc);
  float u = voltage_lpf(v_adc);

  if (sample_index ++ == 1000) {
    char line[128];
    sprintf(line, "%d,%.2f,%.2f", millis(), i, u);
    Serial.println(line);
    sample_index = 0;
  }
  delayMicroseconds(1000);
}
