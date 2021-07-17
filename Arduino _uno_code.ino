#include <Arduino.h>
#include <TinyGPS.h>
#include <TimerOne.h>
#include <Wire.h>
#include <dht.h>
#include <SoftwareSerial.h>
#include "MAX30100_PulseOximeter.h"

#define TempHumSensorIn 8

int RXPin = 4;
int TXPin = 5;
TinyGPS gps;
SoftwareSerial gpsSerial(RXPin, TXPin);
float lat = 27.68, lon = 85.39;
//float lat = 0, lon = 0;

void ServerSendData();
void gpsData();

dht DHT;
PulseOximeter pulseOxySensor;


void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(9600);
  if (!pulseOxySensor.begin())
  {
    Serial.println("Pulse Oxymeter failed to initialize");
    while (true);
  }

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(ServerSendData);
}

void gpsData(){
 while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      gps.f_get_position(&lat, &lon);
    }
  }
  
}

void loop()
{
  pulseOxySensor.update();
  DHT.read11(TempHumSensorIn);
  gpsData();

}

void ServerSendData()
{
  
  String message ="";

  message = message + "{\"latitude\": ";
  message = message + String(lat);
  message = message + ", \"longitude\": ";
  message = message + String(lon);

  message = message + ", \"humidity\": ";
  message = message + String(DHT.humidity);
  message = message + ", \"temperature\": ";
  message = message + String(DHT.temperature);

  message = message + ", \"Heartbeat\": ";
  message = message + String(pulseOxySensor.getHeartRate());
  message = message + ", \"Spotwo\": ";
  message = message +  String(pulseOxySensor.getSpO2());
  message = message + "}";
   
  
  Serial.println(message);

}
