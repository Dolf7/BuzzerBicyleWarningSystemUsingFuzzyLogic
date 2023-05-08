#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "fuzzy.h"

// set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);  //0x27 is i2c address

//Define ALL PIN
int trig_pin = 9;
int echo_pin = 10;
int buzzer = 6;
int speedIntPin = 2;

//VARIABLE to Count SPEED
float REV = 0;
int RPM_VALUE;
unsigned long PREVIOUS = 0;
int TIME;
float kelilingRoda = 0.7;  //1.57 ; //in Meter

//OUTPUT VARIABLE AND FUZZY INPUT
float distance = 0;
int speedKMH = 0;

//OUPUT PWM FROM FUZZY OUTPUT
int pwmBuzzer = 0;

//FOR Timer LCD
unsigned long lcdTimer;

//DEFINE FUNCTION
void interupsi();
int buzzer_trig();
float getDistance();
int geSpeed();
void setLCD();
void updateLCD();
int getStatus();

String buzzerStatus[] = { "M ", "P ", "S ", "AK", "K ", "SK" };

void setup() {
  //init Serial and LCD
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // init All PIN
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(speedIntPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(speedIntPin), interupsi, RISING);
  digitalWrite(trig_pin, LOW);

  lcd.setCursor(2, 0);  //Set cursor to character 2 on line 0
  lcd.print("Hello There!!!");
  delay(2500);
  setLCD();
  Serial.println("START");
}

void loop() {
  distance = getDistance();
  speedKMH = getSpeed();
  pwmBuzzer = buzzer_trig();
  updateLCD();
}


int buzzer_trig() {
  //IMPLEMENTATION OF FUZZY FOR BUZZER PWM VALUE
  fuzzyData fuzzy(speedKMH, distance);
  analogWrite(buzzer, fuzzy.output);

  Serial.print("OUTPUT VALUE : ");
  Serial.println(fuzzy.output);

  return fuzzy.output;
}

void interupsi() {
  //INT USED FOR getDistance();
  REV++;
}

float getDistance() {
  // TRIGGER AND COLLECT DATA FROM HC-SR04
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // COUNT DISTANCE
  long echotime = pulseIn(echo_pin, HIGH);
  float distance = echotime * 0.0343 / 2;  //in CM

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

int getSpeed() {
  detachInterrupt(0);  // STOP Interrupt Process When Count Speed
  TIME = millis() - PREVIOUS;
  RPM_VALUE = (REV / TIME) * 60000;
  PREVIOUS = millis();
  REV = 0;

  int speed = (kelilingRoda * RPM_VALUE * 60) / 1000;  //COUNT SPEED in Km/H

  Serial.print("RPM : ");
  Serial.println(RPM_VALUE);

  Serial.print("Speed : ");
  Serial.println(speedKMH);

  attachInterrupt(digitalPinToInterrupt(speedIntPin), interupsi, FALLING);  // START INTERRUPT
  return speed;
}

void setLCD() {
  //SET LCD 16x2 Template
  //SPD:XXX PWM:XXX
  //DIS:XXX STS:XXX
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SPD:    PWM:");
  lcd.setCursor(0, 1);
  lcd.print("DIS:    STS:");
  //Start LCD Timer
  lcdTimer = millis()
}

void addSpaces(int x) {
  if (x < 100) lcd.print(' ');
  if (x < 10 && x >= 0) lcd.print(' ');
}

void updateLCD() {
  // Update LCD every 1 second without delay
  if(millis() - lcdTimer >= 1000){ 
    lcdTimer = millis();
    //Print SPEED Value in LCD
    lcd.setCursor(4, 0);
    lcd.print(speedKMH);
    addSpaces(speedKMH);

    //PRINT PWM Value in LCD
    lcd.setCursor(12, 0);
    lcd.print(pwmBuzzer);
    addSpaces(pwmBuzzer);

    //PRINT DIS Valuein LCD
    lcd.setCursor(4, 1);
    lcd.print(int(distance));
    addSpaces(int(distance));

    //PRINT Status Value in LCD
    lcd.setCursor(12, 1);
    lcd.print(buzzerStatus[getStatus()]);
  }
  return;
}

int getStatus() {
  if (pwmBuzzer >= 1 && pwmBuzzer < 51) return 1;          // 1 - 50 PELAN
  else if (pwmBuzzer >= 51 && pwmBuzzer < 102) return 2;   // 51 - 101 Sedang
  else if (pwmBuzzer >= 102 && pwmBuzzer < 153) return 3;  // 102 - 152 Agak Kuat
  else if (pwmBuzzer >= 153 && pwmBuzzer < 204) return 4;  // 153 - 203 Kuat
  else if (pwmBuzzer >= 204 && pwmBuzzer < 255) return 5;  // 204 - 255 Sangat Kuat
  return 0;                                                // 0 or Other MATI
}
