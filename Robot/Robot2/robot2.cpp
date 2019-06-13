/*Ports utilisés:
PORTB3 : Mode sortie pour PWM
PIND3 : Mode entrée pour bouton
*/

#include <includeAll.h>

volatile uint8_t compteur_2; // Compteur incrémenté de 0 à 9
volatile bool fini; // Minuterie finie?
volatile bool envoi = false; //Est-ce que le robot envoit en ce moment?

//Fonction qui incrémente la valeur d'un compteur de 0 à 9.
void incrementation(){
    if(compteur_2 == 9)
        compteur_2 = 1;
    else
        compteur_2 ++ ;
    DEBUG_VAR(compteur_2);
}
//Interruption causée par le bouton
ISR ( INT0_vect ) {
  // laisser un delai avant de confirmer la réponse du
  // bouton-poussoir: environ 30 ms (anti-rebond)
  _delay_ms ( 30 );
  // se souvenir ici si le bouton est pressé ou relâché
    // changements d'états tels que ceux de la
    if(PIND & 0x04){
        if(envoi){
            envoi = false;
            compteur_2 = 0;
        }
        incrementation();
        partirMinuterie2('A');
    }
}
//Interruption causée par la minuterie 2.
ISR(TIMER2_COMPA_vect) {
	 if (dureeAtteinte2(2)){
        disableBouton(0);
        fini = true;
        arreterMinuterie2();
     }
      
}
//Fonction principale du robot 2. 
int main(){
    DEBUG_INIT;
    DDRB = 0xFF; //Port B en mode sortie pour envoyer
    enableBouton(3,0);
    while(true){
        fini = false;
        while(!fini){
            //Attente de l'interruption du bouton
        }
        DEBUG_VAR(compteur_2);
        envoi = true;
        enableBouton(3,0); //Permet de renvoyer une nouvelle valeur
        while(envoi){ 
            envoyer(compteur_2);
        }
    
    }

    
    
}