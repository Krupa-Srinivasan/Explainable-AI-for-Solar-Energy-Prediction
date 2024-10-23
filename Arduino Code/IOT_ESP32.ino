
#include <WiFi.h>
#include "DHTesp.h"
#define DHTpin 15

DHTesp dht;
const int lm35_pin = 35;
const int voltageSensor = 32;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;
float RLDR;
float Vout;
float Lux;
String apiKey = "H46HICXGTGKHF2G4";
const char* ssid = "Kiyoo"; 
const char* pass = "d59i9xkv"; 
const char* server = "api.thingspeak.com";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  pinMode(33,INPUT);
  dht.setup(DHTpin, DHTesp::DHT11);
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 3724.0;
  vIN = vOUT / (R2 / (R1 + R2));

  // Read LDR sensor twice with delay
  analogRead(33); // Discard first reading
  int sensorValue = analogRead(33);
  /*Vout = (sensorValue * 0.0048828125);
  RLDR = (10000.0 * (3 - Vout)) / Vout;
  Lux = (RLDR / 500);*/

  Serial.print("L: ");
  Serial.println(sensorValue);
  delay(100); // Delay for ADC to settle

  Serial.print("Solar Volt: ");
  Serial.println(vIN);

  delay(500); 
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(vIN);
    postStr += "&field2=";
    postStr += String(temperature);
    postStr += "&field3=";
    postStr += String(humidity);
    postStr += "&field4=";
    postStr += String(sensorValue);
    postStr += "\r\n\r\n\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    delay(100);
    client.print("Host: api.thingspeak.com\n");
    delay(100);
    client.print("Connection: close\n");
    delay(100);
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    delay(100);
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    delay(100);
    client.print("Content-Length: ");
    delay(100);
    client.print(postStr.length());
    delay(100);
    client.print("\n\n");
    delay(100);
    client.print(postStr);
    delay(100);
  }
  client.stop();
  Serial.println("Sending....");
  delay(500);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
