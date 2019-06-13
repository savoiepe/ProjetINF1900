#include <fonctions.h>
volatile int compteur = 0;
int compteurDroit = 0, compteurGauche = 0;
bool estDroit = false, estGauche = false;

ISR(TIMER2_COMPB_vect){
	compteur++;
}

/*
fonction qui parcours la ligne au centre du trajet;
Cette fonction part un timer lorsque toutes les capteurs detectent la premiere ligne
Par la suite la valeur du timer est sauvegarder dans les variables compteurDroit et 
compteurGauche lors la ligne du mm bord est detecter.Finalement, la fonction arrete
lorsque les deux lignes sont detecter
*/
bool detectionLigne(){
	uint8_t positionnement = checkLignes();
    switch(positionnement){
        case CENTER:
            avancer(VITESSE_FAIBLE);
            break;
        case LEFT:
        case FAR_LEFT:
            ajustementDroite(VITESSE_FAIBLE + 50);
            break;
        case RIGHT:
        case FAR_RIGHT:
            ajustementGauche(VITESSE_FAIBLE + 50);
            break;
        case TOURNANT_GAUCHE_1:
        case TOURNANT_GAUCHE_2:
        case TOURNANT_GAUCHE_3:
        	if(!estGauche && compteur > 0){
        		estGauche = true;
        		compteurGauche = compteur;
        	}
        	if(estGauche && estDroit)
        		return true;
        	break;
        case TOURNANT_DROITE_1:
        case TOURNANT_DROITE_2:
        case TOURNANT_DROITE_3:
        	if(!estDroit && compteur > 0){
        		estDroit = true;
        		compteurDroit = compteur;
        	}
        	if(estDroit && estGauche)
        		return true;
        	break;
        case ALL:
            partirMinuterie2('B');
            _delay_ms(180);
            break;
    }
    return false;
}

//Fonction qui analyse les compteurDroit et compteurGauche afin de choisir quel ligne nous venons de parcourir et retourne cette valeur
uint8_t choixDeLigne(){
	if (compteurGauche < compteurDroit ){
		compteurDroit -= (int)(2.5*compteurGauche);
		if(compteurDroit > 0){
			return 0;   //ligne 1
		}
		return 1;       //ligne 2
	}
	else if(compteurDroit < compteurGauche){
		compteurGauche -= (int)(2.5*compteurDroit);
		if(compteurGauche > 0){
			return 2;   //ligne 3
		}
		return 3;       //ligne 4
	}
}

/*
+----------------+------------+---------------------------------------------------+
| CurrentState   | Next State | 					Fonction					  |
+----------------+------------+---------------------------------------------------+
| LIGNE0         | COIN1      | suivreLigneArret()     							  |
| ATTENDRE1      | COIN1      | loop infini en attendant que le robot soit placer |
| DETECTIONLIGNE | COIN1      | detectionLigne() et choixDeLigne()     			  |
| ATTENDRE2      | COIN1      | loop infini en attendant que le robot soit placer |
| LIGNE2         | COIN1      | suivreLigneCoin()							      |
| FIN            | COIN1      | placer le robot sur l'axe de rotation 		      |
+----------------+------------+---------------------------------------------------+
*/
bool fonctionCoin3(){
    enum statesC3 {LIGNE0,ATTENDRE1,DETECTIONLIGNE,ATTENDRE2, LIGNE2,FIN};
    statesC3 stateC3 = LIGNE0;
    bool robotPlacer = false;
    
    while(true) {
        switch(stateC3){
            case LIGNE0:
                while (!suivreLigneArret()){}
                    stateC3 = ATTENDRE1;
                    avancer(0);
                    eteindreDELs();
                break;
            case ATTENDRE1:
                robotPlacer = false;
                while(!robotPlacer){
                    if (PIND & 0x04){
                        _delay_ms(10);
                        if (PIND & 0x04)
                            robotPlacer = true;
                    }
                }
                stateC3 = DETECTIONLIGNE;
                break;
            case DETECTIONLIGNE:
                while(!detectionLigne()){}
                arreterMinuterie2();
                _delay_ms(200);
                avancer(0);
                eteindreDELs();
                allumerDEL(choixDeLigne());
                stateC3 = ATTENDRE2;
                break;
            case ATTENDRE2:
                robotPlacer = false;
                while(!robotPlacer){
                    if (PIND & 0x04){
                        _delay_ms(10);
                        if (PIND & 0x04)
                            robotPlacer = true;
                    }
                }
                stateC3 = LIGNE2;
                eteindreDEL(choixDeLigne());
                break;
            case LIGNE2:
                if(suivreLigneCoin())
                    stateC3 = FIN;
                break;
            case FIN:
                avancerAxeRotation(VITESSE);
                return true;
        }
    }
}