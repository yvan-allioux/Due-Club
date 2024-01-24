#include <SoftwareSerial.h>
 
SoftwareSerial mp3(5, 6);
 
static uint8_t cmdbuf[8] = {0};
 
void command(int8_t cmd, int16_t dat)
{
  delay(20);
 
  cmdbuf[0] = 0x7e; // bajt startu
  cmdbuf[1] = 0xFF; // wersja
  cmdbuf[2] = 0x06; // liczba bajtow polecenia
  cmdbuf[3] = cmd;  // polecenie
  cmdbuf[4] = 0x00; // 0x00 = no feedback, 0x01 = feedback
  cmdbuf[5] = (int8_t)(dat >> 8); // parametr DAT1
  cmdbuf[6] = (int8_t)(dat); //  parametr DAT2
  cmdbuf[7] = 0xef; // bajt konczacy
 
  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(cmdbuf[i]);
  }
}
 
void setup()
{
  Serial.begin(9600);
  mp3.begin(9600);
 
  delay(500); // Czekamy 500ms na inicjalizacje  
 
  command(0x09, 0x0002); // Wybieramy karte SD jako zrodlo
  delay(200); // Czekamu 200ms na inicjalizacje
 
  command(0x06, 0x001E); // Ustaw glosnosc na 30
  command(0x03, 0x0001); // Otwarzamy pierwszy utwor (kolejnosc nieposortowana)
}
 
void loop() { }