#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"


#define DHTPIN D2 
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


#define WIFI_SSID "CPE61_2G" 
#define WIFI_PASSWORD "61037029"


#define FIREBASE_HOST "humid-0001-default-rtdb.firebaseio.com"
#define FIREBASE_KEY "tJUMw6IP4yC7N5w69Iim4VOy2xHOrGXR2BkkPqaY" 

//OTA
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "CPE61_2G"
#define STAPSK  "61037029"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;


int Relay1 = D4;

FirebaseData firebaseData;

//wifimanager
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() 
{
    connectWifi();
    Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
    
//OTA
    Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }


  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
    delay(1000);
    
   float h = dht.readHumidity();
   
   if (isnan(h)>='60') 
   
  {
   digitalWrite(Relay1, HIGH);
  }
  
  else
  
  {
    
   digitalWrite(Relay1, LOW);
   
  }

  Serial.print("Humidity: ");  
  Serial.println(h);
  
    if(Firebase.set(firebaseData, "/DHT1/Humidity", h)) 
    
    {
        Serial.println("Added"); 
    } 
    else 
    
    {
        Serial.println("Error : " + firebaseData.errorReason());
    }
     
     ArduinoOTA.handle();
}

void connectWifi() {
    
}
