#include <Wire.h>

#define CS 6
#define DATA 5
#define CLK 4

#define DEV_REG_ID 0x01
#define DEV_REG_VAL 0x00
#define DEV_ID 0xA1

#define I2C_DEVICE_ADR 0x30

enum Action {NONE, SEND_DEVICE_ID, SEND_LAST_VALUE};

volatile Action action_required;
volatile uint16_t last_value;

void setup() {
  // put your setup code here, to run once:
  pinMode(CS, OUTPUT);
  pinMode(DATA, INPUT);
  pinMode(CLK, OUTPUT);

  digitalWrite(CS, HIGH);
  digitalWrite(CLK, HIGH);

  Wire.begin(I2C_DEVICE_ADR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  Serial.begin(57600);
  delay(100);
  Serial.println("Device initialized.");
}

void loop() {
  uint16_t absolute_value = 0;
  bool s1, s2, lin, inc, dec, parity, msg_parity;
  chip_select();
  for(int i = 0; i < 15; i++){
    msg_parity = 1;
    clock_tick();
    delayMicroseconds(1);
    bool data = digitalRead(DATA);

    //Parity calculation
    if(data)
      msg_parity = !msg_parity;
   
    if(i < 10)
      absolute_value += (data << (9 - i));
    else {
      switch(i){
        case 10:
          s1 = data;
        break;
        case 11:
          s2 = data;
        break;
        case 12:
          lin = data;
        break;
        case 13:
          inc = data;
        break;
        case 14:
          dec = data;
        break;
        case 15:
          parity = data;
        break;
      }
    }
  }
  chip_unselect();
  
  last_value = absolute_value;

  if(parity == msg_parity)
    Serial.println("Err : Incorrect parity.");

  Serial.print("Actual value is ");
  Serial.print(absolute_value, DEC);
  Serial.println(".");

  Serial.print("Flag state : s1 = ");
  Serial.print(s1 , DEC);
  Serial.print(", s2 = ");
  Serial.print(s2 , DEC);
  Serial.print(", lin = ");
  Serial.print(lin , DEC);
  Serial.print(", inc = ");
  Serial.print(inc , DEC);
  Serial.print(", dec = ");
  Serial.println(dec , DEC);

}

void chip_select(){
  digitalWrite(CS, LOW);
  delayMicroseconds(1);
  
}

void chip_unselect(){
  delayMicroseconds(1);
  digitalWrite(CS, HIGH);
}

void clock_tick(){
  digitalWrite(CLK, LOW);
  delayMicroseconds(1);
  digitalWrite(CLK, HIGH);
}

void requestEvent() {
  switch(action_required){
    case SEND_LAST_VALUE:
    {
      int value_to_send = last_value;
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

