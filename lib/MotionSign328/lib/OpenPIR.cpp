#include "Arduino.h"
#include "OpenPIR.h"
//#include <avr/io.h>


#define PIR_AOUT A0  // PIR analog output on A0
#define PIR_DOUT 8   // PIR digital output on D2

#define PRINT_TIME 100 // Rate of serial printouts

unsigned long lastPrint = 0; // Keep track of last serial out

void OpenPIR::init(){
  // Analog and digital pins should both be set as inputs:
  pinMode(PIR_AOUT, INPUT);
  pinMode(PIR_DOUT, INPUT);

}

void OpenPIR::run(Data &data){
  data.motion.nudgeMax();
  this->getAnalog(data);
  this->getDigital(data);
}

void OpenPIR::getAnalog(Data &data){
  data.motion.setAnalog( analogRead(PIR_AOUT) );

  //float voltage = (float) data.analogPIR / 1024.0 * 5.0;
  // Print the reading from the digital pin.
  // Mutliply by 5 to maintain scale with AOUT.
  /*
  Serial.print(5 * digitalRead(PIR_DOUT));
  Serial.print(',');    // Print a comma
  Serial.print(2.5);    // Print the upper limit
  Serial.print(',');    // Print a comma
  Serial.print(1.7);    // Print the lower limit
  Serial.print(',');    // Print a comma
  Serial.print(voltage); // Print voltage
  Serial.println();
  */

}

void OpenPIR::getDigital(Data &data){
  // The OpenPIR's digital output is active high
  data.motion.setDigital( digitalRead(PIR_DOUT) );

}
