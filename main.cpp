#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;

String authorizedUID = "YourRFIDUID";  // Tanımlı kart UID'si

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(8);
  myServo.write(0); // Kilitli pozisyon
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  if (uid == authorizedUID) {
    Serial.println("Yetkili kart! Kapı açılıyor...");
    myServo.write(90); // Kapı açılıyor
    delay(3000);
    myServo.write(0);  // Kapı tekrar kilitleniyor
  } else {
    Serial.println("Geçersiz kart!");
  }
}
