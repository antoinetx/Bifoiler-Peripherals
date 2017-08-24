Arduino files for EPFL bifoiler peripherals

Those drivers allow the the Arduino to act as a translator, which is then
connected through I2C to a PX4.

Drivers for the following peripherals are provided:

* EMS22: An 10 bit absolute encoder, read through (software) SPI.
* TS14: A ultrasonic distance sensor (Senix ToughSonic 14)

