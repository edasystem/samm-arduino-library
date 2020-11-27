/*
  Samm.cpp - Library for comunicate arduino systems with sammgps.com.
  Created by Edasystem, November 27, 2020.
*/
 
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Samm.h"

const String sammCommandSplitter = "|";
String dataAccum = "";
boolean reading = false;
 
Samm::Samm() {}

/*
Allow to initialize the instance passing the SoftwareSerial instance
*/
void Samm::begin(SoftwareSerial *serialToUse) {
  _pSerial = serialToUse;
}
 
void Samm::setDigitalInput(int inputNumber, int value)
{
  bitWrite(digitalInputs, inputNumber, value);
}

void Samm::setAnalogInput(int inputNumber, byte value) {
  analogInputs[inputNumber] = value;
  // (*_pSerial).println(value, HEX);
}
 
void Samm::report()
{
  String body = "R|";
  body.concat(String(digitalInputs, HEX));
  body.concat(sammCommandSplitter);
  for (byte i = 0; i < analigInputsCount; i = i + 1) {
    String hexValue = String(analogInputs[i], HEX);
    if (hexValue.length() == 1) {
      hexValue = "0"+hexValue;
    }
    body.concat(hexValue);
    // (*_pSerial).println(hexValue);
  }
  sendCommand(body);
}

void Samm::analyze()
{
  while ((*_pSerial).available() > 0) {
    char inChar = (*_pSerial).read();
    if (inChar == '>') {
      reading = false;
      if (dataAccum.length() > 0) {
        decode(dataAccum);
        dataAccum = "";
      }
    }
    if (reading) {
      dataAccum += inChar;
    }
    if (inChar == '<') {
      reading = true;
      dataAccum = "";
    }
  }
}

void Samm::decode(String data) {
  if (data.length() == 0) return;
  char cmd = data[0];
  // digital output
  if (cmd == 'O') {
    if (data.length() < 3) return;
    String output = getValueFromSplit(data.substring(1), '|', 1);
    String status = getValueFromSplit(data.substring(1), '|', 2);
    digitalWrite(output.toInt(), status == "1" ? HIGH : LOW);
    sendCommand("O|1");
  }
}

// https://stackoverflow.com/questions/9072320/split-string-into-string-array
String Samm::getValueFromSplit(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void Samm::sendCommand(String body) {
  (*_pSerial).print("<" + body + ">");
}
