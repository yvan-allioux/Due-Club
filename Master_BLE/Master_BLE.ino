
// Contrôle du mode AT du HC-05
const int hc05_at_control_pin_Sound = 10;
const int hc05_at_control_pin_Light = 11;

void setup()
{
  // Configurer le pin de contrôle HC-05 Light
  pinMode(hc05_at_control_pin_Light, OUTPUT);
  digitalWrite(hc05_at_control_pin_Light, HIGH); // Activer le mode AT
  Serial1.begin(38400);                          // Communication with Light

  delay(1000);

  Serial2.begin(9600); // Communication with Phone
  // Serial3.begin(9600); // Communication with Sound

  // Configurer le pin de contrôle HC-05 Sound
  pinMode(hc05_at_control_pin_Sound, OUTPUT);
  digitalWrite(hc05_at_control_pin_Sound, HIGH); // Activer le mode AT
  Serial3.begin(38400);                          // Vitesse en bauds pour la communication avec le HC-05

  // Attendre que le module HC-05 soit prêt
  delay(1000);

  // SOUND MODULE
  // Envoyer les commandes AT pour la configuration
  sendATCommandSound("AT");
  sendATCommandSound("AT+ORGL");
  sendATCommandSound("AT+IAC?");

  sendATCommandSound("AT+NAME=MAITRE");
  sendATCommandSound("AT+NAME?");

  sendATCommandSound("AT+PSWD=1234");

  sendATCommandSound("AT+RMAAD");
  sendATCommandSound("AT+ROLE=1");
  sendATCommandSound("AT+UART=38400,0,0");
  // Remplacez par l'adresse module esclave IDUINO 98d3:51:fe0b54   111330 98d3:31:f61b53 38400 98d3:32:70f6c1
  sendATCommandSound("AT+BIND=98d3,51,fe0b54"); // IDUINO 98d3:51:fe0b54
  // sendATCommandSound("AT+BIND=98d3,31,f61b53"); //111330 98d3:31:f61b53
  // sendATCommandSound("AT+BIND=98d3,32,70f6c1"); //38400 98d3:32:70f6c1

  sendATCommandSound("AT+CMODE=0");

  // sendATCommandSound("AT+INIT");
  // AT+INIT mode qui permet l'appairage
  // AT+INQ" pour détecter l'Esclave

  // Désactiver le mode AT
  digitalWrite(hc05_at_control_pin_Sound, LOW);
  delay(1000); // Petite pause après désactivation du mode AT
  sendATCommandSound("AT+RESET");

  // Attendre que le module redémarre
  delay(2000);

  // LIGHT MODULE
  // Envoyer les commandes AT pour la configuration
  sendATCommandLight("AT");
  sendATCommandLight("AT+ORGL");
  sendATCommandLight("AT+IAC?");

  sendATCommandLight("AT+NAME=MAITRE");
  sendATCommandLight("AT+NAME?");

  sendATCommandLight("AT+PSWD=1234");

  sendATCommandLight("AT+RMAAD");
  sendATCommandLight("AT+ROLE=1");
  sendATCommandLight("AT+UART=38400,0,0");
  // Remplacez par l'adresse module esclave IDUINO 98d3:51:fe0b54   111330 98d3:31:f61b53 38400 98d3:32:70f6c1
  sendATCommandLight("AT+BIND=000e,ea,cf750a"); // IDUINO 98d3:51:fe0b54
  // sendATCommandSound("AT+BIND=98d3,31,f61b53"); //111330 98d3:31:f61b53
  // sendATCommandSound("AT+BIND=98d3,32,70f6c1"); //38400 98d3:32:70f6c1

  sendATCommandLight("AT+CMODE=0");

  // sendATCommandSound("AT+INIT");
  // AT+INIT mode qui permet l'appairage
  // AT+INQ" pour détecter l'Esclave

  // Désactiver le mode AT
  digitalWrite(hc05_at_control_pin_Light, LOW);
  delay(1000); // Petite pause après désactivation du mode AT
  sendATCommandLight("AT+RESET");

  // Attendre que le module redémarre
  delay(2000);
}

void loop()
{
  // Send Light info to Phone
  if (Serial1.available())
  {
    char data = Serial1.read(); // Get Light data
    Serial2.write(data);        // Send to phone
  }

  // Send Phone commands to Light and Sound
  if (Serial2.available())
  {
    char data = Serial2.read(); // Get Phone data
    Serial1.write(data);        // Send to Light
    Serial3.write(data);        // Send to Sound
  }
}

void sendATCommandSound(const String &command)
{
  Serial3.println(command); // Envoyer la commande AT
  delay(800);               // Attendre un peu pour la réponse

  // Lire et afficher la réponse
  while (Serial3.available())
  {
    char c = Serial3.read();
  }
}

void sendATCommandLight(const String &command)
{
  Serial1.println(command); // Envoyer la commande AT
  delay(800);               // Attendre un peu pour la réponse

  // Lire et afficher la réponse
  while (Serial1.available())
  {
    char c = Serial1.read();
  }
}