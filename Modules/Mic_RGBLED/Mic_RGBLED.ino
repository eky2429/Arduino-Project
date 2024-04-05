//For RGB LED
#define REDPIN 11
#define GREENPIN 10
#define BLUEPIN 9

#define RGBMAX 255
#define LED_DELAY 10
//# of phases for colors
const int phases[6] = {255, 255 * 2, 255 * 3, 255 * 4, 255 * 5, 255 * 6};
int i = 0;
int red = 0, green = 0, blue = 0;


//For MIC
#define MICPIN A0
#define MICMIN 50
#define MICMAX 100
#define MIC_DELAY 100

int micInput = 0;
float m = RGBMAX * 1.0 / (MICMAX - MICMIN);

//Multiplier from microphone

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Sets RGB LED Pins to OUTPUT
  red = 255, green = 0, blue = 0;
  pinMode(REDPIN,  OUTPUT);              
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  //Sets mic
  pinMode(MICPIN, INPUT);
}

//Sets RGB colors for RGB LED
void setColor(int redValue, int greenValue,  int blueValue) {
  redValue *= (micInput * m);
  greenValue *= (micInput * m);
  blueValue *= (micInput * m);
  analogWrite(REDPIN, redValue);
  analogWrite(GREENPIN,  greenValue);
  analogWrite(BLUEPIN, blueValue);

  // Serial.print("(");
  // Serial.print(redValue);
  // Serial.print(",");
  // Serial.print(greenValue);
  // Serial.print(",");
  // Serial.print(blueValue);
  // Serial.println(")");
}

void colorCycle(){
  //RED TO YELLOW TO GREEN TO CYAN TO BLUE TO VIOLET TO
  setColor(red, green, blue);
  if (i < phases[0]) {
    green++;
  } else if (i < phases[1]) {
    red--;
  } else if (i < phases[2]) {
    blue++;
  } else if (i < phases[3]) {
    green--;
  } else if (i < phases[4]) {
    red++;
  } else if (i < phases[5]) {
    blue--;
  } else {
    i = 0;
    return;
  }
  i++;
  // Serial.print("(");
  // Serial.print(red);
  // Serial.print(",");
  // Serial.print(green);
  // Serial.print(",");
  // Serial.print(blue);
  // Serial.println(")");
}

void loop() {

  if (millis() % MIC_DELAY == 0) {
    micInput = analogRead(MICPIN);
    Serial.println(micInput);
  }

  if (millis() % LED_DELAY == 0) {
    colorCycle();
    // Serial.println(i);
  }
}
