# samm-arduino-library
This Arduino Library allow to integrate Digital and Analog inputs, and digital outputs with the platform sammgps.com

## How to Install
Download the `Samm.cpp` and `Samm.h` files.
Go to your arduino folder and create this scheme

```
- Samm
|  - Samm.cpp
|  - Samm.h
```

## How to use
```c
#include <SoftwareSerial.h>
#include <Samm.h>

SoftwareSerial sammSerial(2, 3); // RX, TX
Samm samm;

unsigned long timeNow = 0;

void setup()
{
  // Initialize all pins that can be used as outputs
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize serial for Samm Library
  sammSerial.begin(9600);
  // Pass serial instance as parameter
  samm.begin(&sammSerial);

  // Only for test porpuses
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
}

void loop()
{

  samm.setDigitalInput(0, LOW);
  samm.setDigitalInput(7, HIGH);
  samm.setDigitalInput(8, HIGH);
  samm.setDigitalInput(10, HIGH);
  samm.setAnalogInput(0, 255);
  samm.setAnalogInput(2, 0);
  samm.setAnalogInput(4, 101);
  samm.analyze();

  if (millis() > timeNow + 10000){
    timeNow = millis();
    samm.report();
  }
}

