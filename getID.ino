
uint8_t getID() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) { // If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   // Since a PICC placed get Serial and continue
    return 0;
  }
  String valor;                             // Valor que é lido da TAG RFID
  t1 = millis();
  char * chave;
  for ( uint8_t i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    valor += String(readCard[i]);
    Serial.print(readCard[i]);
  }
  mfrc522.PICC_HaltA();
  envia_lora(valor);
  Serial.println("enviando para gateway");
  //Serial.println(valor);

  // delay(2000);

  Heltec.display->clear();
  Heltec.display->display();
  // Heltec.display->drawString(50, 0, "TRANCA");
  Heltec.display->drawString(40, 25, "AGUARDE");
  //Heltec.display->drawString(30, 50, "TCC JABES");
  Heltec.display->display();

  return 1;
}



////////////////////////////////////////////////////////////////////////
