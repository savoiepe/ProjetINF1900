/*  fonctions_led.cpp : Fonctions pour le controle de la LED
    Auteur: Olivier Leclerc 1954056 et Pierre-Emmanuel Savoie 1952752
    Date: 20 fevrier 2019
*/
#include "fonctions_led.h"
/* Fonction qui donne la couleur ambree a la led si le port est connecte a la led
    param port  Port sur lequel la led est connectee
    param bit1  Premier bit de la led
    param bit2  Deuxieme bit de la led
*/
void ambre(volatile unsigned char &port, uint8_t bit1,uint8_t bit2){  //bit1 plus significatif
    port |= (1 << bit1); //Mets le bit1 a 1
    port &= ~(1 << bit2); //Mets le bit2 a 0
    _delay_ms(4);
    port |= (1 << bit2); //Mets le bit2 a 1
    port &= ~(1 << bit1); //Mets le bit1 a 0
    _delay_ms(2);
}
/* Fonction qui donne la couleur vert a la led si le port est connecte a la led
    param port  Port sur lequel la led est connectee
    param bit1  Premier bit de la led
    param bit2  Deuxieme bit de la led
*/
void vert(volatile unsigned char &port, uint8_t bit1,uint8_t bit2){
port |= (1 << bit1); //Mets le bit1 a 1
port &= ~(1 << bit2); //Mets le bit2 a 0
}
/* Fonction qui donne la couleur rouge a la led si le port est connecte a la led
    param port  Port sur lequel la led est connectee
    param bit1  Premier bit de la led
    param bit2  Deuxieme bit de la led
*/
void rouge(volatile unsigned char &port, uint8_t bit1,uint8_t bit2){
port |= (1 << bit2); //Mets le bit2 a 1
port &= ~(1 << bit1); //Mets le bit1 a 0
}
/* Fonction qui donne la éteint la led si le port est connecte a la led
    param port  Port sur lequel la led est connectee
    param bit1  Premier bit de la led
    param bit2  Deuxieme bit de la led
*/
void eteint(volatile unsigned char &port, uint8_t bit1,uint8_t bit2){
port &= ~(1 << bit1) & ~(1 << bit2); //Mets le bit1 et le bit2 a 0
}
/*
Fontion qui allume une DEL sur le breadboard en fonction du parametre recu
*/
void allumerDEL(uint8_t pos){
    PORTC |= (1 << pos);
}

/*
Fontion qui eteind une DEL sur le breadboard en fonction du parametre recu
*/

void eteindreDEL(uint8_t pos){
    PORTC &= ~(1 << pos);
}

/*
Fontion qui eteind toutes les DELs en meme temps
*/

void eteindreDELs(){
    eteindreDEL(0);
    eteindreDEL(1);
    eteindreDEL(2);
    eteindreDEL(3);
    eteindreDEL(4);
}