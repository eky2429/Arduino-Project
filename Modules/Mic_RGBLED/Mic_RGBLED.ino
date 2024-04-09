/*.  For RGB LED.  */
#define REDPIN 11
#define GREENPIN 10
#define BLUEPIN 9

#define RGBMAX 255
#define LED_DELAY 50

//For color cycle
const int phases[6] = {255, 255 * 2, 255 * 3, 255 * 4, 255 * 5, 255 * 6};
int i = 0;
long prevMillisLED = 0;

int mode = 0; //Mode for RGB LED

//Stores global red green and blue values to use in terms of RGB
int red = 0, green = 0, blue = 0;


/*.  For MIC.  */
#define MICPIN A0

#define MICMIN 1
#define MICMAX 20

#define MIC_DELAY 100

int micInput = 0;
//Multiplier from microphone
float m = 1.0 / (MICMAX - MICMIN);

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
  // Serial.print("M is ");
  // Serial.println(m);
}

int boundColor(int val) {
  // return (val)
  return 0;
}

//Sets RGB colors for RGB LED
void setColor() {
  int redValue = red * (micInput * m);
  int greenValue = green * (micInput * m);
  int blueValue = blue * (micInput * m);
  // Serial.print("(");
  // Serial.print(redValue);
  // Serial.print(",");
  // Serial.print(greenValue);
  // Serial.print(",");
  // Serial.print(blueValue);
  // Serial.println(")");
  analogWrite(REDPIN, redValue);
  analogWrite(GREENPIN,  greenValue);
  analogWrite(BLUEPIN, blueValue);
}

void colorCycle(){
  //RED TO YELLOW TO GREEN TO CYAN TO BLUE TO VIOLET TO
  setColor();
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

void setRGBValues() {
  switch (mode) {
    case 0:
      colorCycle();
      break; //Color Cycle
    case 1:  //Red
      if (red != RGBMAX || green != 0 || blue != 0) {
        red = RGBMAX, green = 0, blue = 0;
      }
      setColor();
      break;
    case 2: //Yellow
      if (red != RGBMAX || green != RGBMAX || blue != 0) {
        red = RGBMAX, green = RGBMAX, blue = 0;
      }
      setColor();
      break;
    case 3: //Green
      if (red != 0 || green != RGBMAX || blue != 0) {
        red = 0, green = RGBMAX, blue = 0;
      }
      setColor();
      break;
    case 4: //Cyan
      if (red != 0 || green != RGBMAX || blue != RGBMAX) {
        red = 0, green = RGBMAX, blue = RGBMAX;
      }
      setColor();
      break;
    case 5: //Blue
      if (red != 0 || green != 0 || blue != RGBMAX) {
        red = 0, green = 0, blue = RGBMAX;
      }
      setColor();
      break;
    case 6: //Magenta
      if (red != RGBMAX || green != 0 || blue != RGBMAX) {
        red = RGBMAX, green = 0, blue = RGBMAX;
      }
      setColor();
      break;
    case 7: //White
      if (red != RGBMAX || green != RGBMAX || blue != RGBMAX) {
        red = RGBMAX, green = RGBMAX, blue = RGBMAX;
      }
      setColor();
      break;
    case 8: //Black / OFFF
      if (red != 0 || green != 0 || blue != 0) {
        red = 0, green = 0, blue = 0;
      }
      setColor();
      break;
    // default: Serial.println("Something's not right");
  }
}

void analyzeMessage(char message) {
  if (message >= '0' && message <= '9') {
    mode = message - '0';
  }
  if (mode == 0) {
    if (red != RGBMAX || green != 0 || blue != 0 || i != 0) {
      i = 0;
      red = RGBMAX, green = 0, blue = 0;
    }
  }
}

void loop() {
  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < MIC_DELAY; ++i) {
    int val = analogRead(MICPIN);
    mn = min(mn, val);
    mx = max(mx, val);
  }

  micInput = mx - mn;
  // Serial.println(micInput);

  if (millis() - prevMillisLED >= LED_DELAY) {
    prevMillisLED = millis();
    setRGBValues();
    // Serial.println(i);
  }

  //Gets input from other Arduino
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      char message = Serial.readString();
      // String message2 = String("Message: " + message);
      // Serial.println(message2);
      analyzeMessage(message);
    }
  }
}
