#line 1
#include <Arduino.h>

void write_string_eeprom(char *str, int a){
  for(int i = 0; i < strlen(str); i++){
    char x = str[i];
    EEPROM.write(a,x);
    a++;
    yield();
  }
}

String read_string_eeprom(int start, int finish){
  String temp = "";
  for(start; start < finish; start++){
    char c;
    c = EEPROM.read(start);
    if(c != NULL){
      temp += c;
    }
  }
  return temp;
}

void clear_eeprom(int start, int finish){
  for(start; start < finish; start++){
    EEPROM.write(start,'\0');
    yield();
  }
}

void EEPROM_Setup(){
  /*
  //Just for write
  clear_eeprom(1,120);
  EEPROM.commit();
  */
 /*
  //clear_eeprom(1,120);
  write_string_eeprom("192.168.4.7",addrDIP);
  write_string_eeprom("192.168.4.1",addrGIP);
  write_string_eeprom("255.255.255.0",addrNIP);
  write_string_eeprom("192.168.4.5",addrSIP);
  write_string_eeprom("LSD",addrSSID);
  write_string_eeprom("987654321",addrPSSID);
  write_string_eeprom("1883",addrPORT);
  EEPROM.commit();
  */
  
  device_ip = read_string_eeprom(addrDIP,addrDIP+15);
  gateway_ip = read_string_eeprom(addrGIP,addrGIP+15);
  subnet_ip = read_string_eeprom(addrNIP,addrNIP+15);
  server_ip = read_string_eeprom(addrSIP,addrSIP+15);
  n_ssid = read_string_eeprom(addrSSID,addrSSID+15);
  p_ssid = read_string_eeprom(addrPSSID,addrPSSID+15);
  s_port = read_string_eeprom(addrPORT,addrPORT+5);
  
  /*
  Serial.print("Device IP : ");
  Serial.println(device_ip);
  Serial.print("Gateway   : ");
  Serial.println(gateway_ip);
  Serial.print("Subnet    : ");
  Serial.println(subnet_ip);
  
  Serial.print("Server IP   : ");
  Serial.println(server_ip);
  Serial.print("Server port : ");
  Serial.println(s_port);
    
  Serial.print("SSID Name   : ");
  Serial.println(n_ssid);
  
  Serial.print("SSID Pass   : ");
  Serial.println(p_ssid);
  */
}

void EEPROM_Set_Address(){
  String temp1,temp2,temp3,temp4;
  int ak1,ak2,ak3,len;

  len = device_ip.length();
  ak1 = device_ip.indexOf(".");
  ak2 = device_ip.indexOf(".",ak1+1);
  ak3 = device_ip.indexOf(".",ak2+1);
  
  temp1 = device_ip.substring(0,ak1);
  temp2 = device_ip.substring(ak1+1,ak2);
  temp3 = device_ip.substring(ak2+1,ak3);
  temp4 = device_ip.substring(ak3+1,len);

  ipd1 = temp1.toInt();
  ipd2 = temp2.toInt();
  ipd3 = temp3.toInt();
  ipd4 = temp4.toInt();
  //////////////////////////////////////////
  len = subnet_ip.length();
  ak1 = subnet_ip.indexOf(".");
  ak2 = subnet_ip.indexOf(".",ak1+1);
  ak3 = subnet_ip.indexOf(".",ak2+1);
  
  temp1 = subnet_ip.substring(0,ak1);
  temp2 = subnet_ip.substring(ak1+1,ak2);
  temp3 = subnet_ip.substring(ak2+1,ak3);
  temp4 = subnet_ip.substring(ak3+1,len);

  sub1 = temp1.toInt();
  sub2 = temp2.toInt();
  sub3 = temp3.toInt();
  sub4 = temp4.toInt();
  //////////////////////////////////////////
  len = gateway_ip.length();
  ak1 = gateway_ip.indexOf(".");
  ak2 = gateway_ip.indexOf(".",ak1+1);
  ak3 = gateway_ip.indexOf(".",ak2+1);
  
  temp1 = gateway_ip.substring(0,ak1);
  temp2 = gateway_ip.substring(ak1+1,ak2);
  temp3 = gateway_ip.substring(ak2+1,ak3);
  temp4 = gateway_ip.substring(ak3+1,len);

  gat1 = temp1.toInt();
  gat2 = temp2.toInt();
  gat3 = temp3.toInt();
  gat4 = temp4.toInt();
  //////////////////////////////////////////
  server_ip.toCharArray(host,16);
  n_ssid.toCharArray(ssid,16);
  p_ssid.toCharArray(password,16);
  port = s_port.toInt();
}
