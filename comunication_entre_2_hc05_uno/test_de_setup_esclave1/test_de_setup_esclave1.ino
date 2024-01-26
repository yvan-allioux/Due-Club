//ESCLAVE

#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // Définir les broches TX (2) et RX (3) pour le module HC-05
int ledPin = 13; // Pin pour la LED
const int hc05_at_control_pin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(hc05_at_control_pin, OUTPUT);
  digitalWrite(hc05_at_control_pin, HIGH); // Activer le mode AT
  delay(1000); // Attendre que le module soit prêt

  pinMode(ledPin, OUTPUT);
  bluetooth.begin(38400); // Initialise la communication série avec le module HC-05

  //sendATCommand("AT+RESET");
  //delay(1000);
  // Envoyez les commandes AT ici
  sendATCommand("AT"); // Vérifiez la communication avec le module 
  sendATCommand("AT+ORGL");

  sendATCommand("AT+NAME=ESCLAVE"); //a tester
  sendATCommand("AT+NAME?");

  sendATCommand("AT+RMAAD");
  sendATCommand("AT+ROLE=0"); // Définir le module en mode esclave
  sendATCommand("AT+UART=38400,0,0"); // Configurer la vitesse en bauds

  sendATCommand("AT+PSWD=1234"); // Définir le mot de passe
  // Désactiver le mode AT
  digitalWrite(hc05_at_control_pin, LOW);
  sendATCommand("AT+RESET");
  delay(1000);
  Serial.println("end setup");
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


void sendATCommand(const String& command) {
  Serial.println("send to hc05 : " + command);
  bluetooth.println(command); // Envoyer la commande AT
  delay(1000); // Attendre un peu pour la réponse

  // Lire et afficher la réponse
  while (bluetooth.available()) {
    char c = bluetooth.read();
    Serial.write(c);
  }
  Serial.println("---");
}
