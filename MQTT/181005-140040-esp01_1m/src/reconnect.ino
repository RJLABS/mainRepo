// Connect to WiFi
void con2WiFi(){
  IPAddress ip(ipd1,ipd2,ipd3,ipd4);
  IPAddress subnet(sub1,sub2,sub3,sub4);
  IPAddress gateway(gat1,gat2,gat3,gat4);
  /*dihapus pada rev2 karena hanya untuk debug
  // Connect to WiFi network
  Serial.println("Connecting to AP ");
  //delay(5000); dihapus pada rev1
  Serial.print("SSID Name : ");
  Serial.println(ssid);
  Serial.print("SSID Pass : ");
  Serial.println(password);
  //delay(250); diubah menjadi 50 pada rev 1
  //delay(50); diubah menjadi 1 pada rev2
  */
  
  delay(10);
  //set static ip
  WiFi.config(ip,gateway,subnet);
  delay(300);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); //diubah menjadi 100 pada rev1
    //delay(100); diubah menjadi 5 pada rev2
    Serial.print(" . ");
    //delay(5);
  }
  //dihapus pada rev2 karena hanya untuk debug
  Serial.println("WiFi connected");
  
  /*
  //dihapus pada rev2 karena hanya untuk debug
  // device identification
  Serial.println("Device information");
  ip = WiFi.localIP();
  
  Serial.print("Device IP : ");
  Serial.println(ip);
  
  subnet = WiFi.subnetMask();
  Serial.print("Subnet    : ");
  Serial.println(subnet);
  
  gateway = WiFi.gatewayIP();
  Serial.print("Gateway   : ");
  Serial.println(gateway);
  
  Serial.println();
  Serial.print("Connecting to : ");
  Serial.println(host);

  //delay(500); dihapus pada rev 1
  */
  con2server();
}

// Set-up connetion to server
void con2server(){
  if(!client.connected()){
    //Serial.println("Reconnect");
    Connect_Stat=false;
    client.connect("ESP8266_DESTROY");
  }
}

