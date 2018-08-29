/*
 * 4/4/2018 add WDT RESET BY roni 
 * 5/4/2018 change lcd lib by roni
 * chage dht lib
 * add delay reconecting 
 * add auto restart
 * add 
 */

#include <avr/wdt.h>
#include <EEPROM.h>
//#include <SPI.h>
#include <Ethernet.h>
#include <Timer.h>


//#define hardReset 4    //pin reset
#define IR1 9
#define IR2 8
#define IR3 7
#define IR4 6
#define IR5 5

#define IR6 3
#define IR7 2
#define IR8 1
#define IR9 0
#define IR10 A0

#define IR11 A1
#define IR12 A2
#define IR13 A3
#define IR14 A4
#define IR15 A5

String REP1,REP2,REP3,REP4,REP5;
//--------------------------------------------------
int Timeout_Connect = 6;      //3 detik
int Timeout_Reset = 600;      //5 menit
int Timout_Suhu = 1200;       //10 menit
//--------------------------------------------------


byte mac[] = {0x28, 0x88, 0x7D, 0xFF, 0xFF, 0xFF};

IPAddress ip,subnet,gateway,server;
IPAddress ip_dns(0, 0, 0, 0);
int port;

int addrDIP = 1;
int addrGIP = 18;
int addrNIP = 35;
int addrSIP = 52;
int addrPORT = 69;

// Use WiFiClient class to create TCP connections
EthernetClient client;


bool Connect_Stat=false;
int Count_Reset=0;
int Count_Connect=0;
int Count_Suhu=0;
String buff;

boolean flgRun, flgOpen, flgClose;
unsigned long delay_time;
 
Timer Timer1;

//=====================================================
void setup() {
  io();
  EEPROM_Setup();
  delay(1000);
  Ethernet.begin(mac, ip, ip_dns, gateway, subnet);
  delay(300);

  // device identification
  //Serial.begin(115200);
  Serial.println("Device information");
  //*
  Serial.print("MAC: ");
  Serial.print(mac[0],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.println(mac[5],HEX);
  //*/  
  
  ip = Ethernet.localIP();
  Serial.print("IP: ");
  Serial.println(IpAddress2String(ip));

  gateway = Ethernet.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(IpAddress2String(gateway));
  
  subnet = Ethernet.subnetMask();
  Serial.print("Subnet: ");
  Serial.println(IpAddress2String(subnet));
    
  Serial.print("Connecting to: ");
  Serial.println(server);
  Serial.print("Port: ");
  Serial.println(port);
 
  con2server();

  delay(1000);
  buff.reserve(150);
  Timer1.every(1000,timerIsr);

  Count_Reset=Timeout_Reset;
  Count_Suhu =Timout_Suhu;
  wdt_enable(WDTO_8S);
  wdt_reset();
}

//=====================================================
void loop() {
  int strLength;
  wdt_reset();
  if (client.available()>0){
    buff = client.readStringUntil('\n');
    delay(1);
    wdt_reset();
    //Serial.println(Serial_data);
    strLength = buff.indexOf("$");
    if(strLength != -1){
      buff = buff.substring(0,strLength);
      processBuffer();
      buff ="";
    }
    client.flush();
  }
  //checkTime();
  Timer1.update();
}

//--------------------------------------------------------------
void timerIsr(){

  if(!client.connected()){
    if(Count_Connect==0){
      Count_Connect=Timeout_Connect;
      con2server();
    }else{
      Count_Connect--;
    }

    if(Count_Reset==0){
      Serial.println("Restart");
      wdt_enable(WDTO_2S);
      while(1);
    }else{
      Count_Reset--;
    }
  }else{
    Count_Connect=0;
    Count_Reset=Timeout_Reset;
    if(Connect_Stat==false){
      Serial.println("Conected");
      Connect_Stat=true;  
      String temp = IpAddress2String(ip);
      temp += "#ETHERNET BASE#$";
      client.print(temp);  
    }
  }

  readSensor(1);
  readSensor(2);
  readSensor(3);

}

