
#define BLYNK_TEMPLATE_ID "TMPLxVAXxX0G"
#define BLYNK_TEMPLATE_NAME "AUTOMATION"
#define BLYNK_AUTH_TOKEN "NZv1loFwOnnEK-YLc6pdNWWOWuZjBTCq"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "vashika'lap";  // type your wifi name
char pass[] = "vashika@02";  // type your wifi password
int water;




BlynkTimer timer;


BLYNK_WRITE(V0)
{
  Serial.println("load 1");
 
 digitalWrite(D0, param.asInt());
}

BLYNK_WRITE(V1)
{
 
water=analogRead(A0);
Blynk.virtualWrite(V1,water );
}



void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  


  pinMode(D0, OUTPUT);
 


  delay(500);
}

void loop() {
  Blynk.run();
  timer.run();
}
