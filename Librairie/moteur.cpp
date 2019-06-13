/*Cette section contient toutes les fonctions "wrapper" sur PWM afin de manipuler les roues comme nous le voulons*/

#include "includeAll.h"

/*Fonction qui cree une onde PWM pour faire tourner les roues (pourcentages a calculer avant d'appeler la fonction)
    param ratioA: pourcentage de l'onde de la premiere roue
    param ratioB: pourcentage de l'onde de la deuxieme roue
    param mode: direction des roues{0 = avance, 1 = recule, 2 = droite, 3 = gauche}*/
void PWM(uint8_t ratioA, uint8_t ratioB, uint8_t mode){
    DDRD |= 0b11110000;
    TCCR1A = 0xA1; //10100001
    //COM1A1, COM1B1: clear (upcount) / set (downcount)
    //WGM10: PWM 8-bit

    TCCR1B = ((1<<CS02) | (1<<CS00)) | (1<<WGM02);
    //Prescale 1024
    
    switch (mode){
        case 0 : PORTD &= ~(1 << 6) & ~(1 << 7); break;   //avance
        case 1 : PORTD |= (1 << 6) | (1 << 7); break;  //recule
        case 2 : PORTD |= (1 << 6); PORTD &= ~(1 << 7); break;  //gauche
        case 3 : PORTD |= (1 << 7); PORTD &= ~(1 << 6); break;  //droite
    }
    OCR1A = ratioA;
    OCR1B = ratioB + 8;
}

/*Fonction qui appelle la fonction PWM afin d'avancer en ligne droite
    param ratio: pourcentage des deux roues*/
void avancer(uint8_t ratio){
    PWM(ratio, ratio, 0);
}

/*Fonction qui appelle la fonction PWM afin de reculer en ligne droite
    param ratio: pourcentage des deux roues*/
void reculer(uint8_t ratio){
    PWM(ratio, ratio, 1);
}

/*Fonction qui appelle la fonction PWM afin de tourner à droite sur place
    param ratio: pourcentage des deux roues*/
void droite(uint8_t ratio){
    PWM(ratio, ratio, 3);
}

/*Fonction qui appelle la fonction PWM afin de tourner à gauche sur place
    param ratio: pourcentage des deux roues*/
void gauche(uint8_t ratio){
    PWM(ratio, ratio, 2);
}

/*Fonction qui ajuste le registre OCR1A afin d'ajuster le pourcentage de la roue droite
Utilisee lors de l'activation des capteurs 1 ou 3 (gauche et droite interieur) afin de
reajuster le robot sur une ligne ou une courbe ou a l'interieur d'une carre.
    param ratio1: pourcentage de la roue droite*/
void ajustementDroite(uint8_t ratio1,uint8_t ratio2 ){
    OCR1A = ratio1;
    OCR1B = ratio2;
}

/*Fonction qui ajuste le registre OCR1B afin d'ajuster le pourcentage de la roue gauche
Utilisee lors de l'activation des capteurs 1 ou 3 (gauche et droite interieur) afin de
reajuster le robot sur une ligne ou une courbe ou a l'interieur d'une carre.
    param ratio1: pourcentage de la roue gauche*/
void ajustementGauche(uint8_t ratio1, uint8_t ratio2){
    OCR1B = ratio1;
    OCR1A = ratio2;
}

/*Fonction qui fait avancer le robot a son axe de rotation afin de le placer au bon endroit avoir de tourner
    param vitesse: pourcentage PWM des roues
        VITESSE - avancerAxeRotation apres un suivi de ligne
        VITESSE_FAIBLE - avancerAxeRotation apres un suivi de courbe*/
void avancerAxeRotation(uint8_t vitesse){
    avancer(VITESSE);
    if (vitesse==VITESSE)
        _delay_ms(500);
    else
        _delay_ms(750);
    avancer(0);
}

/*Fonction qui fait tourner le robot sur place vers la gauche jusqu'a detection de la prochaine ligne*/
void tournerGaucheCapteur(){
    _delay_ms(1000);
    gauche(VITESSE_FAIBLE);
    while(!(checkLignes()==FAR_LEFT)){
    }
    avancer(0);
}

/*Fonction qui fait tourner le robot sur place vers la droite jusqu'a detection de la prochaine ligne*/
void tournerDroiteCapteur(){
    droite(VITESSE_FAIBLE);
    while(!(checkLignes()==FAR_RIGHT)){ 
    }
    avancer(0);
}
