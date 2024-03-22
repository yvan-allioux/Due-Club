DueClub
=======

Mini-scène pour les playmobils qui aiment faire la fête !

![image d'ilustration dalle](/assets/DALLE.jpg)

Sommaire
--------

-   [Introduction](https://github.com/yvan-allioux/Due-Club#introduction)
-   [Description globale du projet](https://github.com/yvan-allioux/Due-Club#description-globale-du-projet)
    -   [Projet](https://github.com/yvan-allioux/Due-Club#projet)
    -   [Organisation](https://github.com/yvan-allioux/Due-Club#organisation)
-   [Principe de fonctionnement](https://github.com/yvan-allioux/Due-Club#principe-de-fonctionnement)
    -   [Carte maître](https://github.com/yvan-allioux/Due-Club#carte-ma%C3%AEtre)
    -   [Application](https://github.com/yvan-allioux/Due-Club#application)
    -   [Carte esclave pour la gestion du son](https://github.com/yvan-allioux/Due-Club#carte-esclave-pour-la-gestion-du-son)
    -   [Carte esclave pour la gestion des lumières](https://github.com/yvan-allioux/Due-Club#carte-esclave-pour-la-gestion-des-lumi%C3%A8res)
-   [Difficultés rencontrées](https://github.com/yvan-allioux/Due-Club#difficult%C3%A9s-rencontr%C3%A9es)
-   [Conclusion](https://github.com/yvan-allioux/Due-Club#conclusion)

![image d'ilustration](/assets/1.jpg)

Introduction
------------

Le projet DueClub consiste en une boîte de nuit connectée spécialement conçue pour les playmobils. Notre ambition principale est de créer un système de gestion sonore et lumineuse dédié à une discothèque miniature. L'équipe, constituée de six membres, a collaboré tout au long des sessions de travaux pratiques pour développer un système interconnecté.

Description globale du projet
-----------------------------

### Projet

L'objectif de ce projet est de concevoir une petite scène musicale équipée de son et de jeux de lumière, le tout contrôlé par une application Android. À l'aide de microcontrôleurs et de capteurs, nous avons élaboré une version miniature d'une discothèque, comprenant de la musique entraînante et des effets lumineux, permettant à nos playmobils de danser toute la nuit.

![image d'ilustration](/assets/2.jpg)

### Organisation

-   08/12 : Création et conception du projet. Réalisation du cahier des charges.
-   19/12 : Initialisation du projet. Partage des tâches : Bluetooth, Son, Lumières, Application.
-   09/01 : Travail de groupes sur les différentes parties.
-   22/01 : Rassemblement des différentes parties fonctionnelles. Liaison avec le Bluetooth.
-   25/01 (hors cours) : Travail sur le Bluetooth. Mise en fonctionnement de toutes les parties ensemble (son, lumière, app, carte maître).
-   29/01 : Finition du projet, montage matériel pour la présentation.

Principe de fonctionnement
--------------------------

Le projet DueClub se divise en quatre parties distinctes : l'application, la carte Arduino Due maître, ainsi que deux cartes Arduino Due esclaves.

### Carte maître

La carte maître joue un rôle central en assurant la connexion entre l'application et les deux cartes esclaves. Elle intègre trois modules Bluetooth, établissant ainsi une liaison sans fil entre l'application, le système audio et les éléments lumineux.

### Application

L'application permet de contrôler via Bluetooth le son et la lumière et d'afficher la remontée d'information du module LED Bar pour connaître son état. L'interface de l'application se compose de différents boutons permettant d'envoyer les commandes à la carte maître.

### Carte esclave pour la gestion du son

La gestion du son a été rendue possible grâce à l'utilisation d'une carte son et d'une carte SD. Ces composants ont permis de stocker des morceaux de musique et de les lire à la demande. Parallèlement, l'intégration d'un module Bluetooth a permis la réception des commandes émanant de l'application.

### Carte esclave pour la gestion des lumières

La gestion de l'éclairage s'est effectuée à l'aide de plusieurs modules lumineux, notamment le RGB LED Stick, la LED Bar et le LED Socket. Pour recevoir et transmettre des commandes, nous avons opté pour l'utilisation d'un module Bluetooth HC05.

Difficultés rencontrées
-----------------------

-   Partie sonore : difficulté à jouer un son lors des premières séances en raison de la documentation difficilement accessible du composant Serial MP3 Player v1.0.
-   Bluetooth (double saut) : défi significatif pour la mise en place de la connexion entre deux modules Bluetooth.
-   Branchements : complications supplémentaires dues au processus de débranchement et de rebranchement entre chaque séance.

Conclusion
----------

Notre équipe a collaboré étroitement pour mener à bien les différentes phases de ce projet. Nous avons réussi à créer une boîte de nuit pour playmobils, intégrant à la fois des éléments lumineux et sonores. Malgré quelques difficultés rencontrées et un investissement important en temps en dehors des cours, nous avons réussi à surmonter les obstacles liés à la carte son et au Bluetooth. Nous avons pris un réel plaisir à travailler sur ce projet, et nous sommes fiers du résultat final. Ainsi, notre boîte de nuit, baptisée DueClub, est désormais reconnue comme la plus populaire dans le monde des playmobils.