/*-----------DEFINIÇÕES------------------*/

#include "heltec.h"
#include "FS.h"
#include <WiFi.h>
#include "FirebaseESP32.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#define FIREBASE_HOST "tranca-96436.firebaseio.com"
#define FIREBASE_AUTH "qmlVBkkLqHbU0q0VktM6OKUEOeLp6oBWOUnG3s76"
#define WIFI_SSID "VIVOFIBRA-D570"
#define WIFI_PASSWORD "84435FDBD1"
#define BAND    920E6  //you can set band here directly,e.g. 868E6,915E6

/*----------VARIÁVEIS-------------------*/
unsigned long t1;
unsigned long t2;
unsigned long tt;


String rssi = "RSSI --";
String packSize = "--";
String packet ;

FirebaseData firebaseData;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "b.st1.ntp.br", 3600, 60000);


//gateway:
byte localAddress = 0xBF;     // address of this device
byte destination = 0xBB;      // destination to send to
byte msgCount = 0;            // contagem de mensagens enviadas
long lastSendTime = 0;        // tempo do ultimo envio
int interval = 2000;          // interval between sends

void inicia_display();
void onReceive(int packetSize);


void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  inicia_display();
  LoRa.receive();
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  // Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, 0, "CONECTANDO ");
  Heltec.display->display();
  delay(2000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectado al Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Conectado con IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  inicia_display();
  timeClient.begin();
}

void loop() {

  onReceive(LoRa.parsePacket());
  //Serial.println("dentro do loop");
  //código original
  /*
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
    cbk(packetSize);
    }
    delay(10);
  */
}
