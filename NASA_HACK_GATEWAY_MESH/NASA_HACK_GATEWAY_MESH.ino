#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "nodemcu-245ef.firebaseio.com"
#define FIREBASE_AUTH "MqB5VsM7NEF48eHnpnbqmpORgxo5ldzHPRLuYpo8"
#define WIFI_SSID "BALU HOTSPOT"
#define WIFI_PASSWORD "balu1562"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//RF24 radio(9, 10); // CE, CSN
RF24 radio(D4, D3); // CE, CSN
const byte address[6] = "00001";
RF24Network network(radio);
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  radio.begin();
  network.begin(90, this_node);

  radio.setAutoAck(false);
  radio.setRetries(15, 15);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  String c1 = Firebase.getString("Message/message");
  Serial.println(c1);
  char request[255] = "";
  for (int i = 0; i < c1.length(); i++) {
    request[i] = c1[i];
  }
  radio.write(&request, strlen(request));
  Serial.println(request);//"1"
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    char incomingData[225] = "";
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    Serial.println(incomingData);  // tell servo to go to a particular angle
  }

  if (Firebase.failed())
    Serial.print("setting /number failed:");
  Serial.println(Firebase.error());
  return;
  delay(100);
}
