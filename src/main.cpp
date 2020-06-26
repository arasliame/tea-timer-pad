#include <Arduino.h>
#include <pitches.h>
#include <displaytime.h>

const int padPin = 16;
const int buzzPin = 4;
const int potPin = A0;
const int duration = 200; //duration of buzz
//10 seconds for testing //const int timerLength = 10; 
int timeSetting;
int prevObjState = 0;
int prevObjState2 = 0;
int timer = 0;
int objectOn = 0;
int potValue;
int prevPotValue;
int prevTimeSetting;
int prevTimeSetting2;

void setup() {
pinMode(padPin,INPUT);
pinMode(potPin,INPUT);
Serial.begin(9600); 
LedSetup();

}

void loop() {

prevPotValue = potValue;
potValue = analogRead(potPin);

Serial.print("Potentiometer: ");
Serial.print(potValue);
Serial.println();

prevObjState2 = prevObjState; //state 2 seconds back
prevObjState = objectOn; // state 1 second back
objectOn = digitalRead(padPin);

//warn when object is removed
if (!objectOn && prevObjState && prevObjState2) {
  tone(buzzPin, NOTE_F6, duration);
}

//start timer
if (objectOn && !prevObjState && !prevObjState2) //2 consecutive seconds before resetting timer
  {
    timer = timeSetting*30 + 1;
    tone(buzzPin,NOTE_B2,duration);
    lc.clearDisplay(0);
  }

//decrement timer
if (objectOn && timer != 0)
  {
    timer--;
    displayTime(timer);
    delay(500);
    if (timer > (60/8)) {displayTime(timer-(60/8+1));} //make the last one blink
    else {lc.clearDisplay(0);}
  }

//end timer
if (objectOn && (timer==0))
  {
    tone(buzzPin,NOTE_A5,duration); //enhancement - make it play a song :)
    lightAll(); //blink display
    delay(500);
    lc.clearDisplay(0); // 
  }

//only allow time selection display if there is nothing on the pressure pad
//only display time selection if the potentiometer has been moved
prevTimeSetting2 = prevTimeSetting;
prevTimeSetting = timeSetting;

if (!objectOn && abs(potValue - prevPotValue)>10 ) {
  timeSetting = map(potValue, 0, 1023, 0, 16);
  Serial.print("Timer Value Map: ");
  Serial.print(timeSetting);
  Serial.println();
  lc.clearDisplay(0);
  displayTime(timeSetting*30);
}

//turn off leds if setting has been the same for a while
if (!objectOn && (timeSetting == prevTimeSetting2) && (timeSetting == prevTimeSetting)) 
{lc.clearDisplay(0);}

Serial.print("Timer: ");
Serial.print(timer);
Serial.println();
Serial.print(objectOn);
Serial.println();

delay(500);
}
