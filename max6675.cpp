// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

//#include <Wire.h>
#include <avr/pgmspace.h>
#include <WProgram.h>
#include <util/delay.h>
#include <stdlib.h>

#include "MAX6675.h"

MAX6675::MAX6675(int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;

  //define pin modes
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);

  digitalWrite(cs, HIGH);
}

float MAX6675::readCelsius(void) {

  uint16_t v;

  digitalWrite(cs, LOW);
  _delay_ms(1);

  v = spiread();
  v <<= 8;
  v |= spiread();

  v >>= 3;

  digitalWrite(cs, HIGH);

  return v*0.25;
}

float MAX6675::readFarenheit(void) {
  return readCelsius() * 9.0/5.0 + 32;
}

byte MAX6675::spiread(void) { 
  int i;
  byte d = 0;

  for (i=7; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    _delay_ms(1);
    if (digitalRead(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    digitalWrite(sclk, HIGH);
    _delay_ms(1);
  }

  return d;
}
