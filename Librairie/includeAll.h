/*Fichier contenant toutes les constantes concernant les vitesses des roues et
les etats des capteurs reutilisees dans le code afin d'ameliorer la lisibilité*/

#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU   8000000UL
#include <util/delay.h>
#include "fonctions_led.h"
#include "ConversionMemoire.h"
#include "Interrupts.h"
#include "capteurs.h"
#include "moteur.h"
#include "debug.h"
#include "Piezo.h"
#include "son.h"
#include "communication.h"

#define VITESSE 130
#define VITESSE_FAIBLE 100
#define RIGHT 0b01000
#define FAR_RIGHT 0b10000
#define LEFT 0b00010
#define FAR_LEFT 0b00001
#define CENTER 0b00100
#define TOURNANT_GAUCHE_1 0b00111
#define TOURNANT_GAUCHE_2 0b01111
#define TOURNANT_GAUCHE_3 0b00011
#define TOURNANT_DROITE_1 0b11100
#define TOURNANT_DROITE_2 0b11110
#define TOURNANT_DROITE_3 0b11000
#define FAR_BOTH 0b10001
#define BOTH_RIGHT 0b11000
#define BOTH_LEFT 0b00011
#define ALL 0b11111
#define NONE 0b0
