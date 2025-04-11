#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#define LED D0
const char *ssid="vashika'lap";
const char *pass="vashikapooj";
const char* server ="api.thingspeak.com";
WiFiClient client;
unsigned long myChannelNumber=2349345;
const char * myWriteAPIKey= "J8PEEQP7UOQKL38J";
int B;
const int HEART=A0;

int heartBeat;
double alpha=0.75;
int period = 20;
double refresh=0.0;
float temperature_c;

void setup()
{
  heart_beat();
  Serial.println(heartBeat);
  pinMode(LED,OUTPUT);
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED)
  {
    digitalWrite(LED,1);
    delay(500);
    digitalWrite(LED,0);
    delay(500);
  }
  Serial.println("Wifi Connected");
  ThingSpeak.begin(client);
}
void loop()
{
  heart_beat();
  Serial.print(heartBeat);
  ThingSpeak.setField(1,heartBeat);
  ThingSpeak.setField(2,B);
  ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
  delay(15000);
  B++;
}
void heart_beat()
{
  static double oldValue=0;
  static double oldrefresh=0;
  int beat=analogRead(HEART);
  double value=alpha*oldValue+(0-alpha)*beat;
  refresh=value-oldValue;
  heartBeat=beat/10;
  oldValue=value;
  oldrefresh=refresh;
  delay(period*10);
  
}
