#include <includeAll.h>
volatile uint8_t compteur_1 =0;
volatile bool local = false;
volatile bool fini = false;
//PWM qui émet la bonne fréquence d'onde infrarouge.
void PWM_Com(){
    DDRB |= 0b00001000; // Le 4e bit est en mode sortie pour OC0A 
    TCCR0A = (1 << COM0A0) | (1<< WGM01); //CTC 
    TCCR0B = (1<< CS00); // No prescaler
    OCR0A = 104; // (8 000 000 / 2 * 38 000) - 1 : Calcul  pour fréquence de 38 khz
}
//Arrête le PWM_Com
void arreterPWM(){
    //COM0A0 est le bit permettant de remettre le port à son utilisation par défaut
    TCCR0A ^= (1<<COM0A0); 
    
}
//Envoi d'un 1 en utilisant le protocole SIRC
void envoyer1(){
    PWM_Com();
    _delay_ms(1.2);
    arreterPWM();
    _delay_ms(0.6);
}
//Envoi d'un 0 en utilisant le protocole SIRC
void envoyer0(){
     PWM_Com();
    _delay_ms(0.6);
    arreterPWM();
    _delay_ms(0.6);
}
//Envoi de la séquence annonçant l'envoi d'une valeur
void envoyerStart(){
     PWM_Com();
    _delay_ms(2.4); 
    arreterPWM();
    _delay_ms(0.6);
}

//Envoi d'une valeur en utilisant le protocole SIRC
void envoyer(uint8_t valeur){
    envoyerStart();
    uint8_t valeurBin[4];
    //Valeur
    for(int i =0;i<4;i++){
        valeur%2 ==0?valeurBin[i]=0:valeurBin[i]=1;
        valeur/=2;
    }

     for(int i =0;i<4;i++){
        if(valeurBin[i]==1)
            envoyer1();
        else
            envoyer0();
    }
    //Fin commande
    envoyer0();
    envoyer0();
    envoyer0();
    //Adresse        }
    envoyer1();
    envoyer0();
    envoyer0();
    envoyer0();
    envoyer0();

}
//Réception d'un 0 suivant le protocole SIRC
void recevoir0(uint16_t &valeur, uint8_t decalage){
    valeur &= ~(1 << (decalage));
    _delay_ms(0.6);

}
//Réception d'un 1 suivant le protocole SIRC
void recevoir1(uint16_t &valeur, uint8_t decalage){
    valeur |= (1 << (decalage));
    _delay_ms(1.2);

}
//Incrémente la variable volatile compteur_1 de 0 à 9
void incrementation(){
    if(compteur_1 == 9)
        compteur_1 = 1;
    else
        compteur_1 ++ ;
}
//Interruption causée par le bouton
//Si pesé, incrémente le compteur et part la minuterie
ISR ( INT0_vect ) {
  // laisser un delai avant de confirmer la réponse du
  // bouton-poussoir: environ 30 ms (anti-rebond)
  _delay_ms ( 30 );
  // se souvenir ici si le bouton est pressé ou relâché
    // changements d'états tels que ceux de la
    if(PIND & 0x04){
        local = true;
        incrementation();
        partirMinuterie0('A', 1024);
    }
}
//Interruption causée par la comparaison A de la minuterie 0
//Si la minuterie est active depuis 2 secondes, arrête la minuterie
ISR(TIMER0_COMPA_vect) {
	 if (dureeAtteinte0(2)){
        disableBouton(0);
        fini = true;
        arreterMinuterie0();
     }
      
}
//Réception d'une valeur suivant le protocole SIRC ou de l'incrémentation
// d'un compteur et retourne cette valeur
uint16_t recevoir(){
    uint16_t valeurRecue=0;
    local =false;
    fini = false;
    compteur_1 = 0;
    enableBouton(3,0);
    while((valeurRecue<128 || valeurRecue >137) && !local){
        valeurRecue = 0;
        DDRB = 0b11111110; // On reçoit les valeurs par PINB0
        uint8_t compteur = 0;

        //Réception de la séquence de démarrage
        while(compteur != 5 && !local){
            if(!(PINB & 0b00000001)){
                compteur++;
                _delay_ms(0.6);
            }else{
                compteur = 0;
            }
        }
        _delay_ms(0.6);
        //Réception de la commande
        for(uint8_t i = 0 ; i < 12 ; i ++){
            _delay_ms(0.6);
            if(PINB & 0b00000001)
                recevoir0(valeurRecue, i);
            else
                recevoir1(valeurRecue, i);
        }
    }
    while(!fini && local);
    if(fini){
        valeurRecue = compteur_1 + 128;
    }
    return valeurRecue;
    
}