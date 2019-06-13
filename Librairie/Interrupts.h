#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU   8000000UL
#include <util/delay.h>

void enableBouton(uint8_t enableCase, uint8_t vect);

void disableBouton(uint8_t vect);

bool dureeAtteinte0(double duree, double prescaler = 1024);

bool dureeAtteinte2(double duree, double prescaler = 1024);

void partirMinuterie0(char compare, int prescaler);

void partirMinuterie2(char compare);

void arreterMinuterie0();

void arreterMinuterie2();