#include <Arduino.h>
#include <pitches.h>
//#include <displaytime.h>

const int padPin = 16;
const int buzzPin = 4;
const int duration = 200;
const int pitch = 800;
//3 seconds for testing
const int timerLength = 3; //3 * 60 //minutes for easier entering

int curPadState = 0;
int prevPadState = 0;
int prevObjState = 0;
int timer = 0;
int objectOn = 0;

const int pressureThreshold = 500;

void setup() {
  // put your setup code here, to run once:
pinMode(padPin,INPUT);
Serial.begin(9600); 


}

void loop() {
  // put your main code here, to run repeatedly:
prevPadState = curPadState;
curPadState = analogRead(padPin);

//prevObjState2 = prevObjState; //additional variable 
prevObjState = objectOn;


//translate pressure #s to state
if ((prevPadState - curPadState) < -pressureThreshold) //object has been placed
  {
    objectOn = 1;
  }
else if ((prevPadState - curPadState) > pressureThreshold) //object has been removed
  {
    objectOn = 0;
  }

//start timer
if (objectOn && !prevObjState)
  {
    timer = timerLength + 1;
    tone(buzzPin,NOTE_B2,duration);
  }

//increment timer
if (objectOn && timer != 0)
  {
    timer--;
  }

//end timer
if (objectOn && (timer==0)) 
  {
    tone(buzzPin,NOTE_A5,duration); //enhancement - make it play a song :)
  }
//displayTime(timer);
//Serial.print("Timer: ");
//Serial.print(timer);
Serial.print(curPadState);
Serial.println();
delay(1000);
}