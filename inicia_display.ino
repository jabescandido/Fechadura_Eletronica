void inicia_display() {

  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
 // delay(1500);
  Heltec.display->clear();
  Heltec.display->drawString(20, 0, "      GATEWAY");
  //Heltec.display->drawString(30, 25, "ELETRONICA");
  Heltec.display->drawString(20, 50, "    TCC - Jabes");
  Heltec.display->display();
 // delay(1000);
}
