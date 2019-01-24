#include "dht.h"
#include <SFE_BMP180.h>
#include <Wire.h>
dht DHT;
int i;
const int DHTpin = 7;
const int lightPin = A0;
const int Tpin = A1;
const int soilPin = A2;
const int gasPin = A3;
SFE_BMP180 barosensor;

void setup() {
  Serial.begin(9600);
  barosensor.begin();
}

void loop() {
  int lux;
  
  for(i = 0; i < 5; i++){  
  
  int chk = DHT.read11(DHTpin);
  int RH = DHT.humidity;
  Serial.print("Humidity = ");
  Serial.print(RH);
  Serial.println("%"); 
  delay(1000);
  
  int lux = analogRead(lightPin);
  Serial.print("Light Intensity = ");
  Serial.print(lux);
  Serial.println(" lux");
  delay(1000);

  int T = analogRead(Tpin);
  T = T * 0.4883;
  T = map(T,0,160,0,30);
  Serial.print("Temperature = ");
  Serial.print(T);
  Serial.println("*C");
  delay(1000);

  int heatIndex = {(-42.379 + 2.04901523*T + 10.14333127*RH - .22475541*T*RH - .00683783*T*T - .05481717*RH*RH + .00122874*T*T*RH + .00085282*T*RH*RH - .00000199*T*T*RH*RH - 32) *5/9};
  Serial.print("Heat Index = ");
  Serial.print(heatIndex);
  Serial.println("*F");
  delay(1000);

  int moisture = analogRead(soilPin);
  moisture = map(moisture,2048,10,0,100);
  Serial.print("Soil Moisture = ");
  Serial.print(moisture, 1);
  Serial.println("%");
  delay(1000);

  int gasppm = analogRead(gasPin);
  Serial.print("CO2 concentration = ");
  Serial.print(gasppm, DEC);
  Serial.println(" ppm");
  delay(1000);

  char status; 
  double P, tp;

  status = barosensor.startTemperature();
  if (status != 0) {
      status = barosensor.getTemperature(tp);

    if (status != 0) {
      status = barosensor.startPressure(1);

      if (status != 0) {
      status = barosensor.getPressure(P, tp);

        if (status != 0) {        
          Serial.print("Pressure: ");
          Serial.print(P);
          Serial.println(" hPa");
        }
      }
    }
  }
   }
   delay(3000);
  if(lux < 170){
    Serial.println("\n");
    Serial.println("This probably is not a good place to plant it");
    Serial.println("\n");
  }
 // else if(bluetooth.serialRead) 
   
   delay(10000); 
}
