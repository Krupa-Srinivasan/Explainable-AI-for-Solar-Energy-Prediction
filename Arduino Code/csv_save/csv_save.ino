#include <WiFi.h>
#include <SD.h> // Include the SD library

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

File dataFile; // Declare a file object

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
  
  // Initialize the SD card
  if (!SD.begin()) {
    Serial.println("SD card initialization failed!");
    return;
  }
  
  // Create a file on the SD card
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error opening data.csv");
    return;
  }
  
  // Write headers to the CSV file
  dataFile.println("Solar Voltage,VIN,Temperature,Luminosity");
  
  dataFile.close();
}

void loop() {
  int temp_adc_val;
  float temp_val;
  float tempF;
  temp_adc_val = analogRead(lm35_pin);
  temp_val = (temp_adc_val * 4.88);    
  temp_val = (temp_val / 10);         
  tempF = temp_val * 9 / 5 + 32;

  Serial.print("Temperature = ");
  Serial.println(tempF);
  delay(500);

  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 3724.0;
  vIN = vOUT / (R2 / (R1 + R2));

  int sensorValue = analogRead(33);
  /*Vout = (sensorValue * 0.0048828125);
  RLDR = (10000.0 * (3 - Vout)) / Vout;
  Lux = (RLDR / 500);*/

  Serial.print("L: ");
  Serial.println(sensorValue);
  delay(500);

  Serial.print("Solar Volt: ");
  Serial.println(vIN);

  // Append data to the CSV file
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(vIN);
    dataFile.print(",");
    dataFile.print(temp_val);
    dataFile.print(",");
    dataFile.print(sensorValue);
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv for writing");
  }

  Serial.println("Data saved to data.csv");

  delay(5000); // Delay for 5 seconds before saving the next data
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
