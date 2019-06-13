#pragma once
#include "son.h"
#include <avr/io.h>
//Liste des notes: _ signifies octave - , le chiffre qui suit est le chiffre de l'octave , d signifie diese
// Ex: 
//Octave -2
#define A_2 45
#define Ad_2 46
#define B_2 47
//Octave -1
#define C_1 48
#define Cd_1 49
#define D_1 50
#define Dd_1 51
#define E_1 52
#define F_1 53
#define Fd_1 54
#define G_1 55
#define Gd_1 56
#define A_1 57
#define Ad_1 58
#define B_1 59
//Octave 0
#define C0 60
#define Cd0 61
#define D0 62
#define Dd0 63
#define E0 64
#define F0 65
#define Fd0 66
#define G0 67
#define Gd0 68
#define A0 69
#define Ad0 70
#define B0 71
//Octave 1
#define C1 72
#define Cd1 73
#define D1 74
#define Dd1 75
#define E1 76
#define F1 77
#define Fd1 78
#define G1 79
#define Gd1 80
#define A1 81

// reference : http://www.tonalsoft.com/pub/news/pitch-bend.aspx 

//Classe qui definit le comportement du piezo pour emettre des sons
class Piezo{
    public:
    //Constructeur de Piezo qui initialise le port B en mode sortie pour les pins 3 et 4
    Piezo(){
        DDRB |= (1<<2) | (1<<3); //DDRB = XXXX 11XX
    }
    //Retourne le son associe a la note passee en parametre de la liste de sons 
    Son getSon(uint8_t note);
    //Retourne vrai si la note est dans la liste de sons
    bool estUneNote(uint8_t note);
    //Emets le son passe en parametre
    void emmettreSon(Son son);
    //Arrete le son
    void arreterSon();
    private:
    //La liste des sons possibles pour le robot
    const Son sons[37] = { {45,110},{46,116},{47,123},{48,131},{49,149},{50,147},{51,156},{52,165},{53,175},{54,185},
                {55,196},{56,208},{57,220},{58,233},{59,247},{60,262},{61,277},{62,294},{63,311},{64,330},
                {65,349},{66,370},{67,392},{68,415},{69,440},{70,466},{71,494},{72,523},{73,554},{74,587},
                {75,622},{76,659},{77,698},{78,740},{79,784},{80,831},{81,880}
                    };
    
};