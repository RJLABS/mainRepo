void processBuffer(){

  String task,dat;
  int m0,m11,m12,m21,m22,m31,m32,m41,m42;
  m0 = buff.indexOf('=');
  task = buff.substring(0,m0);
  //Serial.println(task);

 if(task == "tes"){
  Serial.println("test mode on");  
 }
 else if(task == "C1"){
    m12 = buff.indexOf('~',m0+1);
    m21 = buff.indexOf('=',m12+1);
    m22 = buff.indexOf('~',m21+1);
    m31 = buff.indexOf('=',m22+1);
    m32 = buff.indexOf('~',m31+1);
    m41 = buff.indexOf('=',m32+1);
    m42 = buff.indexOf('~',m41+1);

    temp_HOST = buff.substring(m0+1,m12);
    temp_SSID = buff.substring(m21+1,m22);
    temp_PASS = buff.substring(m31+1,m32);
    temp_PORT = buff.substring(m41+1,m42);

    //change server ip
    clear_eeprom(addrSIP,addrSIP+16);
    temp_HOST.toCharArray(cserver_ip,16);
    write_string_eeprom(cserver_ip, addrSIP);
    //EEPROM.commit();
    
    //change ssid name
    clear_eeprom(addrSSID,addrSSID+16);
    temp_SSID.toCharArray(cn_ssid,16);
    write_string_eeprom(cn_ssid, addrSSID);
    //EEPROM.commit();
    
    //change ssid pass
    clear_eeprom(addrPSSID,addrPSSID+16);
    temp_PASS.toCharArray(cp_ssid,16);
    write_string_eeprom(cp_ssid, addrPSSID);
    //EEPROM.commit();
    
    //change port
    clear_eeprom(addrPORT,addrPORT+5);
    temp_PORT.toCharArray(cs_port,6);
    write_string_eeprom(cs_port, addrPORT);
    EEPROM.commit();
    
    dat = device_ip;
    dat += "#Device IP has been change#$";
    dat = "";
    buff = "";
    Serial_data = "";
  }
  else if (task == "C2"){
    m12 = buff.indexOf('~',m0+1);
    m21 = buff.indexOf('=',m12+1);
    m22 = buff.indexOf('~',m21+1);
    m31 = buff.indexOf('=',m22+1);
    m32 = buff.indexOf('~',m31+1);
    
    temp_DIP = buff.substring(m0+1,m12);
    temp_NIP = buff.substring(m21+1,m22);
    temp_GIP = buff.substring(m31+1,m32);
    
    //change device IP
    clear_eeprom(addrDIP,addrDIP+16);
    temp_DIP.toCharArray(cdevice_ip,16);
    write_string_eeprom(cdevice_ip, addrDIP);
    //EEPROM.commit();
    
    //change subnet
    clear_eeprom(addrNIP,addrNIP+16);
    temp_NIP.toCharArray(csubnet_ip,16);
    write_string_eeprom(csubnet_ip, addrNIP);
    //EEPROM.commit();
    
    //change gateway
    clear_eeprom(addrGIP,addrGIP+16);
    temp_GIP.toCharArray(cgateway_ip,16);
    write_string_eeprom(cgateway_ip, addrGIP);
    EEPROM.commit();
    
    dat = device_ip;
    dat += "#Device IP has been change#$";
    dat = "";
    buff = "";
    Serial_data = "";
  }
}