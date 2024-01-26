#include <SoftwareSerial.h>

// Pins pour SoftwareSerial (RX, TX)
const int hc05_rx_pin = 2; // Connecté au TX du HC-05
const int hc05_tx_pin = 3; // Connecté au RX du HC-05

// Contrôle du mode AT du HC-05
const int hc05_at_control_pin = 10;

SoftwareSerial hc05(hc05_rx_pin, hc05_tx_pin); // RX, TX

void setup() {
  // Initialiser les ports série pour la communication avec le HC-05 et le débogage
  Serial.begin(9600); // Pour le débogage

  Serial.println("up pin");
  // Configurer le pin de contrôle HC-05
  pinMode(hc05_at_control_pin, OUTPUT);
  digitalWrite(hc05_at_control_pin, HIGH); // Activer le mode AT

  Serial.println("hc05 serial start");
  hc05.begin(38400);  // Vitesse en bauds pour la communication avec le HC-05

  // Attendre que le module HC-05 soit prêt
  delay(1000);

  // Envoyer les commandes AT pour la configuration
  sendATCommand("AT+ADDR?");
  sendATCommand("AT+RMAAD");
  sendATCommand("AT+ROLE=1");
  sendATCommand("AT+CMODE=0");
  // Remplacez par l'adresse module esclave IDUINO 98d3:51:fe0b54   111330 98d3:31:f61b53 38400 98d3:32:70f6c1
  //sendATCommand("AT+BIND=98d3,51,fe0b54"); //IDUINO 98d3:51:fe0b54
  //sendATCommand("AT+BIND=98d3,31,f61b53"); //111330 98d3:31:f61b53
  sendATCommand("AT+BIND=98d3,32,70f6c1"); //38400 98d3:32:70f6c1
  sendATCommand("AT+UART=38400,0,0");
  //sendATCommand("AT+PSWD=1245"); // Définir le mot de passe

  // Désactiver le mode AT
  digitalWrite(hc05_at_control_pin, LOW);
  delay(1000); // Petite pause après désactivation du mode AT
  sendATCommand("AT+RESET");

  // Attendre que le module redémarre
  delay(2000);

  // Envoyer un message de test à l'esclave
  //hc05.println("test"); // Envoyer "test" au module HC-05 esclave
  Serial.println("end setup");
}

void loop() {
  delay(10000);
  Serial.print("A");
  hc05.println("A");
}

void sendATCommand(const String& command) {
  Serial.println("send to hc05 : " + command);
  hc05.println(command); // Envoyer la commande AT
  delay(800); // Attendre un peu pour la réponse
  
  // Lire et afficher la réponse
  while (hc05.available()) {
    char c = hc05.read();
    Serial.write(c);
  }
  Serial.println("---");
}
