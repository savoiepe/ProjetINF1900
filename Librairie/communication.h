#include <includeAll.h>

//Méthodes d'envoi par émetteur infrarouge en utilisant le protocole SIRC

//Envoi d'un 1 en utilisant le protocole SIRC
void envoyer1();
//Envoi d'un 0 en utilisant le protocole SIRC
void envoyer0();
//Envoi de la séquence annonçant l'envoi d'une valeur
void envoyerStart();
//Envoi d'une valeur en utilisant le protocole SIRC
void envoyer(uint8_t valeur);
//PWM qui émet la bonne fréquence d'onde infrarouge.
void PWM_Com();
//Arrête le PWM_Com
void arreterPWM();

//Methodes de réception

//Réception d'un 1 suivant le protocole SIRC
void recevoir1();
//Réception d'un 0 suivant le protocole SIRC
void recevoir0();
//Réception d'une valeur suivant le protocole SIRC et retourne cette valeur
uint16_t recevoir();