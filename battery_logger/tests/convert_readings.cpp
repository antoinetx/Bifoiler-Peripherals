#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "../battery_logger/drotek_sensor.h"

TEST_GROUP(DrotekConversion)
{

};

TEST(DrotekConversion, CanConvertBatteryVoltage)
{
    DOUBLES_EQUAL(30, drotek_volts_from_adc(395), 0.1);
    DOUBLES_EQUAL(60, drotek_volts_from_adc(791), 0.1);
}

TEST(DrotekConversion, CanConvertBatteryCurrent)
{
    DOUBLES_EQUAL(20.0, drotek_amps_from_adc(364), 1);
    DOUBLES_EQUAL(40.0, drotek_amps_from_adc(391), 1);
}
