#include "Piezo.h"
   //Retourne le son associe a la note passee en parametre de la liste de sons 
Son Piezo::getSon(uint8_t note){
    return sons[note-45]; //45 est la note minimale
}
//Retourne vrai si la note est dans la liste de sons
bool Piezo::estUneNote(uint8_t note){
    return note <= 81 && note >= 45; //81 est la note maximale et 45 est la note minimale
}
//Émets le son passé en paramètre
void Piezo::emmettreSon(Son son){

    TCCR0A = (1 << COM0A0) | (1<< WGM01); //Toggle on match, CTC
    TCCR0B = (1<<CS02); //Prescaler de 256: Cest le prescaler le plus petit permettant de couvrir toutes les notes avec le timer 0
    OCR0A = son.getValeurRegistre(); //Permet de definir la frequence du buzzer
}
//Arrête le son
void Piezo::arreterSon(){
    TCCR0A ^= (1<<COM0A0); //Remets le port a son operation normale

}

