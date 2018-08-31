#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte mac[]    = {  0x90, 0xA2, 0xDA, 0x00, 0x3B, 0xB6 };  //Ganti dengan MAC ethernet yang anda gunakan
byte ip[]     = { 192, 168, 1, 177 }; //Sesuaikan alamat IP dengan jaringan lokal
byte dns2[]     = {8, 8, 8, 8};
byte gateway[]     = { 192, 168, 1, 254 };
int data1;
char pubschar1 [20];
char message_buff[250];
char message_buff_call[200];
EthernetClient ethClient;
PubSubClient client("geeknesia.com", 1883, callback, ethClient);
void callback(char* topic, byte* payload, unsigned int length)
{
}

void setup()
{
  Serial.begin(9600); 
  delay(500);
  Ethernet.begin(mac, ip, dns2, gateway);
  pinMode(2, INPUT_PULLUP); //deklarasi sebagai input dan dengan internal pull up
}
void loop()
{
  if (!client.connected())  //bangun koneksi jika koneksi tidak terhubung dengan cloud
  {
    client.connect("DEVICE-ID", NULL, NULL, "iot/will", 2, 64, "DEVICE-ID");
  }

  if (digitalRead(2) == LOW) //karena pin di setting sebagai input dengan internal pull-up maka ketika switch di tekan kondisi berubah ke logika 0 atau "LOW"
  {
    Serial.println("Aktif");
    data1 = digitalRead(2);
    client.publish("iot/live", "DEVICE-ID"); //Masukkan device id
    itoa(data1, pubschar1, 10);
    String pubString  = "{\"code\":\"USERNAME:PASSWORD\","; //masukkan username dan password anda sesuai yang ada pada detail device
    pubString += "\"attributes\": {";
    pubString += "\"Status\": ""\"Aktif\",";
    pubString += "\"PIN_Logic\": " + String(pubschar1);
    pubString += "}}";
    pubString.toCharArray(message_buff, pubString.length() + 1);
    client.publish("iot/data", message_buff);
    delay(5000);
  }
  else if (digitalRead(2) == HIGH) // kondisi normal ketika switch tidak di tekan
  {
    Serial.println("Non-Aktif");
    data1 = digitalRead(2);
    client.publish("iot/live", "DEVICE-ID"); //Masukkan device id
    itoa(data1, pubschar1, 10);
    String pubString  = "{\"code\":\"USERNAME:PASSWORD\","; //masukkan username dan password anda sesuai yang ada pada detail device
    pubString += "\"attributes\": {";
    pubString += "\"Status\": ""\"Non-Aktif\",";
    pubString += "\"PIN_Logic\": " + String(pubschar1);
    pubString += "}}";
    pubString.toCharArray(message_buff, pubString.length() + 1);
    client.publish("iot/data", message_buff);
    delay(5000);
  }
}