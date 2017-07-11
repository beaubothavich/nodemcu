#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

const char* MY_SSID = "Live with Walkman_874b";
const char* MY_PWD =  "55555555";
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");
  while (WiFi.status() != WL_CONNECTED){
      delay(1000);
      Serial.print(".");
  }
  Serial.println("wl connected");
  Serial.println("");
  Serial.println("WIFI connected\n ");
  Serial.println("");
  sensors.begin();
}

void loop() {
      Serial.print(" Requesting temperatures...");
      sensors.requestTemperatures();
      Serial.println("DONE");
      Serial.print("Temperature for Device 1 is: ");
      float temp = sensors.getTempCByIndex(0);
      Serial.print(temp);

      char tempoutstr[25] = "temp=";
      String token = "&token=65beb48699b1e32986c50ee01fc1f4d3a0343f133cfff657b584863035bb14d3";
      String ref = "&ref=1";
      dtostrf(temp, 4, 2, &tempoutstr[5]);
           
      http.begin("http://medmo.herokuapp.com/api/temp");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      http.POST(tempoutstr+token+ref);
      http.writeToStream(&Serial);
      Serial.println();
      http.end();
  delay(3000);
}
