#pragma once
#include <avr/io.h> 
#include <avr/interrupt.h>
#define 	F_CPU   8000000UL
#include <util/delay.h>
#include "memoire_24.h"

void initialisationUART ( void );

void transmissionUART ( uint8_t donnee );

void enableConversion();

void disableConversion();

uint8_t conversionAnalogique(uint8_t pos);

void ecrireMemoire(uint16_t adresse, uint8_t* donnee, const uint8_t longueur);

void ecrireParUsb();

void lireMemoireEtTransmission();

void lireMemoire(uint16_t adresse, uint8_t* donnee);