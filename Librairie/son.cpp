#include "son.h"

//Retourne la note associée au son
uint8_t Son::getNote(){
    return note_;
}
// Retourne la fréquence de la note
uint16_t Son::getFrequence(){
    return frequence_;
}
//Retuorne la valeur à utiliser pour OCR0A
uint8_t Son::getValeurRegistre(){
    return valeurRegistre_;
}


