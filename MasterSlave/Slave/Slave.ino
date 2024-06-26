#include <Wire.h>
int DO_Blink = 13;
byte I2C_OnOff;
void setup() 
{
  pinMode(DO_Blink, OUTPUT);
  Wire.begin(1);
  Wire.onReceive(BlinkLED);
}
void loop() 
{
  delay(100);
}

//When we receive data, this is called
void BlinkLED(int Press)
{
  I2C_OnOff = Wire.read();
  if (I2C_OnOff == 1)
  {
   digitalWrite(DO_Blink, HIGH);
  }
  else if (I2C_OnOff == 0)
  {
   digitalWrite(DO_Blink, LOW);
  } 
}