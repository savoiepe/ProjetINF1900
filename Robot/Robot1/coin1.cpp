#include <fonctions.h>

//Fonction permettant de suivre la ligne en fonction des capteurs. 
//Identique à celle de la librairie, mais la valeur de retour est la 
//valeur des capteurs.
uint8_t suivreLigne1(){
    uint8_t positionnement = checkLignes();
    switch(positionnement){
        case CENTER:
            avancer(VITESSE);
            break;
        case LEFT :
        case FAR_LEFT:
            ajustementDroite(VITESSE + 50, VITESSE - 20);
            break;
        case RIGHT:
        case FAR_RIGHT:
            ajustementGauche(VITESSE + 50, VITESSE - 20);
            break;
        case ALL:
            break;
        default: 
            avancer(VITESSE_FAIBLE);
            break;
    }
    return positionnement;
}
//Fait avancer le robot de 3 pouces (La distance entre deux pts)
void avancerPoint(){ 
    avancer(VITESSE_FAIBLE);
    _delay_ms(1225);
    avancer(0);
    _delay_ms(500);
}
//Fait tourner le robot à gauche de 90 degrés.
void tournerGauche90(){ 
    PWM(125, 125, 2);
    _delay_ms(1150);
    avancer(0);
    _delay_ms(500);
}
//Fait tourner le robot ;a droite de 90 degrés. 
void tournerDroite90(){ 
    PWM(125, 125, 3);
    _delay_ms(1150);
    avancer(0);
    _delay_ms(500);
}
//Fait avancer le robot en ligne droite jusqu'à ce qu'il rencontre
//une ligne
void avancerJusquaLigne(){
    while(!suivreLigne1());
}
//Fait avancer le robot de la distance entre ses capteurs et son axe
//de rotation.
void avancerAxeRotationPoint(uint8_t vitesse){
    avancer(VITESSE);
    if (vitesse==VITESSE)
        _delay_ms(750);
    else
        _delay_ms(1150);
    avancer(0);
}
//Fonction permettant de réaliser le premier segment.
void fonctionCoin1(){
    //Avancer jusqu'à la ligne d'arrêt.
    while(!suivreLigneArret()){ 
    }
    avancer(0);
    _delay_ms(500);
    //Réception du point par infrarouge
    uint8_t point = recevoir() -128;
   //Positionnement jusqu'au premier point
    avancerAxeRotationPoint(0);
    avancer(0);
    _delay_ms(500);
    avancerPoint();
    tournerGauche90();

    avancer(VITESSE_FAIBLE);
    _delay_ms(1300);
    avancer(0);
    _delay_ms(500);

    //Calcul du numéro de la colonne et de la ligne en fonction du point:

    /*   1   2   3
    ---------------
    0 |  1   2   3
    1 |  4   5   6
    2 |  7   8   9

    */
    uint8_t colonne = (point % 3) ==  0 ? 3 : point % 3;
    uint8_t ligne = (point - 1) / 3 ; 

    
    //Avancer jusqu'à la bonne colonne
    for(int i = 0; i < 4 - colonne; i++){
        avancerPoint(); //Avancer de la distance entre deux pts
    }
    tournerDroite90();
    //Avancer jusqu'à la bonne ligne
    for(int i = 0; i < 2 - ligne ; i++){
        avancerPoint(); //Avancer de la distance entre deux pts
    }
    //Le robot émet un son grave, tourne à droite et en émet un autre
    Piezo piezo;
    piezo.emmettreSon(piezo.getSon(45));
    _delay_ms(3000);
    piezo.arreterSon();
    tournerDroite90();
    piezo.emmettreSon(piezo.getSon(45));
    _delay_ms(3000);
    piezo.arreterSon();
    //Le robot se redéplace vers la ligne noire
    for(int i = 0; i < 4- colonne; i++){
        avancerPoint();
    }
    avancer(VITESSE_FAIBLE);
    _delay_ms(1300);
    avancer(0);
    _delay_ms(500);
    tournerGauche90();
    avancerJusquaLigne();
    //Le robot se déplace vers le prochain segment
    while((suivreLigne1()!=TOURNANT_GAUCHE_1) && (suivreLigne1()!=TOURNANT_GAUCHE_2)){}
    avancerAxeRotation(VITESSE);

}