#include "FS.h"
#include "heltec.h"
#include "MFRC522.h"
#include "FirebaseESP32.h"
#define RFID_SDA 12
#define RFID_SCK 5
#define RFID_MOSI 27
#define RFID_MISO 19
#define RFID_RST 13
#define BAND    920E6


void inicia_display();
void  recebe_lora();


MFRC522 mfrc522(RFID_SDA, RFID_RST);
uint8_t successRead;
byte readCard[4];
unsigned int counter = 0;

unsigned long t1;
unsigned long t2;
unsigned long tt;

String rssi = "";
String packSize = "";
String packet ;
String outgoing;
void confirma(String);

//tranca:
byte localAddress = 0xBB;     // endereço desta tranca
byte destination = 0xBF;      // endereço do gateway

byte msgCount = 0;            // contagem de mensagens enviadas
long lastSendTime = 0;        // tempo da última mensagem enviada
int interval = 2000;          // intervalo entre os envios


void setup()
{
  pinMode(17, OUTPUT);
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  mfrc522.PCD_Init();
  inicia_display();
  LoRa.receive();
}

void loop()
{
  //código original
  do {
    onReceive(LoRa.parsePacket());
    successRead = getID();
    //delay(700);
  }
  while (!successRead);
}
