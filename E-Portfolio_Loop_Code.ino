#include <dht.h>
#include <SFE_BMP180.h>
#include <Wire.h>
dht DHT;
int i;
int j;
int k;
int l;
int m;
int n;
int o;
int p;
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
  float lux;
  float T;
  float H;
  float hindex;
  float moisture;
  float gasppm; 
  
  for(i = 0; i < 5; i++){  
  
  int hum = 0;
  int light = 0;
  int temp = 0;
  int HI = 0;
  int pres = 0;
  int gas = 0;
  int SM = 0;
  
  for(j = 0; j < 10; j++){
  light = light + analogRead(lightPin);
  delay(2.5);
  }
  float lux = light / 10;
  Serial.print("Light Intensity = ");
  Serial.print(lux);
  Serial.println(" lux");
  delay(1000);

  for(k = 0; k < 10; k++){
  temp = temp + analogRead(Tpin);
  delay(2.5);
  }
  float T = (temp / 10) * 0.4883;
  T = map(T,0,160,0,30);
  Serial.print("Temperature = ");
  Serial.print(T);
  Serial.println("*C");
  delay(1000);

  DHT.read11(DHTpin);
  for(l = 0; l < 10; l++){
  int RH = DHT.humidity;
  hum = hum + RH;
  delay(2.5);
  }
  float H = hum / 10;
  Serial.print("Humidity = ");
  Serial.print(H);
  Serial.println("%"); 
  delay(1000);

  for(m = 0; m < 10; m++){
  int heatIndex = {(-42.379 + 2.04901523*T + 10.14333127*H - .22475541*T*H - .00683783*T*T - .05481717*H*H + .00122874*T*T*H + .00085282*T*H*H - .00000199*T*T*H*H - 32) *5/9};
  HI = HI + heatIndex;
  delay(2.5);
  }
  float hindex = HI / 10;
  Serial.print("Heat Index = ");
  Serial.print(hindex);
  Serial.println("*F");
  delay(1000);

  for(n = 0; n < 10; n++){
  SM = SM + analogRead(soilPin);
  delay(2.5);
  }
  float moisture = SM / 10;
  moisture = map(moisture,2048,10,0,100);
  Serial.print("Soil Moisture = ");
  Serial.print(moisture);
  Serial.println("%");
  delay(1000);

  for(o = 0; o < 10; o++){
  gas = gas + analogRead(gasPin);
  delay(2.5);
  }
  float gasppm = gas / 10;
  Serial.print("CO2 concentration = ");
  Serial.print(gasppm);
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
  
  delay(3000);
  Serial.println("\n");
  }
    
  if(lux < 170 && T > 30){
  Serial.println("\n");
  Serial.println("You would need to water your plant at 4 hour intervals.");
  Serial.println("\n"); 
  }
  delay(10000); 
}
