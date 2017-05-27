#include <ESP8266WiFi.h>;
#include <ESP8266HTTPClient.h>;

const char* MY_SSID = "Live with Walkman_874b";
const char* MY_PWD =  "55555555";

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
}

void loop() {
      WiFiClient client;
      HTTPClient http;
      http.begin("http://meteor-workspace-beaurulez.c9users.io/api/temp");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      http.POST("temp=25&token=65beb48699b1e32986c50ee01fc1f4d3a0343f133cfff657b584863035bb14d3");
      http.writeToStream(&Serial);
      Serial.println();
      http.end();
  /*float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("temperature : ");
  Serial.println(t);
  Serial.print("humidity : ");
  Serial.println(h);*/
  delay(3000);
}
