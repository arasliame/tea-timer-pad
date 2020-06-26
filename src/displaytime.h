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

void displayTime(int seconds) {
    int minutes = seconds / 60;
    int eigths = (seconds % 60)/8;
    for (int row = 0; row<matrixHeight; row++) {
        if (minutes != 0) {
            for (int col = 0; col < matrixWidth; col++) {
                lc.setLed(0,row,col,true);
            }
            minutes--;
            }
        if (minutes = 0) {
            for (eigths; eigths > 0; eigths--) {
                lc.setLed(0,row,eigths,true);
                }
            }
        }


}
        
            
        
    
