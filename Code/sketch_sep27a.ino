#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define trigger D1 
#define echo    D2 

long level; 


char auth[] = "R6qyEFQdnZdQZyxtC3Nuqreet6A9ml_s";
char ssid[] = "wasanfern";
char pass[] = "2317012345";


void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode( trigger, OUTPUT );
  pinMode( echo   , INPUT );
  Blynk.begin(auth, ssid, pass);
 
}

void loop() {
  digitalWrite( trigger , LOW );   
  digitalWrite( trigger , HIGH );    
  digitalWrite( trigger , LOW );
  long duration = pulseIn( echo, HIGH , 10000 ); 
  level = 0.034 * duration / 2;
  Blynk.virtualWrite(V1, level);  
  Blynk.run();
}
