// Définition du numéro de broche pour la LED intégrée
const int ledPin = 13; // La plupart des cartes Arduino ont une LED intégrée sur la broche 13

void setup() {
  // Initialise la broche de la LED en mode sortie
  pinMode(ledPin, OUTPUT);

  // Boucle pour faire clignoter la LED 10 fois
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);   // Allume la LED
    delay(200);                   // Attend 200 ms
    digitalWrite(ledPin, LOW);    // Éteint la LED
    delay(200);                   // Attend 200 ms
  } 
}

void loop() {
  // La boucle loop() reste vide car le clignotement ne se produit que dans le setup()
}
