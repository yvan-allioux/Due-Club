# Due-Club
 Due-Club arduino

https://github.com/salvadorrueda/SerialMP3Player

# Probème de permission sur le port /dev/ttyACM0 sur Arduino DUE
Avec un IDE de type : arduino-ide_2.2.1_Linux_64bit.AppImage
- ls -l /dev/ttyACM0
- sudo nano /etc/udev/rules.d/99-arduino.rules écrire : '''SUBSYSTEM=="tty", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="003e", MODE="0666", GROUP="dialout"'''
- sudo udevadm control --reload-rules
- sudo chown $USER:dialout /dev/ttyACM0
- sudo chmod a+rw /dev/ttyACM0
- Eteindre et rallumer l'ordi
- ouviri IDE
- Lancer le code



