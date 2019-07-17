#include "config.h";

#define PIR D6
#define SENSOR_DELAY 1000

// sketch starts assuming no motion is detected
int pirState = LOW;
int pirRead = 0;

AdafruitIO_Feed *pir = io.feed("pir");

void setup() {
  // put your setup code here, to run once:

  pinMode(PIR, INPUT);
  Serial.begin(115200);
  while(!Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  // put your main code here, to run repeatedly:
  io.run();

  Serial.println("Leer sensor PIR");
  readPIR();

}

void readPIR() {
  // check if motion is detected
  pirRead = digitalRead(PIR);
  if (pirRead == HIGH) {
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("* Motion detected!");
      pir->save(1);
      pirState = HIGH;
    }
  } 
  else {
    if (pirState == HIGH) {
      Serial.println("* Motion ended.");
      pir->save(0);
      pirState = LOW;
    }
  }
  delay(SENSOR_DELAY);
}
