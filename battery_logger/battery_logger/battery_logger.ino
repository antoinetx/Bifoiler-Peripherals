#include "drotek_sensor.h"
#include "LowPassFilter.h"

#define LED_PIN 13
#define PERIOD_TRIM 9

const float sample_freq = 1000;


// We are recording at 1 Hz, so we need to cutoff below 1/2 Hz to
// respect Shannon limit
const float cutoff_freq = 0.1;

LowPassFilter current_lpf(sample_freq, cutoff_freq);
LowPassFilter voltage_lpf(cutoff_freq, cutoff_freq);

void setup() {
  Serial.begin(115200);
  Serial.println("time_ms,current_ma,voltage_mv");
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  static int sample_index = 0;
  static bool led_status = false;

  int start_us = micros();

  int v_adc = analogRead(0);
  int i_adc = analogRead(1);

  // Filter the samples
  float i = current_lpf(i_adc);
  float u = voltage_lpf(v_adc);

  // Write down result every second
  if (sample_index ++ == 1000) {
    char line[128];
    sprintf(line, "%lu,%ld,%ld", millis(), static_cast<long>(1000 * i), static_cast<long>(1000 * u));
    Serial.println(line);
    sample_index = 0;
    led_status = !led_status;
    digitalWrite(LED_PIN, led_status);
  }

  int stop_us = micros();
  delayMicroseconds(1000 - PERIOD_TRIM - (stop_us - start_us));
}
