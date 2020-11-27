/*
  Samm.cpp - Library for comunicate arduino systems with sammgps.com.
  Created by Edasystem, November 27, 2020.
*/
#ifndef Samm_h
#define Samm_h
 
#include "Arduino.h"
#include <SoftwareSerial.h>

class Samm
{
  public:
    Samm();
    void begin(SoftwareSerial *serialToUse);
    void setDigitalInput(int inputNumber, int value);
    void setAnalogInput(int inputNumber, byte value);
    void report();
    void analyze();
  private:
    SoftwareSerial *_pSerial;
    int _serialRx;
    int _serialTx;
    long digitalInputs;
    int analigInputsCount = 5;
    byte analogInputs[5];
    void decode(String data);
    String getValueFromSplit(String data, char separator, int index);
    void sendCommand(String body);
};
 
#endif
