//Connect with pin 18 and 19
#include <TinyGPS.h>
#include <OneWire.h>
#include <DallasTemperature.h>


//long   lat,lon; // create variable for latitude and longitude object
float lat,lon;
float Celsius = 0;
float Fahrenheit = 0;

TinyGPS gps; // create gps object

#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void setup(){
sensors.begin();
Serial.begin(57600); // connect serial
Serial.println("The GPS Received Signal:");
Serial1.begin(9600); // connect gps sensor

}
 
void loop(){
    sensors.requestTemperatures();

    Celsius = sensors.getTempCByIndex(0);
    
    Fahrenheit = sensors.toFahrenheit(Celsius);
  
    while(Serial1.available()){ // check for gps data
    if(gps.encode(Serial1.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude

    Serial.print("Position: ");
    
    //Genterate link
    Serial.print("www.google.com/maps/@");
    Serial.print(lat,6);
    Serial.print(",");
    Serial.println(lon,6);
     
    Serial.print(Celsius);
    Serial.print(" C  ");
    Serial.print(Fahrenheit);
    Serial.println(" F");

   }
  }
} 
