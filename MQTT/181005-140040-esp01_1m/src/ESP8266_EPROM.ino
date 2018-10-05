/*
 * Parameter setting
 * Flash Mode : DIO
 * Flash Freq : 40 MHz
 * CPU Freq : 80 MHz
 */
#include <Ticker.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

char host[16],ssid[16],password[16];

int ipd1,ipd2,ipd3,ipd4; //ip device
int sub1,sub2,sub3,sub4; //subnet
int gat1,gat2,gat3,gat4; //gateway

IPAddress ip,subnet,gateway;

int port,flag;
String device_ip,gateway_ip,subnet_ip,server_ip,n_ssid,p_ssid, s_port,s_timeout;
char cdevice_ip[16],cgateway_ip[16],csubnet_ip[16],cserver_ip[16],cn_ssid[16],cp_ssid[16],cs_port[6],ct_timeout[7];
String temp_DIP,temp_GIP,temp_NIP,temp_HOST,temp_SSID,temp_PASS,temp_PORT;

int addrDIP = 1;
int addrGIP = 18;
int addrNIP = 35;
int addrSIP = 52;
int addrSSID = 69;
int addrPSSID = 86;
int addrPORT = 103;

// Use WiFiClient class to create TCP connections
WiFiClient espClient;
PubSubClient client(espClient);

//--------------------------------------------------
int Timeout_Connect = 6;      //3 detik
int Timeout_Reset = 600;      //5 menit

bool Connect_Stat=false;
int Count_Reset=0;
int Count_Connect=0;
int Count_dis=0;
String buff;

//--------------------------------------------------

String Serial_data,temp_ip,temp_time;

void timerIsr();
Ticker timer4(timerIsr,500);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(10);
    
    EEPROM.begin(512);
    EEPROM_Setup();
    EEPROM_Set_Address();
  
    IPAddress ip(ipd1,ipd2,ipd3,ipd4);
    IPAddress subnet(sub1,sub2,sub3,sub4);
    IPAddress gateway(gat1,gat2,gat3,gat4);
    /*
    // Connect to WiFi network
    Serial.println("Connecting to AP ");
    delay(5000);
    Serial.print("SSID Name : ");
    Serial.println(n_ssid);
    Serial.print("SSID Pass : ");
    Serial.println(p_ssid);
    delay(250);
    */
    con2WiFi();
    
    client.setServer(host, 1883);
    client.setCallback(callback);
    //*
    Serial.println("");
    Serial.println("WiFi connected");
    
    //set static ip
    WiFi.config(ip,gateway,subnet);
    
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
    Serial.print("Port : ");
    Serial.println(port);
    //*/
    con2server();
 
    timer4.start();
    Count_Reset=Timeout_Reset;
}

void loop()
{
 client.loop();
 timer4.update();
}

void timerIsr()
{
//Serial.println("check");
//-----------------------------------  
if(!client.connected() || client.state() == -1){
    if(Count_Connect==0){
      Count_dis=0;
      Count_Connect=Timeout_Connect;
      if(WiFi.status() == WL_CONNECTED){
        con2server();
      }
      else{
          con2WiFi();
         }
    }else{
      Count_Connect--;
      Count_dis++;
      if(Count_dis>=6){
        Serial.print("failed to connect, reconnect = ");
        Serial.print(client.state());
        Serial.println("try again every 3 S");
        Count_dis=0;
      }
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
      String topic = "top";
      String pay="pesan";
      // On cennected, publish an announcement...
      //bool MQTT::publish(String& topic, String& data, int qos, int retain)
      client.publish("outTopic","payload");
      //and resubscribe
      client.subscribe("inTopic");
    }
  }
}
//------------------------------------------------------
