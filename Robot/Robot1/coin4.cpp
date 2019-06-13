#include <fonctions.h>

/*
+--------------+------------+-------------------+
| CurrentState | Next State | 	   Fonction 	|
+--------------+------------+-------------------+
| LIGNE0       | CARRE1     | suivreLigne() 	|
| CARRE1       | LIGNE2     | suivreCarre() 	|
| LIGNE2       | CARRE3     | suivreLigne() 	|
| CARRE3       | LIGNE4     | suivreCarre() 	|
| LIGNE4       | CARRE5     | suivreLigne() 	|
| CARRE5       | LIGNE6     | suivreCarre()  	|
| LIGNE6       | FIN        | suivreLigneCoin() |
| CARRE5       | X          | return true 		|
+--------------+------------+-------------------+
*/

bool fonctionCoin4(){
    DEBUG_INIT;
    enum statesC4 {LIGNE0,CARRE1,LIGNE2,CARRE3,LIGNE4,CARRE5,LIGNE6,FIN};
    statesC4 stateC4 = LIGNE0; 
    bool enableAll = true;

    while(true)
    {
        switch(stateC4){
            case LIGNE0: 
                if(suivreLigne(enableAll)){
                    stateC4 = CARRE1;
                }
                break;
            case CARRE1:
                if(suivreCarre(enableAll)){
                    stateC4 = LIGNE2;
                }
                break;
            case LIGNE2:
                if(suivreLigne(enableAll)){
                    stateC4 = CARRE3;
                }
                break;
            case CARRE3:
                if(suivreCarre(enableAll)){
                    stateC4 = LIGNE4;
                }
                break;
            case LIGNE4:
                if(suivreLigne(enableAll)){
                    stateC4 = CARRE5;
                }
                break;
            case CARRE5:
                if(suivreCarre(enableAll)){
                    stateC4 = LIGNE6;
                }
                break;
            case LIGNE6:
                if(suivreLigneCoin()){
                    stateC4 = FIN;
                }
                break;
            case FIN:
                avancer(VITESSE);
                _delay_ms(400);
                avancer(0);
                return true;
        }
    }
}