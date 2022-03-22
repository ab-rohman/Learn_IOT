#include <Arduino.h>

#define RED_LED D5   //led warna merah
#define GREEN_LED D6 //led warna hijau
#define BOARD_LED1 D0 //led pada GPIO 16
#define BOARD_LED2 D4 //led pada GPIO 2
#define BLUE_LED D7  //led warnah biru

void setup()
{
  Serial.begin(115200);
  pinMode(GREEN_LED, OUTPUT); //atur pin-pin digital sebagai output
  pinMode(BOARD_LED1, OUTPUT); //atur pin-pin digital sebagai output
  pinMode(BOARD_LED2, OUTPUT); //atur pin-pin digital sebagai output
  Serial.println("Contoh Program LED SOS");
}

void loop()
{
  // 3 dits (3 titik atau huruf S)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(GREEN_LED, HIGH); // LED nyala
    delay(150);                  // delay selama 150ms
    digitalWrite(GREEN_LED, LOW); // LED mati
    delay(100);                  // delay selama 100ms
  }
  delay(100);

  // 3 dahs (3 garis atau huruf O)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(BOARD_LED1, HIGH); // LED nyala
    delay(400);                  // delay selama 400ms
    digitalWrite(BOARD_LED1, LOW); // LED mati
    delay(100);                  // delay selama 100ms
  }

  // 100ms delay to cause slight gap between letters
  delay(100);
  // 3 dits again (3 titik atau huruf S)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(BOARD_LED2, HIGH); // LED nyala
    delay(150);                  // delay selama 150ms
    digitalWrite(BOARD_LED2, LOW); // LED mati
    delay(100);                  // delay selama 100ms
  }

  // wait 5 seconds before repeating the SOS signal
  delay(5000);
}