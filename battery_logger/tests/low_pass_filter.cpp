#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "../battery_logger/LowPassFilter.h"

TEST_GROUP(LowPassFiltering)
{

};

TEST(LowPassFiltering, CanProcessLowPass)
{
    float cutoff = 10;
    float sample_frequency = 100;
    LowPassFilter f(sample_frequency, cutoff);

    // Computes step response
    DOUBLES_EQUAL(0.4, f(1), 0.1);
    DOUBLES_EQUAL(0.7, f(1), 0.1);
    DOUBLES_EQUAL(0.85, f(1), 0.1);
}
