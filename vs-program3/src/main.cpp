#include <Arduino.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define RED_LED D5 
#define GREEN_LED D6 
#define BLUE_LED D7

DHT dht(D1, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  Serial.println("Menggunakan DHT11 untuk menyalakan lampu");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = dht.readHumidity();
  float c = dht.readTemperature();
  float f = dht.readTemperature(true);

  float k = (f + 459.67) * 5/9;
  float r = c * 4 / 5;

  if (isnan(h) || isnan(c) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(c, h, false);

  if ( c > 25 )
  {
    digitalWrite(RED_LED, HIGH); 
    Serial.println("Kota berada pada suhu Panas "); 
    delay(1000); 
  } else if ( c > 19)
  {
    digitalWrite(BLUE_LED, HIGH); 
    Serial.println("Kota berada pada suhu Normal "); 
    delay(1000);  
  } else { 
    digitalWrite(GREEN_LED, HIGH); 
    Serial.println("Kota berada pada suhu Dingin "); 
    delay(1000); 
  }
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(c);
  Serial.print(F("°C "));
  Serial.print(r);
  Serial.print(F("°R "));
  Serial.print(k);
  Serial.print(F("°K "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  digitalWrite(GREEN_LED, LOW); 
  digitalWrite(BLUE_LED, LOW); 
  digitalWrite(RED_LED, LOW); 
}