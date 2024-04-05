// include the library code:
#include <LiquidCrystal.h>

//  Pins for LCD
const int registerPin = 7;
const int enablePin = 8;
const int D4Pin = 9;
const int D5Pin = 10;
const int D6Pin = 11;
const int D7Pin = 12;

//  Constants for LCD
const int SIZE_OF_ROW = 16;
const int NUM_COLS = 2;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(registerPin, enablePin, D4Pin, D5Pin, D6Pin, D7Pin);

//Text for state1
String text1;
int TEXT1_LENGTH;
String text2;
int TEXT2_LENGTH;

//Index for both lines of text
int text1Index = 0;
int text2Index = 0;

bool inputRecieved = false;

#define LCD_DELAY 100

void scroll(int row, String text, int *index, int length) {
  //Rewrites line 2 with charcter from quote, giving "illusion" of scrolling
  lcd.setCursor(0, row);
  for (int i = 0; i < SIZE_OF_ROW; i++) {
    lcd.print(text.charAt((i + (*index)) % length));
  }

  //Sets quote index back to 0 if too high
  if ((*index) % length == 0) {
    (*index) = 0;
  }

  (*index)++;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Sets up Serial monitor (for debugging)
  lcd.begin(SIZE_OF_ROW, NUM_COLS); //Initializes display of LCD
}

void getInput(){
  Serial.println("Input Artist name:");
  while (Serial.available() == 0) {}

  text1 = Serial.readString();
  TEXT1_LENGTH = text1.length();

  Serial.println("Input song name:");
  while (Serial.available() == 0) {}

  text2 = Serial.readString();
  TEXT2_LENGTH = text2.length();
}



void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("White loop:");

  if (inputRecieved == false) {
    Serial.println("White loop:");
    getInput();
    inputRecieved = true;
  }

  if (millis() % LCD_DELAY == 0) {
    lcd.clear();
    //Rewrites line 1 with charcter from quote, giving "illusion" of scrolling
    scroll(0, text1, &text1Index, TEXT1_LENGTH);
    //Rewrites line 2 with charcter from quote, giving "illusion" of scrolling
    scroll(1, text2, &text2Index, TEXT2_LENGTH);
  }

}