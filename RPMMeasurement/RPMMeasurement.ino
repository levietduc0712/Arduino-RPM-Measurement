#include<digitalWriteFast.h>

volatile unsigned int temp, temp2, counter = 0, rod = 0;
const unsigned long timeInterval = 200;  // Time interval in milliseconds
unsigned long previousMillis = 0;
const int resolution = 1000;

//Arduino Mega
//Back - Phase A - Pin2
//White - Phase B - Pin3
//Orange - Phase Z - Pin18

void setup(){
  Serial.begin (115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);

  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  attachInterrupt(5, ai2, RISING);

}

void loop(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= timeInterval) {
    // Calculate RPM
    float rpm = (float)counter / resolution / (float)(timeInterval / 60000.0);

    float delta = 1000.0 - rpm;
    
    // Display RPM
//    Serial.print("RPM: ");
    Serial.println(rpm);
//    Serial.print(" Counter: ");
//    Serial.print(counter);
//    Serial.print(" Round: ");
//    Serial.println(rod);

    // Reset counters
    counter = 0;
    rod = 0;
    previousMillis = currentMillis;
  }
}

void ai0(){
  if(digitalReadFast(3) == LOW){
    counter++; //CW
  }
}

void ai1(){
  if(digitalReadFast(2) == LOW){
    counter--; //CCW
  }
}

void ai2(){
  rod ++;
}
