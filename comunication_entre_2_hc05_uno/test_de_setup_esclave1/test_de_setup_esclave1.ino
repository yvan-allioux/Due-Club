#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // Définir les broches TX (2) et RX (3) pour le module HC-05
int ledPin = 13; // Pin pour la LED

void setup() {
  pinMode(ledPin, OUTPUT);
  bluetooth.begin(38400); // Initialise la communication série avec le module HC-05
}

void loop() {
  if (bluetooth.available()) { // Vérifie si des données sont disponibles depuis le module HC-05
    char receivedChar = bluetooth.read(); // Lit le caractère reçu
    
    if (receivedChar == 'A') { // Si le caractère reçu est 'A'
      for (int i = 0; i < 10; i++) {
        digitalWrite(ledPin, HIGH); // Allume la LED
        delay(200); // Attend 200 ms
        digitalWrite(ledPin, LOW); // Éteint la LED
        delay(200); // Attend 200 ms
      }
    }
  }
}
