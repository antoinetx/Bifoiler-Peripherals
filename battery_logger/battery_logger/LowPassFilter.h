#pragma once

class LowPassFilter {
  public:
    LowPassFilter(float sample_frequency, float cutoff_frequency) : output(0.)
    {
      const float dt = 1 / sample_frequency;

      alpha = 2 * 3.14 * dt * cutoff_frequency / (2 * 3.14 * dt * cutoff_frequency + 1);
      one_minus_alpha = 1 - alpha;
    }

    float operator()(float input)
    {
      output = alpha * input + one_minus_alpha * output;
      return output;
    }

  private:
    float output;
    float alpha;
    float one_minus_alpha;
};
