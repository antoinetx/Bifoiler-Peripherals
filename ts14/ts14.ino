#include <Wire.h>


#define DEV_REG_ID 0x01
#define DEV_REG_VAL 0x00
#define DEV_ID 0xA2

#define I2C_DEVICE_ADR 0x32

enum Action {NONE, SEND_DEVICE_ID, SEND_LAST_VALUE};

volatile Action action_required;
volatile uint32_t last_value;

void setup() {

  Wire.begin(I2C_DEVICE_ADR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  Serial1.begin(9600);
  Serial.begin(9600);
  delay(100);

}

void loop() {
  if (Serial1.available() > 0) {
    //Serial.println(Serial1.read());
    int value = Serial1.parseInt();
    //double conv = (double)value * 0.0859536;
    last_value = (uint32_t) value;
    Serial.println(value);
  }
  
  
  delay(50);

}


void requestEvent() {
  switch(action_required){
    case SEND_LAST_VALUE:
    {
      uint32_t value_to_send = last_value;
      Wire.write((uint8_t*) (&value_to_send), sizeof(value_to_send));
      //Wire.write((uint8_t) 0x01);
      //Wire.write((uint8_t) 0x01);      
    }
    break;

    case SEND_DEVICE_ID:
      Wire.write((uint8_t) DEV_ID);
    break;
  }

  action_required = NONE;
}

void receiveEvent(int howMany) {
  if(howMany == 1)
  {
    char c = Wire.read();
    switch(c){
      case DEV_REG_VAL:
        action_required = SEND_LAST_VALUE;
      break;

      case DEV_REG_ID:
        action_required = SEND_DEVICE_ID;
      break;
    }
  }
}

