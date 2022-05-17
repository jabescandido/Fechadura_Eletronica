/*-------------FIREBASE-------------------*/

void confirma_firebase(String valor, int endereco) {
  t1 = millis();
  Serial.println("confirmando firebase");
  Serial.println("valor recebido: " + valor);
  Serial.println("endereço recebido " + String (endereco, HEX));
  Serial.println(endereco);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->display();
  Heltec.display->drawString(40, 25, "AGUARDE");
  Heltec.display->display();
  Serial.print("Valor recebido pela tranca: ");
  Serial.println(valor);
  Serial.print( "valor recebido em endereço: ");
  Serial.println(endereco);
  String rota;
  if (endereco == 187) {                //definir um if com uma identificação para cada nova tranca no sistema.
    rota = "Tags/tranca_posicao/187";
  }
  Firebase.getString(firebaseData, rota + "/" +  valor);
  String texto2 = firebaseData.stringData();
  Serial.println(texto2);
  int tam2 = texto2.length();
  Serial.print("Tamanho do arquivo");
  Serial.println(tam2);
  //se o tamanho do arquivo retornado for diferente de 0, então tem na base de dados e deve ser liberado o acesso.
  if (tam2 != 0) {
    Serial.println("Libera acesso");
    envia_lora("1"); //permite acesso
   // delay(2000);
    inicia_display();
    timeClient.update();
    String horario =  timeClient.getFormattedTime();
    String rota_acessos = "acessos";
    String identificacao = "/";
    identificacao += horario;
    Firebase.setString(firebaseData, rota_acessos + identificacao, valor);

  } else {
    Serial.println("Nega acesso");
    envia_lora("0"); //nega acesso
    // delay(2000);
    inicia_display();
  }
  t2 = millis();
  tt= t2 - t1;
  Serial.println("tempo em mili segundos para confirmação completa");
  Serial.println(tt);
}
