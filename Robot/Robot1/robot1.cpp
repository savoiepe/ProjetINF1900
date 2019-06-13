#include <includeAll.h>
#include <fonctions.h>
/*
Ce fichier contient le code principal du robot1. Il permet au robot de recevoir
son coin de départ. En fonction de celui-ci, le robot change d'états:

Tableau de changement d'états
_____________________________


+--------------+-------+------------+--------+
| CurrentState | Input | Next State | Output |
+--------------+-------+------------+--------+
| None         | 1     | COIN1      | X      |
| None         | 2     | COIN2      | X      |
| None         | 3     | COIN3      | X      |
| None         | 4     | COIN4      | X      |
| COIN1        | X     | COIN2      | X      |
| COIN2        | X     | COIN3      | X      |
| COIN3        | X     | COIN4      | X      |
| COIN4        | X     | COIN1      | X      |
+--------------+-------+------------+--------+


Ports utilisés|     Mode|       Utilité              |
------------------------------------------------------
        A0-A4 |      Out | IR1-IR5 (Capteurs)
------------------------------------------------------
        B0-B1 |      In  | Récepteur infrarouge
------------------------------------------------------
        B2-B3 |      Out | Buzzer Piezo (PWM minuterie 0)
------------------------------------------------------
        C0-C5 |      Out | LEDs capteurs
------------------------------------------------------
        D3    |      In  | Bouton
------------------------------------------------------
        D4-D7 |      Out | Roues (PWM minuterie 2)
-----------------------------------------------------|

*/
enum states {COIN1,COIN2,COIN3,COIN4}; //États possibles après réception
volatile uint8_t state; // État courant
volatile uint8_t stateDebut; //État de départ


//Fonctions principale du robot1: Permet d'effectuer le trajet complet.
int main(){
    //Initialisation
    DEBUG_INIT;
    DDRC = 0xFF;
    enableConversion();
    enableBouton(3, 0 );
    // Déterminer le premier coin:
    uint8_t coinDebut = -1;
    while(coinDebut<1 || coinDebut>4){
        coinDebut = recevoir() -128;
    }
    
    DEBUG_VAR16(coinDebut);
    //Allume la del correspondant à la valeur passée
    allumerDEL(coinDebut-1);
    _delay_ms(3000);
    state = coinDebut-1; // De 0 à 3
    stateDebut = state;

    do{
        switch(state){
            case COIN1: //Les 9 points
                if(state != stateDebut)
                    tournerGaucheCapteur();
                fonctionCoin1();
                state = COIN2;
                break;
            case COIN2: //Les deux courbes
                if(state != stateDebut)
                    tournerGaucheCapteur();
                fonctionCoin2();
                state = COIN3;
                break;
            case COIN3: //Les 4 segmets similaires
                if(state != stateDebut)
                    tournerGaucheCapteur();
                fonctionCoin3();
                state = COIN4;
                break;
            case COIN4://Les rectangles du bas
                if(state != stateDebut)
                    tournerGaucheCapteur();
                fonctionCoin4();
                state = COIN1;
                break;
        }
    }while(state != stateDebut);
    //Procédure de fin
    Piezo piezo;
    piezo.emmettreSon(piezo.getSon(81));
    _delay_ms(2000);
    piezo.arreterSon();
}
