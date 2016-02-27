#include <TinySP.h>

#define DATA_SIZE 10

int led = 13;
unsigned char payload[DATA_SIZE];
TinySP tinysp;

void setup() {
  pinMode(led, OUTPUT);
 
  // Dummy payload 0xFF 0xCA 0xFE 0xCA 0xFE ......
  for(int i = 0; i < DATA_SIZE; i++){
    if(i == 0){
        payload[i] = 0xFF; // The id of the payload
        }else
        {
          if(i % 2 == 0)
          {
            payload[i] = 0xCA;
          }else
            payload[i] = 0xFE;
        }
    }
    Serial.begin(9600);
}

void loop() {
  Packet packet_s = Packet(payload, DATA_SIZE);
  tinysp.send_packet(packet_s);
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}
