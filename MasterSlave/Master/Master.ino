#include <Wire.h>

//Stores message to use
String readString;

//Byte to send to slave
byte I2C_OnOff;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Type On to turn on the LED and Off to shut it down!");
}

void loop()
{

  //When we recieve input, trasnfer text letter by letter
  while (Serial.available())
  {
    delay(2);
    char c = Serial.read();
    readString += c;
    Serial.println(readString);
  }

  //Compares value
  if (readString == "BlueOn" || readString == "BLUEON" || readString == "blueon")
  {
    Serial.println("LED is ON");   
    I2C_OnOff = 1;
  }
  else if (readString == "BlueOff" || readString == "BLUEOFF" || readString == "blueoff")
  {
    Serial.println("LED is OFF");   
    I2C_OnOff = 0;
  }

  //Prints user's input
  // if (readString.length() > 0)                                            
  // {
  //   Serial.println(readString);                                            
  //   readString = "";                                                        
  // }

  //Sends message to Slave
  Wire.beginTransmission(1);                                                
  Wire.write(I2C_OnOff);                                                    
  Wire.endTransmission();                                                   
}