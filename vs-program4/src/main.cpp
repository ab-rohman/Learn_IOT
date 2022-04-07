#include <Arduino.h>
int nilaiSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("contoh penggunaan Sensor LDR");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  nilaiSensor = analogRead(A0);
  Serial.print("Nilai Sensor : ");
  Serial.println(nilaiSensor);
  delay(1000);
}