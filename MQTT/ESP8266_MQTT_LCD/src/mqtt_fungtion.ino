//=================void mqtt==================
void callback(char* topic, byte* payload, uint32_t length){//unsigned int length) {
  int strLength;
  //------convert to string-------------------------
  payload[length]='\0';// terminate string with 0
  buff = String((char*)payload);  // convert to string
  //Serial.println("test string : "+buff);
  //Serial.println(Serial_data);
  strLength = buff.indexOf("$");
    if(strLength != -1){
      lcd.clear();
      buff = buff.substring(0,strLength);
      //Serial.println(buff);
      lcd.setCursor(0, 1);
      lcd.print(buff);
      processBuffer();
    }
    buff="";
}