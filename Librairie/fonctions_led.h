/*  fonctions_led.h : En-tete des fonctions pour le controle des leds
    Auteur: Olivier Leclerc 1954056
    Date: 20 fevrier 2019
*/

#pragma once
#include <avr/io.h> 
#define F_CPU   8000000UL
#include <util/delay.h>
//bit1 est le MSB

//La fonction ambre fait alterner les bits du port passe en parametre entre 10 et 01. 
void ambre(volatile unsigned char &port=PORTB, uint8_t bit1=1,uint8_t bit2=0);
//La fonction vert met les bits du port passe en parametre a 10
void vert(volatile unsigned char &port=PORTB, uint8_t bit1=1,uint8_t bit2=0);
//La fonction rouge met les bits du port passe en parametre a 01
void rouge(volatile unsigned char &port=PORTB, uint8_t bit1=1,uint8_t bit2=0);
//La fonction éteint met les bits du port passe en parametre a 00
void eteint(volatile unsigned char &port=PORTB, uint8_t bit1=1,uint8_t bit2=0);
//La fonction allume la DEL voulue du breadboard
void allumerDEL(uint8_t pos);
//La fonction eteint la DEL voulue du breadboard
void eteindreDEL(uint8_t pos);
//La fonction eteint toutes les DEL du breadboard
void eteindreDELs();