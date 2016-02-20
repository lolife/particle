#include "math.h"
// the audio output
const int audio_out = A0;
const float pi = 3.1415926;
const float f = 1000.0;
unsigned long t0;

void setup() {
  t0 = millis();
  pinMode(audio_out, OUTPUT);

  Serial.begin( 9600 ); //ignored, I'm told
  Serial.println( "a2d.ino : Printing to USB via serial." );
  Serial.printlnf( "t0 = %i", t0 );
}


void loop() {
  int n;

  while( (millis()-t0) < 10000 ) {
    /* Scale to 0 – 255 for analog output */
    n = (int)((127.0 * sin( 2.0 * pi * f * (millis()-t0)/1000 ))+127.0);
    Serial.printlnf( "%i\t%i", (millis()-t0)/1000, n );
    analogWrite(audio_out, n );
//    delay(10);
  }
  delay(5000);
  t0 = millis();
}
