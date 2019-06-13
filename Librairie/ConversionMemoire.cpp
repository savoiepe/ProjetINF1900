#include "ConversionMemoire.h"

//Fonction qui ne prend pas de parametre et qui active la conversion Analogique
void enableConversion(){
    // ADC mux : reference analogique externe
	//           ajuste a droite
	ADMUX = (0 << REFS1) | (0 << REFS0) | (0 << ADLAR) | (0 << MUX4) |
		(0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);

	// ADC Status and Control Register A : 
	//  Active le convertisseur mais sans demarrer de conversion pour l'instant.
	//  Pas de declanchement automatique et aucune interruption suivant
	//  la fin d'une convertion. Division de l'horloge par 64 (il faudra
	//  donc 13 cycles du convertisseur * 64 pour terminer une conversion
	//  soit 832 cycles d'horloge soit 104 micro-secondes
	ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) |
		(0 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
}

//Fonction qui ne prend pas de parametre et qui rend la conversion inactive
void disableConversion(){
    //rendre la conversion inactive
    ADCSRA = 0 << ADEN;
}

/* Fonction de conversion conversionAnalogique
    param pos	position sur le PORTA (de 0 a 7)
*/
uint8_t conversionAnalogique(uint8_t pos){
    uint16_t adcVal;

	// Garder les bits de ADMUX intacts, sauf les bit permettant	
	// la selection de l'entree
	ADMUX &= ~((1 << MUX4) | (1 << MUX3) |
		(1 << MUX2) | (1 << MUX1) | (1 << MUX0));

	// selectionner l'entree voulue
	ADMUX |= ((pos & 0x07) << MUX0);

	// demarrer la conversion
	ADCSRA |= (1 << ADSC);

	// Attendre la fin de la conversion soit 13 cycles du convertisseur.
	while (!(ADCSRA & (1 << ADIF)));

	// important: remettre le bit d'indication de fin de cycle a zero 
	// pour la prochaine conversion ce qui se fait en l'ajustant a un.
	ADCSRA |= (1 << ADIF);

	// Aller chercher le resultat sur 16 bits.
	adcVal = ADCL;
	adcVal += ADCH << 8;

	// resultat sur 8 bits
    return uint8_t(adcVal >> 2);
}
void initialisationUART ( void ) {

        // 2400 bauds. Nous vous donnons la valeur des deux

        // premier registres pour vous éviter des complications

        UBRR0H = 0;

        UBRR0L = 0xCF;

        // permettre la reception et la transmission par le UART0

        UCSR0A =0 ;

        UCSR0B = (1<<RXEN0)|(1<<TXEN0) ;

        // Format des trames: 8 bits, 1 stop bits, none parity

        UCSR0C = (1<<UCSZ00)|(1<<UCSZ01) ;

}

//Renvoie l'information inscrite dans le robot vers l'ordinateur.
void transmissionUART ( uint8_t donnee ) { 

    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = donnee;    

}

/* Fonction qui lit la ce qui se trouve dans la memoire
	Param adresse	Adresse a laquel on veut ecrire
	Param  donnee	pointeur vers un array de char que l'on veut ecrire en memoire
*/
void ecrireMemoire(uint16_t adresse, uint8_t* donnee){
	Memoire24CXXX memoire = Memoire24CXXX();
	memoire.ecriture(adresse, donnee, sizeof(*donnee));
}

/* Fonction qui lit la ce qui se trouve dans la memoire */
void lireMemoireEtTransmission(){
    initialisationUART();
    Memoire24CXXX memoire = Memoire24CXXX();
    uint8_t valeurlue=0xFF;
    uint8_t adresse =0x00;
    while(true ){
        memoire.lecture(adresse,&valeurlue);
        transmissionUART(valeurlue);
        adresse++;
    }
}

/* Fonction qui lit la ce qui se trouve dans la memoire */
void lireMemoire(uint16_t adresse, uint8_t* donnee){
    Memoire24CXXX memoire = Memoire24CXXX();
	memoire.lecture(adresse,donnee);
}
