#include <SoftwareSerial.h>
 
SoftwareSerial mp3(5, 6);  // Création d'un objet SoftwareSerial pour la communication avec le module MP3
 
static uint8_t cmdbuf[8] = {0};  // Création d'un tableau pour stocker les commandes envoyées au module MP3
 
// Fonction pour envoyer des commandes au module MP3
void command(int8_t cmd, int16_t dat)
{
  delay(20);  // Délai pour assurer la stabilité de la communication

  cmdbuf[0] = 0x7e; // octet de début
  cmdbuf[1] = 0xFF; // version
  cmdbuf[2] = 0x06; // nombre d'octets dans la commande
  cmdbuf[3] = cmd;  // la commande elle-même
  cmdbuf[4] = 0x00; // 0x00 = pas de retour, 0x01 = avec retour
  cmdbuf[5] = (int8_t)(dat >> 8); // premier paramètre de la donnée (DAT1)
  cmdbuf[6] = (int8_t)(dat); // deuxième paramètre de la donnée (DAT2)
  cmdbuf[7] = 0xef; // octet de fin

  // Boucle pour envoyer la commande au module MP3
  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(cmdbuf[i]);
  }
}
 
// Configuration initiale
void setup()
{
  Serial.begin(9600);  // Initialisation de la communication série
  mp3.begin(9600);     // Initialisation de la communication avec le module MP3
 
  delay(500); // Attente de 500ms pour l'initialisation
  
  command(0x09, 0x0002); // Sélection de la carte SD comme source
  delay(200); // Attente de 200ms pour l'initialisation
 
  command(0x06, 0x001E); // Réglage du volume à 30
  command(0x03, 0x0001); // Lecture de la première piste (dans l'ordre non trié)
  //delay(10000);
  //command(0x0D, 0x0000); // Lecture de tous les fichiers MP3
}
 
// Boucle principale vide
void loop() { }
