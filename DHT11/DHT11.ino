/* 
 * ESP8266 NodeMCU DHT11 - Humidity Temperature Sensor Example
 * https://circuits4you.com
 * 
 * References
 * https://circuits4you.com/2017/12/31/nodemcu-pinout/
 * 
 */
 
#include "DHTesp.h"

#define DHTpin 14    //D5 of NodeMCU is GPIO14  for dht11

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  
  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);

  // use this instead: 
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
  //dht.setup(DHTpin, DHTesp::DHT22); //for DHT22 Connect DHT sensor to GPIO 17
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
 // Serial.print(dht.getStatusString());

  if(dht.getStatusString()=="OK"){
    Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t\n");
    
    }

  

  /*
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);

  */
}
