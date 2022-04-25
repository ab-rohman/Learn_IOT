#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT11
#define RED_LED D5 
#define GREEN_LED D6 
#define BLUE_LED D7
DHT dht(D3, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  dht.begin();
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.home();
}
void LED_Mati() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i = 0; i < lcdColumns; i++) {
    message = " " + message;
  }
  message = message + " ";
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void loop() {
  delay(2000);
//float h = dht.readHumidity();
  float c = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(c) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  LED_Mati();
  if (c > 25) {
    Serial.println("Kota berada pada suhu Panas ");
    Serial.println("Lampu LED Merah berkedip");
    for (int i = 0; i < 3; i++) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW); 
      digitalWrite(BLUE_LED, LOW); 
      delay(150);
      LED_Mati();
      delay(150);
    }
  } else if (c > 18) {
    Serial.println("Kota berada pada suhu Normal "); 
    Serial.println("Lampu LED biru berkedip");
    for (int i = 0; i < 3; i++) {
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(GREEN_LED, LOW); 
      digitalWrite(RED_LED, LOW); 
      delay(150);
      LED_Mati();
      delay(150);
    }
  }  else if (c < 18) {
    Serial.println("Kota berada pada suhu Dingin "); 
    Serial.println("Lampu LED Hijau berkedip");
    for (int i = 0; i < 3; i++) {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW); 
      digitalWrite(BLUE_LED, LOW);
      delay(150);
      LED_Mati();
      delay(150);
    }
  }else{
    Serial.println("Tidak terkategorikan"); 
  }
  lcd.home();
  lcd.print(c);
  lcd.print(" C ");
  lcd.print(f);
  lcd.print(" F ");
  scrollText(1, "26-04-2022 02:35", 200, 16);
}