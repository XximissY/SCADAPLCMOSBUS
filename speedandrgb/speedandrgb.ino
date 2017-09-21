#include <Wire.h>
#include <AM2320.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);
AM2320 th;
const int redPin = 29;
const int greenPin = 30;
const int bluePin = 31;
const int fanspeed = 19;
const int potR = 10;
const int potG = 11;
const int potB = 12;
const int potF = 13;
int modePin = 25;
int potFvalue = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(fanspeed, OUTPUT);
  pinMode(modePin, INPUT);
  pinMode(potR, INPUT);
  pinMode(potG, INPUT);
  pinMode(potB, INPUT);
  pinMode(potF, INPUT);
  Wire.begin();
  Serial.begin(9600);
  lcd.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int r, g, b, fanspeedvalue;
  float temp;
  digitalRead(modePin);
  if (modePin = HIGH) {
    int tempvalue = map(th.t, 10, 80, 0, 100);
    fanspeedvalue = map(tempvalue, 0, 100, 0, 255);
    analogWrite(fanspeed, fanspeedvalue);
    colorful();
    delay(2);
  } else {

    r = analogRead(potR);
    g = analogRead(potG);
    b =  analogRead(potB);
    potFvalue = analogRead(potF);
    fanspeedvalue = map(potFvalue, 0, 1023, 0, 255);
    analogWrite(fanspeed, fanspeedvalue);
    setColor(r, g, b);
    delay(2);
  }

}
void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
void colorful()
{
  digitalRead(modePin);
  int beatingdelay = analogRead(potF);
  int beatingvalue = map(beatingdelay, 0, 1023, 50, 1000);
  do {
    for (int fadeValueR = 0 ; fadeValueR <= 255; fadeValueR += 5) {
      setColor(fadeValueR, 0, 0);  // red
      delay(beatingvalue);
    }
    for (int fadeValueR = 255 ; fadeValueR >= 0; fadeValueR -= 5) {
      // sets the value (range from 0 to 255):
      setColor(fadeValueR, 0, 0);  // red
      // wait for 30 milliseconds to see the dimming effect
      delay(beatingvalue);
    }

    for (int fadeValueG = 0 ; fadeValueG <= 255; fadeValueG += 5) {
      setColor( 0, fadeValueG, 0); // Green
      delay(beatingvalue);
    }
    for (int fadeValueG = 255 ; fadeValueG >= 0; fadeValueG -= 5) {
      // sets the value (range from 0 to 255):
      setColor( 0, fadeValueG, 0); // Green
      // wait for 30 milliseconds to see the dimming effect
      delay(beatingvalue);
    }

    for (int fadeValueB = 0 ; fadeValueB <= 255; fadeValueB += 5) {
      setColor( 0, 0, fadeValueB); // blue
      delay(beatingvalue);
    }
    for (int fadeValueB = 255 ; fadeValueB >= 0; fadeValueB -= 5) {
      // sets the value (range from 0 to 255):
      setColor( 0, 0, fadeValueB); // blue
      // wait for 30 milliseconds to see the dimming effect
      delay(beatingvalue);
    }
    for (int fadeValueRG = 0 ; fadeValueRG <= 255; fadeValueRG += 5) {
      setColor( fadeValueRG, fadeValueRG, 0); // yellow
      delay(beatingvalue);
    }
    for (int fadeValueRG = 255 ; fadeValueRG >= 0; fadeValueRG -= 5) {
      // sets the value (range from 0 to 255):
      setColor( fadeValueRG, fadeValueRG, 0); // yellow
      // wait for 30 milliseconds to see the dimming effect
      delay(beatingvalue);
    }
    for (int fadeValueRb = 0 ; fadeValueRb <= 255; fadeValueRb += 5) {
      setColor( fadeValueRb, 0, fadeValueRb); // yellow
      delay(beatingvalue);
    }
    for (int fadeValueRb = 255 ; fadeValueRb >= 0; fadeValueRb -= 5) {
      // sets the value (range from 0 to 255):
      setColor( fadeValueRb, 0, fadeValueRb); // yellow
      // wait for 30 milliseconds to see the dimming effect
      delay(beatingvalue);
    }
  } while (modePin = LOW);
}


