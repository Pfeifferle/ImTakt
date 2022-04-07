#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 7
#define DIO 6
#define TEST_DELAY   1000
TM1637Display display(CLK, DIO);
const int led = 0;
const int leddrei = 1;
const int ledvier = 2;
const int buttonUp = 3;
const int buttonDown = 4;
const int buttonModus = 5;
int buttonUp_state = LOW;
int buttonDown_state = LOW;
int buttonModus_state = LOW;
int takt = 60;
float ton;
float pause; 
int wait = 10;
int taktModus = 4;
int noteNumber = 1;



void setup() {
  pinMode(led, OUTPUT);
  pinMode(leddrei, OUTPUT);
  pinMode(ledvier, OUTPUT);
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonModus, INPUT);
  
  digitalWrite(led, HIGH);
  
  display.setBrightness(0x02);
 
  
}

void loop() {
  
 

  buttonUp_state = digitalRead(buttonUp);
  buttonDown_state = digitalRead(buttonDown);
  buttonModus_state = digitalRead(buttonModus);
  if (LOW == buttonUp_state) {
    takt=takt+5;
    if (takt>180){ takt=180; }
    while (LOW == buttonUp_state) {
      buttonUp_state = digitalRead(buttonUp);
    }
    wait = 10;
  }
  if (LOW == buttonDown_state) {
    takt=takt-5;
    if (takt<60) { takt=60; }
    while (LOW == buttonDown_state) {
      buttonDown_state = digitalRead(buttonDown);
    }
    wait = 10;    
  }

  if (LOW == buttonModus_state) {
    if (taktModus == 4) { taktModus = 3; }
    else { taktModus = 4; }
    while (LOW == buttonModus_state) {
      buttonModus_state = digitalRead(buttonModus);
    }
    wait = 10;    
  }
  ton = ((float)60000) / ((float)takt);
  ton = ton / 4;
  if(taktModus==4) {
    if (noteNumber==1) {
      pause=ton*2;
     ton=pause;
    } else {
      pause=ton*3;
    }
  }

  
  digitalWrite(led, HIGH);
  delay(ton);
  digitalWrite(led, LOW);
  delay(pause);
  if (wait>0){
    display.showNumberDec(takt, false);
    
    if(taktModus==4)
    {digitalWrite(8,HIGH);
    digitalWrite(13,LOW);}
    else
    {digitalWrite(13,HIGH);
    digitalWrite(8,LOW);}
  }
  else{
    display.clear();
    digitalWrite(13,LOW);
    digitalWrite(8,LOW);
  }
  wait = wait - 1;
  noteNumber = noteNumber + 1;
  if (noteNumber == taktModus){noteNumber=1;}
}