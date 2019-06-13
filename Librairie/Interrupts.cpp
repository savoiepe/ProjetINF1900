/*Cette section contient des fonctions permettant de partir/arreter des minuteries
et d'activer des interruptions externes sur le bouton-poussoir*/

#include "Interrupts.h"
volatile uint8_t compteur0 = 0;
volatile uint8_t compteur2 = 0;

/*Branchement des fils:
    D4 - enable gauche
    D5 - enable droite
    D6 - direction gauche
    D7 - direction droite*/

/*Fonction pour enable les interruptions externes INT0, INT1, INT2
    param enableCase: type d'enable {0 = low level, 1 = any edge, 2 = falling edge, 3 = rising edge}
    param vect: type d'interruption {0 = INT0, 1 = INT1, 2 = INT2}*/
void enableBouton(uint8_t enableCase, uint8_t vect){
    cli();
    switch(vect){
        case 0: EIMSK |= (1 << INT0); break;
        case 1: EIMSK |= (1 << INT1); break;
        case 2: EIMSK |= (1 << INT2); break;
    }
    switch(enableCase){
        //Low level
        case 0 : EICRA &= ~(11 << vect*2); break;
        //Any edge i
		case 1: EICRA |= (01 << vect * 2); EICRA &= ~(10 << vect * 2); break;
        //Falling edge
        case 2 : EICRA |= (10 << vect*2);EICRA &= ~(01 << vect*2); break;
        //Rising edge
        case 3 : EICRA |= (11 << vect*2); break;
    }
    sei();
}

/*Fonction pour disable les interruptions externes INT0, INT1, INT2 avec differentes types d'enable
    param vect: type d'interruption {0 = INT0, 1 = INT1, 2 = INT2}*/
void disableBouton(uint8_t vect){
    cli();
    switch(vect){
        case 0: EIMSK &= ~(1 << INT0); break;
        case 1: EIMSK &= ~(1 << INT1); break;
        case 2: EIMSK &= ~(1 << INT2); break;
    }
    sei();
}

/*Fonction verifie si la duree voulue a ete atteinte par la minuterie 0
    param duree: duree en seconde pour laquelle nous voulons faire marcher la minuterie
    param prescaler: la valeur du prescaler de la minuterie avec 1024 comme valeur de defaut*/
bool dureeAtteinte0(double duree, double prescaler){
    double nbInterrupts = (8000000*duree)/(prescaler * 0xFF);
    compteur0++;
    if (compteur0 >= nbInterrupts){
        compteur0 = 0;
        return true;
    }
    return false;
}

/*Fonction verifie si la duree voulue a ete atteinte par la minuterie 2
    param duree: duree en seconde pour laquelle nous voulons faire marcher la minuterie
    param prescaler: la valeur du prescaler de la minuterie avec 1024 comme valeur de defaut*/
bool dureeAtteinte2(double duree, double prescaler){
    double nbInterrupts = (8000000*duree)/(prescaler * 0xFF);
    compteur2++;
    if(compteur2 >= nbInterrupts){
        compteur2 = 0;
        return true;
    }
    return false;
}

/*Fonction qui active une minuterie avec le Timer/Counter0
    param duree: nombre de cycles total de la minuterie (a diviser par 1024)
    
Utilisation:
    ISR(TIMER0_COMPA_vect) {
	    if (dureeAtteinte0(x))
            ...
    }*/
void partirMinuterie0(char compare, int prescaler){
    sei();
    TCNT0 = 0;
    if (compare == 'A'){
        OCR0A = 0xFF;
        TIMSK0 |= (1 << OCIE0A); //Compare à 0CR0A
    }
    else if (compare == 'B'){
        OCR0B = 0xFF;
        TIMSK0 |= (1 << OCIE0B); //Compare à 0CR0B
    }
    TCCR0A = 0;
    if(prescaler==1024){
        TCCR0B |= (1 << CS02) | (1 << CS00); //prescaler 1024
    }
    else if(prescaler==0){
        TCCR0B |= (1 << CS00); //prescaler none
    }
	TCCR0B |= (1 << WGM02); //Mode CTC
    compteur0 = 0;
}

/*Fonction qui active une minuterie avec le Timer/Counter2
    param duree: nombre de cycles total de la minuterie (a diviser par 1024)
    
Utilisation:
    ISR(TIMER2_COMPA_vect) {
	    if (dureeAtteinte2(x))
            ...
    }*/
void partirMinuterie2(char compare){
    sei();
    TCNT2 = 0 ;
    if (compare == 'A'){
        OCR2A = 0xFF;
        TIMSK2 = (1 << OCIE2A) ; //Compare à 0CR2A
    }
    else if (compare == 'B'){
        OCR2B = 0xFF;
        TIMSK2 = (1 << OCIE2B) ; //Compare à 0CR2B
    }

    TCCR2A = 0;
    TCCR2B =  (1 << CS22) | (1 << CS21) | (1 << CS20) | (1 << WGM22); //Mode CTC, prescale 1024
    compteur2 = 0;
}

/*Fonction qui desactive le Timer/Counter0 en empechant de comparer*/
void arreterMinuterie0(){
    TIMSK0 = 0;
}

/*Fonction qui desactive le Timer/Counter2 en empechant de comparer*/
void arreterMinuterie2(){
    TIMSK2 = 0;
}