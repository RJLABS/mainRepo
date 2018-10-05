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
      buff = buff.substring(0,strLength);
      Serial.println(buff);
      processBuffer();
    }
    buff="";
}
//===================================================
void pub(String topic,String Data)
{  
  if(client.connected()){
    char charData[120];
    char charIP[50];
    memset(charData,'\n',sizeof(charData));
    memset(charIP,'\n',sizeof(charIP));
    topic.toCharArray(charIP,topic.length()+1);
    Data.toCharArray(charData,Data.length()+1);
    client.publish(charIP,charData);
    }   
}

//===========================================
void sub(String Data1)
{  
  char charData1[50];
  memset(charData1,'\n',sizeof(charData1));
  Data1.toCharArray(charData1,Data1.length()+1);
  client.subscribe(charData1);
  //free(charData);
}
