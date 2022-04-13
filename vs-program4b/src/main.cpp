#include <Arduino.h>
#define RED_LED D2
#define GREEN_LED D1
#define triggerPin D6
#define echoPin D5

void setup() {
   Serial.begin (115200);
   pinMode(GREEN_LED, OUTPUT);
   pinMode(RED_LED, OUTPUT);
   pinMode(triggerPin, OUTPUT);
   pinMode(echoPin, INPUT);
}

void jauh(){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
}
void dekat(){
    digitalWrite(RED_LED, LOW);
    for (int x = 0; x < 10; x++)
    {
        digitalWrite(GREEN_LED, HIGH);
        delay(10);
        digitalWrite(GREEN_LED, LOW);
        delay(10);
    }
}

void loop() {
   long duration, jarak;
   digitalWrite(triggerPin, LOW);
   delayMicroseconds(2);
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   jarak = duration * 0.034 / 2;
   if (jarak > 100)
   {
       jauh();
   }else{
       dekat(); 
   }
   Serial.print(jarak);
   Serial.println(" cm");
   delay(500);
}