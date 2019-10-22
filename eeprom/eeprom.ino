#include <ESP8266WiFi.h>

const char* SSID = "R360"; //MAX 32
const char* PASSWORD = "HFDYUK64323246"; //MAX 32

#include <EEPROM.h>

void setup() {
  Serial.begin(9600);

  EEPROM_ESP8266_GRABAR(SSID, 0); //Primero de 0 al 32, del 32 al 64, etc
  EEPROM_ESP8266_GRABAR(PASSWORD, 32); //SAVE

  Serial.println();
  Serial.println(EEPROM_ESP8266_LEER(0, 32));//Primero de 0 al 32, del 32 al 64, etc
  Serial.println(EEPROM_ESP8266_LEER(32, 64));

 // WiFi.begin(EEPROM_ESP8266_LEER(0,32).c_str(), EEPROM_ESP8266_LEER(32,64).c_str());

}

void EEPROM_ESP8266_GRABAR(String buffer, int N) {
  EEPROM.begin(512); delay(10);
  for (int L = 0; L < 32; ++L) {
    EEPROM.write(N + L, buffer[L]);
  }
  EEPROM.commit();

 

}
//
void loop() {}
//

//
String EEPROM_ESP8266_LEER(int min, int max) {
  EEPROM.begin(512); delay(10); String buffer;
  for (int L = min; L < max; ++L)
    if (isAlphaNumeric(EEPROM.read(L)))
      buffer += char(EEPROM.read(L));
  return buffer;
}
