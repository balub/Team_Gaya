#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int request;


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
  request = 30 ;
  radio.write(&request, sizeof(request));
  Serial.println("30");
}

