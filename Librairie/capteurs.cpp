/*Cette section contient les fonctions necessaires pour affecter et verifier l'etat des capteurs
du robot afin qu'il se reajuste lors de ses parcours et qu'il se deplace convenablement*/

#include "capteurs.h"
bool courbe = false;
volatile bool tournantCoinDeux = true;
volatile bool minuterieAtteinte = false;
volatile bool aDepasse = false;

/*Fonction d'interruption appelée lorsque le minuterie activée dans suivreCourbe est atteinte*/
ISR(TIMER2_COMPA_vect) {
        if (!minuterieAtteinte && dureeAtteinte2(1)){
            minuterieAtteinte = true;
            aDepasse = true;
            arreterMinuterie2();
        }

        if (dureeAtteinte2(8)){
            aDepasse = true;
            arreterMinuterie2();
        }
}

/*  Fonction qui effectue la conversion analogique d'une valeur du port A et allume la LED correspondante si cest une valeur noire
    Retourne la position sur le capteur de la LED correspondante
        param pos: choix de la position sur le PORTA pour effectuer la conversion (0 - 4)*/
uint8_t checkLigne(uint8_t pos){
	uint8_t valeur = conversionAnalogique(pos);
    if (valeur <= 100){ //le debogage des valeurs de conversion nous montrent que la ligne noire donne toujours une valeur inferieure a 40, donc <= 100 pour etre sur
        allumerDEL(pos);
        return (1 << pos);
    }
    eteindreDEL(pos);
    return 0;
}

/*Fonction qui retourne l'etat des capteurs sur un uint8_t en appelant checkLigne pour chaque capteur*/
uint8_t checkLignes(){
	return checkLigne(0) | checkLigne(1) | checkLigne(2) | checkLigne(3) | checkLigne(4);
}

/*Fonction appelée dans la section 2 afin d'alterner de vitesse entre une courbe et une ligne
Retourne true seulement apres un tournant a gauche, soit a la toute fin de la section afin d'aller a la section 3
Active une minuterie en parallele afin d'empecher le robot de ralentir lorsqu'on ne le veut pas
Detecte une courbe lorsque les capteurs aux extremites (0 et 4) sont activés*/
bool suivreCourbe(){
    uint8_t positionnement = checkLignes();

    if (tournantCoinDeux){
        partirMinuterie2('A');
        tournantCoinDeux = false;
    }

    switch(positionnement){
        case CENTER:
            if(!courbe)
                avancer(VITESSE);
            else avancer(VITESSE_FAIBLE);
            break;
        case LEFT :
            if (!courbe)
                ajustementDroite(VITESSE + 50, VITESSE);
            else
                ajustementDroite(VITESSE_FAIBLE, VITESSE_FAIBLE - 50);
            break;
        case FAR_LEFT :
            if (aDepasse)
                courbe = true;
            ajustementDroite(VITESSE_FAIBLE + 10, VITESSE_FAIBLE - 50);
            break;
        case RIGHT :
            if (!courbe)
                ajustementGauche(VITESSE + 50, VITESSE);
            else
                ajustementGauche(VITESSE_FAIBLE + 10, VITESSE_FAIBLE - 50);
            break;
        case FAR_RIGHT :
            if (aDepasse)
                courbe = true;
            ajustementGauche(VITESSE_FAIBLE, VITESSE_FAIBLE - 50);
            break;
        case TOURNANT_DROITE_1 :
        case TOURNANT_DROITE_2 :
            _delay_ms(30);
            positionnement = checkLignes();
            if (positionnement == TOURNANT_DROITE_1 || positionnement == TOURNANT_DROITE_2){
                courbe = false;
                aDepasse = false;
                partirMinuterie2('A');
                avancerAxeRotation(VITESSE_FAIBLE);
                tournerDroiteCapteur();
            }
            break;
        case TOURNANT_GAUCHE_1 :
        case TOURNANT_GAUCHE_2 :
            _delay_ms(30);
            positionnement = checkLignes();
            if (positionnement == TOURNANT_GAUCHE_1 || positionnement == TOURNANT_GAUCHE_2){
                return true;
            }
            break;
    }
    return false;
}

