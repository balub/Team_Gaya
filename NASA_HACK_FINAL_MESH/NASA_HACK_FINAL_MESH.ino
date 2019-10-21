#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 20, 4);

RF24 radio(9, 10); // CE, CSN
RF24Network network(radio);      // Include the radio in the network
const byte address[6] = "00001";
int len = 0;
char response[225] = "";

int buttons[] = {2, 3, 4, 5};

void setup() {
  Serial.begin(9600);
  radio.begin();
  network.begin(90, 01); //(channel, node address)
  radio.setAutoAck(false);
  radio.setRetries(15, 15);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  lcd.begin();
  lcd.backlight();
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(8, OUTPUT);

}
void loop() {

  if (digitalRead(2) == HIGH) {
    lcd.clear();
    if (radio.available()) {
      len = radio.getDynamicPayloadSize();
      radio.read(&response, len);
      Serial.println(response);
    }
    lcd.setCursor(0, 0);
    lcd.print(response);
    for (int positionCounter = 0; positionCounter < (len * 10) ; positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(150);
    }
  }
  if (digitalRead(3) == HIGH) {
    sendSOS();
  }
  if (digitalRead(4) == HIGH) {
    flashLightd();
  }
  if (digitalRead(5) == HIGH) {
    lcd.display();
    AID();
  }
}

void sendSOS() {
  Serial.println("SOS sent");
  char message[] = "Help needed at 17.31,12,65";
  RF24NetworkHeader header2(00);     // (Address where the data is going)
  bool ok2 = network.write(header2, &message, sizeof(message)); // Send the data
  
}
void flashLightd() {
  Serial.println("flashing lights");
  delay(300);
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(8, LOW);

  }
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);

  }
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(8, LOW);

  }
  delay(300);
}
void AID() {
  lcd.clear();
  String question[] = {"If Cut:",
                       "If Bone Broke",
                       "If Deep Cut",
                       "If Cold and Wet"
                      };
  String answer[] = {" Apply Turmeric poweder ASAP",
                     "Make a Makeshift Turnikit",
                     "Wrap with clean cloth",
                     "Get Warm, Change clothes"
                    };
  int  num = random(0, 4);
  lcd.setCursor(0, 0);
  lcd.print(question[num]);
  lcd.setCursor(0, 1);
  lcd.print(answer[num]);
  for (int positionCounter = 0; positionCounter < len; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

}

