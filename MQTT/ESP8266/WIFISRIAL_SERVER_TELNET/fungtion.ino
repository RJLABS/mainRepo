void subProses(){
  if(incomingData == "ledOn"){
     digitalWrite(BUILTIN_LED2, HIGH);
     serverClient.print("LED OFF");
  }
  else if(incomingData == "ledOff"){
    digitalWrite(BUILTIN_LED2, LOW);
    serverClient.print("LED ON");
  }
  else if(incomingData == "temp"){
    serverClient.print("30,5");
  }
  }
  

