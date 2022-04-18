#include <Arduino.h>
#include <DHT.h>
#define sensorLDR A0
int nilaiSensor;

#define DHTTYPE DHT11
#define RED_LED D5 
#define GREEN_LED D6 
#define BLUE_LED D7
#define triggerPin D3
#define echoPin D2

DHT dht(D1, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
   Serial.begin (115200);
   pinMode(triggerPin, OUTPUT);
   pinMode(echoPin, INPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
   pinMode(D0, OUTPUT);
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
   Serial.print(jarak);
   Serial.println(" cm");
   if(jarak == 1){
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(RED_LED, LOW); 
    Serial.println("LED biru menyala");
  }else if(jarak == 2){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW); 
    digitalWrite(BLUE_LED, LOW); 
    Serial.println("LED hijau menyala");
  }else if(jarak == 3){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(BLUE_LED, LOW); 
    Serial.println("LED merah menyala");
  }else{
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    Serial.println("LED menyala semua");
    delay(100);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW); 
  }
   delay(2000);
}