void onReceive(int packetSize)
{
  //Serial.println("entrando no onReceive");
  if (packetSize == 0) return;          // Se não há pacote, retorne

  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  String incoming = "";
  //Serial.println("dentro do recebe lora");
  while (LoRa.available())
  {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length())
  { // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("Desconsiderando Mensagem.");
    return;
  }
  /*
    // if message is for this device, or broadcast, print details:
    Serial.println("Received from: 0x" + String(sender, HEX));
    Serial.println("Sent to: 0x" + String(recipient, HEX));
    Serial.println("Message ID: " + String(incomingMsgId));
    Serial.println("Message length: " + String(incomingLength));
    Serial.println("Message: " + incoming);
    Serial.println("RSSI: " + String(LoRa.packetRssi()));
    Serial.println("Snr: " + String(LoRa.packetSnr()));
    Serial.println();
  */
  // Serial.println(incoming.toInt());
  if (incoming.toInt() == 0) {
    Heltec.display->clear();
    Heltec.display->drawString(15, 25, "ACESSO NEGADO");
    Heltec.display->display();
    delay(2000);
    inicia_display();
  }
  if (incoming.toInt() == 1) {
    Heltec.display->clear();
    Heltec.display->drawString(5, 30, "ACESSO AUTORIZADO");
    Heltec.display->display();
    t2 = millis();
    digitalWrite(17, HIGH);
    delay(2000);
    digitalWrite(17, LOW);
    delay(2000);
    inicia_display();
  }
  if (incoming.toInt() == 2) {
    Heltec.display->clear();
    Heltec.display->drawString(15, 15, "EVACUEM !!");
    digitalWrite(17, HIGH);
    Heltec.display->display();
    t2 = millis();
    delay(2000);
    inicia_display();
  }
   if (incoming.toInt() == 3) {
    Heltec.display->clear();
    digitalWrite(17, LOW);
    t2 = millis();
    delay(2000);
    inicia_display();
  }

  /* int numero = atoi.char* (incoming);
    Serial.println(numero);
    int resultado = numero +1;
    Serial.println(resultado);
  */
  
  tt = t2 - t1;
  Serial.println("Tempo total para abertura da tranca: ");
  Serial.println(tt);
}







/*
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    packet = "";
    packSize = String(packetSize, DEC);
    for (int i = 0; i < packetSize; i++) {
      packet += (char) LoRa.read();
    }
    rssi = String(LoRa.packetRssi(), DEC);  //rssi é a resposta preciso descobrir como a rsposta vem. ------------------------------------------
    Serial.println(rssi);
    Serial.println("resposta");
    //      aux == 1;
  }
  Serial.println("Esperando resposta");

  // aux == 0; //reseta a condição do loop    // comentado para uso na funcao teste

  if (rssi == "1")  //Autoriza acesso
  {
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->clear();
    Heltec.display->display();
    Heltec.display->drawString(40, 25, "AUTORIZADO");
    Heltec.display->display();
    Serial.println("Libera acesso");
    digitalWrite(17, HIGH);
    delay(2000);
    digitalWrite(17, LOW);
  }

  if (rssi == "0") //Nega acesso
  {
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->clear();
    Heltec.display->display();
    Heltec.display->drawString(40, 25, "NEGADO");
    Heltec.display->display();
    delay(3000);
  }
  }
*/
