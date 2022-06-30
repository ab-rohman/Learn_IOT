//LED setup
//#define LED D3
//Servo Setup
#include <Servo.h>
Servo myservo;  
int sudutON= 90;
int sudutOFF= 0;

//HC-SR Setup
#define trigPin D6
#define echoPin D5

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

#define MQTT_USER "jti"
#define MQTT_PASSWORD "1"

long duration;
float distanceCm;
float distanceInch;

//LCS-I2C setup
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//wifi setup
//#include <WiFi.h>
#include <ESP8266WiFi.h>  
String macAddr = "";

//PubSub / Broker setup
#include <PubSubClient.h>

// const char *mqtt_server = "broker.emqx.io";
// const char *topic = "esp32/1941720023/ana_test";
// const char *mqtt_username = "emqx";
// const char *mqtt_password = "public";
// const int mqtt_port = 1883;

const char *topic = "esp32/1941720023/ana_result";
const char *topic_result = "esp32/1941720023/ana_test";
const int mqtt_port = 1883;
const char *ssid = "JTI-POLINEMA";
const char *password = "jtifast!";

IPAddress server(140, 238, 201, 233);

WiFiClient espClient;
PubSubClient client(espClient);

//var project
String pesan = "Reconnecting";
String blanker = "            ";
//unsigned int
void callback(char* topic_result, byte* payload, int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  pesan = response;

  // Send data
  Serial.print("Message sent [");
  Serial.print(topic_result);
  Serial.print("] ");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
  Serial.println();

  // Receive data
  Serial.print("Message received [");
  Serial.print(topic_result);
  Serial.print("] ");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
  Serial.println();
  // Serial.println(set_temp);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //LED Setup
  //pinMode(LED, OUTPUT);
  //Servo Setup
  myservo.attach(D4);

  //hcsr setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //lcd setup
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();

  //starting Wifi/internet connection
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Wifi Connected!");
  Serial.print("Running on ip: ");
  Serial.println(WiFi.localIP());
  macAddr = WiFi.macAddress();
  Serial.println(macAddr);

  //mqtt setup
  ////Setting client ID
  client.setSocketTimeout(600);
  client.setKeepAlive(50);
  // client.setServer(mqtt_server, 1883);
  client.setServer(server, 1883);
  client.setCallback(callback);
  client.subscribe(topic);
  client.subscribe(topic_result);
}

void hcsr(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  distanceInch = distanceCm * CM_TO_INCH;
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(macAddr.c_str(), MQTT_USER, MQTT_PASSWORD))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      client.connect(macAddr.c_str(), MQTT_USER, MQTT_PASSWORD);
      delay(1000);
    }
  }
}

void loop() {
  hcsr();
  // Prints the distance in the LCD
  lcd.setCursor(0, 0);
  if(distanceCm <= 100){
    //digitalWrite(LED, HIGH);
    myservo.write(sudutON);
    lcd.print("Ada tamu" + blanker);
  }else{
    //digitalWrite(LED, LOW);
    myservo.write(sudutOFF);
    lcd.print("       --" + blanker);
  };
  lcd.setCursor(0,1);
  lcd.print(String(client.subscribe(topic_result)) + blanker);
  if(client.subscribe(topic_result)){
    lcd.print("message dari nabil" + blanker);
  }

  //cek koneksi
  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
  {
    client.connect(macAddr.c_str(), MQTT_USER, MQTT_PASSWORD);
  }

  static char distTemp[7];
  dtostrf(distanceCm, 4, 2, distTemp);
  client.publish(topic_result, distTemp);
  client.subscribe(topic);
  client.subscribe(topic_result);
  delay(1000);
}


void scrollText(int row, String message, int delayTime, int lcdColumns)
 {
   for (int i = 0; i < lcdColumns; i++)
   {
     message = " " + message;
   }
   message = message + " ";
   for (int pos = 0; pos < message.length(); pos++)
   {
     lcd.setCursor(0, row);
     lcd.print(message.substring(pos, pos + lcdColumns));
     delay(delayTime);
   }
 }



