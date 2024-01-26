#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(38400); // La vitesse par défaut pour les commandes AT du HC-05

  // Configure le module HC-05 en mode maître et le lie à l'adresse de l'esclave
  mySerial.print("AT+ROLE=1\r\n");
  delay(1000);
  mySerial.print("AT+CMODE=0\r\n");
  delay(1000);
  mySerial.print("AT+BIND=98D3,31,FC5179\r\n"); // Remplacez avec l'adresse de votre module esclave
  delay(1000);

  // D'autres configurations si nécessaire...
}

void loop() {
  mySerial.print('A'); // Envoie la lettre 'A'
  delay(10000); // Attend 10 secondes (10000 millisecondes)
}
