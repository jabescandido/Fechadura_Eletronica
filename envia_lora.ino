void envia_lora(String outgoing) {
  //int i = 0;
  //while (i < 6) {

    LoRa.beginPacket();                   // start packet
    LoRa.write(destination);              // add destination address
    LoRa.write(localAddress);             // add sender address
    LoRa.write(msgCount);                 // add message ID
    LoRa.write(outgoing.length());        // add payload length
    LoRa.print(outgoing);                 // add payload
    LoRa.endPacket();                     // finish packet and send it
    Serial.println("envinando mensagem para a tranca");
    Serial.println(outgoing);
  //  i ++;
  //}
}
