#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

//RF24 radio(12,14); // CE, CSN for esp32
//RF24 radio(D4,D3); // CE, CSN for nodemcu
RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";
int len=0;
char response[225]="";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setRetries(15, 15);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    len = radio.getDynamicPayloadSize();
    radio.read(&response, len);
    Serial.println(response);
  }
}
