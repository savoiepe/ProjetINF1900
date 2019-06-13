#include "debug.h"

//Transmet un uint8_t en character au UART
void transInt2char(uint8_t integer){
    uint8_t dividende = 100;
    do{
        uint8_t character = integer / dividende +'0';
        transmissionUART(character);
        integer -= integer / dividende  * dividende;
        dividende /= 10;
    }while(integer!=0);
}
//Transmet un uint16_t en charactère au UART
void transInt2char16(uint16_t integer){
    uint16_t dividende = 10000;
    do{
        uint8_t character = integer / dividende + '0' ;
        transmissionUART(character);
        integer -= integer / dividende  * dividende;
        dividende /= 10;
    }while(integer!=0);
}
//Transmet la valeur d'une variable uint8_t et la ligne à laquelle
//la fonction est appelée
void debugValeur(uint8_t valeur, uint8_t ligne){
    //Transmet valeur
    char valeurs[9] = "Valeur: ";
    for(int i=0;i<9;i++){
        transmissionUART(valeurs[i]);
    }
    transInt2char(valeur);
    //Transmet ligne
    char lignes[9] = " Ligne: ";
    for(int i=0;i<9;i++){
        transmissionUART(lignes[i]);
    }
    transInt2char(ligne);
    //Transmet espace
    transmissionUART('\n');
}
//Transmet la valeur d'une variable uint16_t et la ligne à laquelle
//la fonction est appelée
void debugValeur16(uint16_t valeur, uint8_t ligne){
    //Transmet valeur
    char valeurs[9] = "Valeur: ";
    for(int i=0;i<9;i++){
        transmissionUART(valeurs[i]);
    }
    transInt2char16(valeur);
    //Transmet ligne
    char lignes[9] = " Ligne: ";
    for(int i=0;i<9;i++){
        transmissionUART(lignes[i]);
    }
    transInt2char(ligne);
    //Transmet espace
    transmissionUART('\n');
}
//Initialise le UART pour permettre le débogage
void debugInitialisation(){
    initialisationUART();
    //Transmet message d'initialisation
    char messageInit[17] = "Debut Debogage:\n";
    for(int i=0;i<17;i++){
        transmissionUART(messageInit[i]);
    }
  
}
//Affiche la ligne à laquelle la fonction est appelée
void erreur(){
    char messageErreur[14] = "Erreur ligne ";
    for(int i=0;i<14;i++){
        transmissionUART(messageErreur[i]);
    }
    transmissionUART(__LINE__);

}