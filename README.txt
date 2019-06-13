Structure des fichiers:
------------------------------------------------------------------------------------------------------------
├── Librairie: Fichiers nécessaires à la création de la librairie. Celle-ci contient du code réutilisable.
|   |
│   ├── capteurs.cpp
│   ├── capteurs.h
│   ├── cleanMemory.cpp
│   ├── cleanMemory.h
│   ├── communication.cpp
│   ├── communication.h
│   ├── ConversionMemoire.cpp
│   ├── ConversionMemoire.h
│   ├── debug.cpp
│   ├── debug.h
│   ├── fonctions_led.cpp
│   ├── fonctions_led.h
│   ├── includeAll.h
│   ├── Interrupts.cpp
│   ├── Interrupts.h
│   ├── Makefile
│   ├── Makefile_common.mk
│   ├── memoire_24.cpp
│   ├── memoire_24.h
│   ├── moteur.cpp
│   ├── moteur.h
│   ├── Piezo.cpp
│   ├── Piezo.h
│   ├── son.cpp
│   └── son.h
|
├── README.txt
|
├── Robot : Contient le code pour le robot1 et le robot2
|   |
│   ├── Robot1: Fichiers pour installer le programme du premier robot.
│   │   ├── coin1.cpp
│   │   ├── coin2.cpp
│   │   ├── coin3.cpp
│   │   ├── coin4.cpp
│   │   ├── fonctions.h
│   │   ├── Makefile
│   │   └── robot1.cpp
│   │
│   │
│   ├── Robot2: Fichiers pour installer le programme du deuxième robot (Transmission infrarouge)
│   │   ├── Makefile
│   │   └── robot2.cpp
│   │   
│   └── test: Fichiers utilisés pour faire des tests unitaires.
│       ├── Makefile
│       └── test.cpp
|
└── serieViaUSB: Fichiers nécessaires pour lire la transmission sur le UART. Utilisé pour
                    le débogage.
------------------------------------------------------------------------------------------------------------
________________________________________
Description plus détaillée des fichiers:
________________________________________

-capteurs.* :           Contient les méthodes associées aux capteurs infrarouges utilisés pour suivre la ligne
                        noire.

-cleanMemory.* :        Contient les méthodes permettant d'effacer le contenu de la mémoire. Puisque nos
                        robots n'utilisent pas la mémoire externe, la fonction n'a pas été utilisée. 

-communication.* :      Contient les méthodes reliées à l'émetteur et au récepteur infrarouge qui 
                        permettaient la communication entre les deux robots.

-ConversionMemoire.*:   À MODIFIER

-debug.*                Contient les méthodes permettant de déboguer le robot.

-fonctions_led.* :      Contient les méthodes associées aux leds.

-includeAll.h :         Fichier d'en-tête contenant toutes les en-têtes utilisées. Utilisé pour réduire le nombre
                        de fichiers d'en-tête à importer dans un programme. 

-Interrupts.* :         Contient les méthodes reliées aux interruptions comme les minuteries et les boutons.

-Makefile_common.mk :   Makefile général que le Makefile de la librairie utilise. 

-memoire_24.* :         Contient les méthodes reliées à la mémoire externe. Nos robots n'utilisent pas
                        la mémoire externe donc ce fichier n'est pas utilisé.

-moteur.* :             Contient les méthodes reliées aux déplacements du robot. Contient également des  
                        méthodes reliées au PWM puisque le déplacement du robot utilise le PWM.

-Piezo.* :              Contient la classe Piezo permettant de contrôler le piezo du robot. Contient également    
                        la liste des sons disponibles.

-son.* :                Contient la classe Son contenant les paramètres d'un son comme la fréquence, la note
                        et la valeur du registre à modifier pour obtenir cette fréquence.

-coin*.cpp :            Contient les méthodes permettant de faire un segment du parcours.

-robot1.cpp :           Contient le comportement global du robot1. Contient le main(). 

-robot2.cpp :           Contient le comportement global du robot2. Contient le main().

-test.cpp :             Contenu variable dépendant des tests à exécuter. 

------------------------------------------------------------------------------------------------------------

Branchement nécessaire des fils:
 _______________________________
|                               |
|            Roues              |
|_______________________________|
|                               |
|    D4 - enable gauche         |
|    D5 - enable droite         |
|    D6 - direction gauche      |
|    D7 - direction droite      |
|_______________________________|
|                               |
|     Conversion analogique     |
|_______________________________|
|                               |
|           A0 - IR1            |
|           A1 - IR2            |
|           A2 - IR3            |
|           A3 - IR4            |
|           A4 - IR5            |
|_______________________________|
|                               |
|            Buzzer             |
|_______________________________|
|                               |
|          B2 - noir            |
|          B3 - rouge           |
|_______________________________|
|                               |
|         Communication         |
|_______________________________|
|                               |
|           B0 & B1             |
|_______________________________|
|                               |
|           Capteurs            |
|_______________________________|
|                               |
|            PORTC              |
|      De gauche a droite       |
|     face a face au robot:     |
|       C4,C5,C3,C2,C1,C0       |
|_______________________________|