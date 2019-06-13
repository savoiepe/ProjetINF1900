#pragma once
#include <avr/io.h>
#include "Interrupts.h"
#define F_CPU   8000000UL

//Classe qui definit les proprietes d'un son dont sa note, sa frequence et la valeur a laquelle on doit initialiser OCR0A
class Son{
    public:
    //Constructeur
    Son(uint8_t note, uint16_t frequence): note_(note), frequence_(frequence){
        valeurRegistre_ = 15625/frequence_-1; //8 000 000 / 2 / 256 / frequence -1 (256 est le prescaler et 8 000 000 est la frequence CPU)
    }
    //Retourne la note associee au son
    uint8_t getNote();
    //Retourne la frequence de la note
    uint16_t getFrequence();

    //Retourne la valeur a utiliser pour OCR0A
    uint8_t getValeurRegistre();

    private:
    uint8_t note_;
    uint16_t frequence_;
    uint8_t valeurRegistre_;
};

