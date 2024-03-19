#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* ssid = "Rohit_2G";
const char* password =  "******";
String url = "https://rohitdasamantharao.com/api/iot/getbulbstatus";

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting");

  //Waiting for the connection to be established....
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //print connection details
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    //Creating a wifi client and seting to insecure for now.
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String fullUrl = url;

    //Send a GET Request to url 
    Serial.println("Requesting " + fullUrl);
    if (https.begin(client, fullUrl)) {
      int httpCode = https.GET();
      Serial.println("============== Response code: " + String(httpCode));
      if (httpCode > 0) {
        Serial.println(https.getString());
        String json = https.getString();
        StaticJsonDocument<200> doc;

        //Deserialize the Json resoponse using ArduinoJson.h functions
        deserializeJson(doc, json);
        String value = doc["bulbStatus"];
        Serial.println(value);
        if(value == "true")
          digitalWrite(2, HIGH);
        else
          digitalWrite(2, LOW);
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  delay(500);
}