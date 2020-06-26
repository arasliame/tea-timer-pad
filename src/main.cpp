#include <Arduino.h>
#include <pitches.h>
#include <displaytime.h>

const int padPin = 16;
const int buzzPin = 4;
const int duration = 200;
const int pitch = 800;
//3 seconds for testing
const int timerLength = 10; //3 * 60 //minutes for easier entering

int curPadState = 0;
int prevPadState = 0;
int prevObjState = 0;
int prevObjState2 = 0;
int timer = 0;
int objectOn = 0;

const int pressureThreshold = 500;

void setup() {
  // put your setup code here, to run once:
pinMode(padPin,INPUT);
Serial.begin(9600); 
LedSetup();

}

void loop() {

//prevPadState = curPadState;
//curPadState = digitalRead(padPin);

prevObjState2 = prevObjState; //additional variable 
prevObjState = objectOn;
objectOn = digitalRead(padPin);

/*
//analog code translate pressure #s to state
if ((prevPadState - curPadState) < -pressureThreshold) //object has been placed
  {
    objectOn = 1;
  }
else if ((prevPadState - curPadState) > pressureThreshold) //object has been removed
  {
    objectOn = 0;
    lc.clearDisplay(0);
  }
*/

//start timer
if (objectOn && !prevObjState && !prevObjState2) //2 consecutive seconds before resetting timer
  {
    timer = timerLength + 1;
    tone(buzzPin,NOTE_B2,duration);
    lc.clearDisplay(0);
  }

//decrement timer
if (objectOn && timer != 0)
  {
    timer--;
    displayTime(timer,500);
  }

//end timer
if (objectOn && (timer==0))
  {
    tone(buzzPin,NOTE_A5,duration); //enhancement - make it play a song :)
    lightAll();
    delay(500);
    lc.clearDisplay(0); // change this to blink the display
  }
Serial.print("Timer: ");
Serial.print(timer);
Serial.println();
Serial.print(objectOn);
Serial.println();

delay(500);
}
