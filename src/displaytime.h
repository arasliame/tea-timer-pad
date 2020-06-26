#include <LedControl.h>

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 14 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 12 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(14,13,12,1);

const int matrixHeight = 8;
const int matrixWidth = 8;

unsigned long delaytime=100;

void LedSetup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

}

void displayTime(int seconds,int blinkdelay) {
    lc.clearDisplay(0);
    int minutes = seconds / 60;
    Serial.print("Minutes: ");
    Serial.print(minutes);
    Serial.println();
    int eigths = (seconds % 60)/8;
    int blink = 0;
    Serial.print("Eigths: ");
    Serial.print(eigths);
    Serial.println();
        while (minutes) {
            for (int row = 0; row < matrixHeight; row++) {
                lc.setLed(0,row,minutes,true);
            }
            minutes--;
          }
      blink = eigths;
      while (eigths >= 0) {
        lc.setLed(0,eigths,0,true);
        eigths--;
      }
      delay(blinkdelay);
      lc.setLed(0,blink,0,false);
}

void lightAll () {
  for (int row = 0; row < matrixHeight; row++) {
    lc.setRow(0,row,B11111111);
  }
}