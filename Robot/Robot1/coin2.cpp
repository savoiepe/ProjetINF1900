#include <fonctions.h>
//fonction simple du coin2 qui appelle en boucle la fonction suivreCourbe de la librairie jusqu'a ce que celle-ci retourne true
void fonctionCoin2(){
    while(!suivreCourbe()){}
    avancerAxeRotation(VITESSE_FAIBLE);
}
