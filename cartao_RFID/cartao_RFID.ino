#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53 // Arduino Mega
#define RST_PIN 5 // Arduino Mega
#define LED 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  pinMode(LED, OUTPUT);
  SPI.begin();         // Inicia comunicação (protocolo) SPI bus
  mfrc522.PCD_Init();  // Inicia a instância MFRC522

  Serial.begin(9600);  // Inicia comunicação Serial em 9600 baud rate
  initialMessage();
}

void loop() {
  // Verifica novos cartões: Aguarda a proximidade do cartão ou tag
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  
  // Verifica a porta serial para leitura: Seleciona o cartão
  if (!mfrc522.PICC_ReadCardSerial()) return;

  twinkleLed();

  // Mostra UID na serial
  Serial.print("UID do cartão:");
  String contentTag = "";
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    contentTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    contentTag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
}

void initialMessage() {
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  digitalWrite(LED, LOW);
}

void twinkleLed() {
  digitalWrite(LED, !digitalRead(LED));
  delay(500);
}
