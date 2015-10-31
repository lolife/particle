// the ultrasonic sensor
const int sensor = D1;

// a stoplight comprised of 3 LEDs
const int redLED = D2;
const int yellowLED = D3;
const int greenLED = D4;

// the LED that we are currently flashing
int flashLED = redLED;
int delay_time=60;

// t-nought of our execution timer
unsigned long t0;

// Minimum time to wait between updates
const unsigned int execution_delay = 100;

// converts microseconds into cm
const float us2s = 0.01715;

// The last distance measurement,
// which is registered as a Particle variable on the Cloud
double  distance = 0.0,
        volume = 0.0,
// x-nought is our reference for zero
        x0=25.3134,
        slope=-85.8571,
        intercept=2126.47;

void setup() {
  t0 = millis();
  Particle.variable("distance", distance);
  Particle.variable("volume", volume);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  /*Serial.begin( 9600 ); //ignored, I'm told
  Serial.println( "ultra.ino : Printing to USB via serial." );
  Serial.printlnf( "%s\t%s\t%s", "t", "x", "V" );*/
}

void pulseOut(int s) {
  // Send pulse to ultrasonic sensor
  pinMode(s, OUTPUT);
  digitalWrite(s, HIGH);
  delay(1);
  digitalWrite(s, LOW);
}

void loop() {
  //Keep flashing our currently flashing LED
  digitalWrite(flashLED, LOW);
  delay(delay_time);

  //This is our execution timer. We get a new reading every
  if( millis() - t0 > execution_delay) {
    distance = read_distance(sensor);
    volume = (distance*slope)+intercept;
    if( volume < 1000) {
      flashLED = greenLED;
    }
    else if( volume < 1500) {
      flashLED = yellowLED;
    }
    else {
      flashLED = redLED;
    }
    delay_time = 1.0/distance*1000.0;
    /*Serial.printlnf( "%i\t%f\t%f", millis(), distance, volume );*/
    t0=millis();
  }
  digitalWrite(flashLED, HIGH);
  delay(delay_time);
}

float read_distance( int s) {
  // x=vt We get t from the sensor.
  // v is encapsulated in the us2s constant
  float x=0;
  unsigned long t;

  // Send pulse to ultrasonic sensor
  pulseOut(s);

  // Wait for pulse information from sensor
  pinMode(s, INPUT);
  t = pulseIn(s, HIGH);
  x = (float)t * us2s;
  return(x);
}
