#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//RF24 radio(9, 10); // CE, CSN
RF24 radio(D4,D3); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setRetries(15, 15);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  char request[255] = "FLOOD WARNING";   
  radio.write(&request, strlen(request));
  Serial.println(request);//"1"
  
}
