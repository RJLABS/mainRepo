

//smartRelay.ino
/*
* create 22082018
*
*
*/
#include <IRremote.h>
#include <SoftwareSerial.h>


#define RL1 0
#define RL2 0
#define RL3 0
#define RL4 0
#define RL5 0

SoftwareSerial mySerial(10, 11); // RX, TX

int buff;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over
  if (mySerial.available()) {
    buff=mySerial.read();
    execute(buff);
    Serial.write(mySerial.read());
  }

  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
//===================================
void execute(int inByte ){
    switch (inByte) {
      case 'a':
        digitalWrite(RL1, HIGH);
        break;
      case 'b':
        digitalWrite(RL2, HIGH);
        break;
      case 'c':
        digitalWrite(RL3, HIGH);
        break;
      case 'd':
        digitalWrite(RL4, HIGH);
        break;
      case 'e':
        digitalWrite(RL5,HIGH);
        break;
      case 'A':
      	digitalWrite(RL1,LOW);
      	break;
      case 'B':
      	digitalWrite(RL2,LOW);
      	break;
      case 'C':
      	digitalWrite(RL3,LOW);
      	break;
      case 'D':
      	digitalWrite(RL4,LOW);
      	break;
      case 'E':
      	digitalWrite(RL5,LOW);
      	break;	

      default:
        // turn all the LEDs off:
         Serial.println("unknow command!! check again");
         mySerial.write("unknow command!! check again");
        }
   }
