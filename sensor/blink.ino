//int delay_time = 5;
//int led1 = D0;
//int led2 = D7;
int sensor = A0;
int sensor_avg;
const int char_buf_size = 64;
char buf[char_buf_size];
unsigned long t0;

int init_sensor(int s);

void setup() {
  t0 = millis();

  init_buf(buf);
  Serial.begin(9600); //ignored, I'm told
  sprintf( buf, "t=%0.3f : %s", (float)(millis()-t0)/1000.0, "Printing to USB via serial." );
  Serial.write( buf );

  init_buf(buf);
  pinMode(sensor, INPUT);
  sensor_avg = init_sensor(sensor);
  sprintf( buf, "%i", sensor_avg);
  log_msg(buf);
}

void loop() {
  if( millis()-t0 < 60000 ) {
    // Read sensor value, format it and log it
    int value =  analogRead(sensor) - sensor_avg;
    sprintf( buf, "%0.3f %i", (float)(millis()-t0)/1000.0, value );
    log_msg(buf);
//    delay(delay_time);
  }
  else {
    log_msg("Execution complete. Grab your data, we're going to sleep until more data comes in or for 15 seconds.");
    delay(1000);
    System.sleep(A0, CHANGE, 15);
//    System.sleep(SLEEP_MODE_DEEP, 30);
    t0 = millis();
    sensor_avg = init_sensor(sensor);
  }
}

void init_buf(char* char_buffer) {
  for( int x=0; x<char_buf_size; ++x) {
    char_buffer[x]=0;
  }
}

int init_sensor(int s) {
  long sum=0;
  for( int x=0; x<1000; ++x) {
    sum += (long)analogRead(s);
  }
  return((int)((float)sum*0.001));
}

void log_msg(char* msg) {
  Serial.println(msg);
}
