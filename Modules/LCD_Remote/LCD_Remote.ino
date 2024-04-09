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
String text1 = String("Song name: ");
int TEXT1_LENGTH = text1.length();
String text2 = String("Artist name: ");
int TEXT2_LENGTH = text2.length();

//Index for both lines of text
int text1Index = 0;
int text2Index = 0;

bool inputRecieved = false;
long prevMillisLCD = 0;

#define LCD_DELAY 500

//Includes remote library
#include "IRremote.h"
int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 6
bool remoteRecieved = false; //Stores if we get input from remote
long prevMillisRem = 0;

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
#define REM_DELAY 500

/*-----( Function )-----*/
void translateIR() { // takes action based on IR code received
  // describing Remote IR codes 
  switch(results.value) {
    // case 0xFFA25D: Serial.println("POWER"); break;
    // case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    // case 0xFF629D: Serial.println("VOL+"); break;
    // case 0xFF22DD: Serial.println("FAST BACK");    break;
    // case 0xFF02FD: Serial.println("PAUSE");    break;
    // case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F:
      Serial.write("DOWN");
      break;
    // case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F:
      Serial.write("UP");
      break;
    // case 0xFF9867: Serial.println("EQ");    break;
    // case 0xFFB04F: Serial.println("ST/REPT");    break;
    case 0xFF6897:
      // Serial.println("0");
      Serial.write('0');
      break;
    case 0xFF30CF:
      // Serial.println("1");
      Serial.write('1');
      break;
    case 0xFF18E7:
      // Serial.println("2");
      Serial.write('2');
      break;
    case 0xFF7A85:
      // Serial.println("3");
      Serial.write('3');
      break;
    case 0xFF10EF:
      // Serial.println("4");
      Serial.write('4');
      break;
    case 0xFF38C7:
      // Serial.println("5");
      Serial.write('5');
      break;
    case 0xFF5AA5:
      // Serial.println("6");
      Serial.write('6');
      break;
    case 0xFF42BD:
      // Serial.println("7");
      Serial.write('7');
      break;
    case 0xFF4AB5:
      // Serial.println("8");
      Serial.write('8');
      break;
    // case 0xFF52AD: Serial.println("9");    break;
    // case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
    // default: 
    //   Serial.println(" other button : ");
    //   Serial.println(results.value);
  }// End Case

  // delay(500); // Do not get immediate repeat
} //END translateIR


//Scrolls through text in LCD Screen
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
  // Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
}

void scrollText() {
  lcd.clear();
  //Rewrites line 1 with charcter from quote, giving "illusion" of scrolling
  scroll(0, text1, &text1Index, TEXT1_LENGTH);
  //Rewrites line 2 with charcter from quote, giving "illusion" of scrolling
  scroll(1, text2, &text2Index, TEXT2_LENGTH);
}

void getInput(){
  Serial.println("Input Song name:");
  while (Serial.available() == 0) {}

  String input = Serial.readString();
  input.trim();
  text1 += input + " |";
  TEXT1_LENGTH = text1.length();

  Serial.println("Input Artist name:");
  while (Serial.available() == 0) {}

  input = Serial.readString();
  input.trim();
  text2 += input + " |";
  TEXT2_LENGTH = text2.length();

  // Serial.println(text1);
  // Serial.println(text2);
}



void loop() {
  // put your main code here, to run repeatedly:

  // if (inputRecieved == false) {
  //   getInput();
  //   inputRecieved = true;
  //   scrollText();
  // }

  long currentMillis = millis();

  if (currentMillis - prevMillisLCD >= LCD_DELAY) {
    prevMillisLCD = currentMillis;
    scrollText();
  }

  // If we get input from the remote...
  if (irrecv.decode(&results) && !remoteRecieved){
    translateIR(); 
    irrecv.resume(); // receive the next value
    remoteRecieved = true;
    prevMillisRem = currentMillis;
  }
  
  if(remoteRecieved && currentMillis - prevMillisRem >= REM_DELAY) {
    remoteRecieved = false;
  }

}