/*Fonction utilisee afin de que le robot suive une ligne droite jusqu'a detection d'une ligne pleine (return true)
Utilisee au debut des sections 1 et 3*/
bool suivreLigneArret(){
    uint8_t positionnement = checkLignes();
    switch(positionnement){
        case CENTER:
            avancer(VITESSE_FAIBLE);
            break;
        case LEFT :
        case FAR_LEFT:
            ajustementDroite(VITESSE_FAIBLE + 50);
            break;
        case RIGHT:
        case FAR_RIGHT:
            ajustementGauche(VITESSE_FAIBLE + 50);
            break;
        case ALL:
            return true;
            break;
    }
    return false;
}

/*Fonction utilisee afin de que le robot suive une ligne droite jusqu'a detection d'un coin (return true)
Utilisee a chacun des quatre coins du parcours complet*/
bool suivreLigneCoin(){
    uint8_t positionnement = checkLignes();
    switch(positionnement){
        case CENTER:
            avancer(VITESSE);
            break;
        case LEFT :
        case FAR_LEFT:
            ajustementDroite(VITESSE + 50);
            break;
        case RIGHT:
        case FAR_RIGHT:
            ajustementGauche(VITESSE + 50);
            break;
        case TOURNANT_GAUCHE_1:
        case TOURNANT_GAUCHE_2:
        case ALL:
            return true;
            break;
    }
    return false;
}

/*Fonction utilisee afin que le robot suive chacune des lignes droites de la section 4.
Afin d'empecher de voir plusieurs fois la meme ligne, la booléenne enableAll change de
valeur a chaque detection de ligne droite jusqu'a ca que l'etat des capteurs change*/
bool suivreLigne(bool& enableAll){
    uint8_t positionnement = checkLignes();
    switch(positionnement){
        case CENTER:
            enableAll = true;
            avancer(VITESSE);
            break;
        case LEFT :
        case FAR_LEFT:
            enableAll = true;
            ajustementDroite(VITESSE + 50, VITESSE - 20);
            break;
        case RIGHT:
        case FAR_RIGHT:
            enableAll = true;
            ajustementGauche(VITESSE + 50, VITESSE - 20);
            break;
        case ALL:
            if (enableAll){
                enableAll = false;
                avancer(VITESSE);
                /*Emission de son a l'entree d'un carre*/
                Piezo piezo;
                piezo.emmettreSon(piezo.getSon(81));
                _delay_ms(50);
                piezo.arreterSon();
                _delay_ms(20);
                piezo.emmettreSon(piezo.getSon(81));
                _delay_ms(50);
                piezo.arreterSon();
                return true;
                break;
            }
    }
    return false;
}

/*Fonction utilisee afin que le robot avance en ligne droite en se reajustant a l'interieur de chacun
des carres de la section 4. Afin d'empecher de voir plusieurs fois la meme ligne, la booléenne enableAll
change de valeur a chaque detection de ligne droite jusqu'a ca que l'etat des capteurs change*/
bool suivreCarre(bool& enableAll){
    uint8_t positionnement = checkLignes();
    switch(positionnement){
        case NONE:
            enableAll = true;
            avancer(VITESSE);
            break;
        case LEFT:
        case BOTH_LEFT:
        case FAR_LEFT :
            enableAll = true;
            ajustementGauche(VITESSE + 50, VITESSE - 20);
            break;
        case RIGHT:
        case BOTH_RIGHT:
        case FAR_RIGHT:
            enableAll = true;
            ajustementDroite(VITESSE + 50, VITESSE - 20);
            break;
        case ALL:
            if (enableAll){
                enableAll = false;
                avancer(VITESSE);
                /*Emission de son a la sortie d'une carre*/
                Piezo piezo;
                piezo.emmettreSon(piezo.getSon(81));
                _delay_ms(50);
                piezo.arreterSon();
                _delay_ms(20);
                piezo.emmettreSon(piezo.getSon(81));
                _delay_ms(50);
                piezo.arreterSon();
                return true;
                break;
            }
    }
    return false;
}