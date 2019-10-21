#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

RF24 radio(9, 10); // CE, CSN

//RF24 radio(12,14); // CE, CSN for esp
//RF24 radio(12, 14, 26, 25, 27);
const byte address[6] = "00001";
int response;

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
    radio.read(&response, sizeof(response));
    Serial.println(response);
  }
}

