#pragma once

#include "includeAll.h"

void PWM(uint8_t ratioA, uint8_t ratioB, uint8_t mode);

void avancer(uint8_t ratio);

void reculer(uint8_t ratio);

void droite(uint8_t ratio);

void gauche(uint8_t ratio);

void ajustementDroite(uint8_t ratio, uint8_t ratio2 = 150);

void ajustementGauche(uint8_t ratio, uint8_t ratio2 = 150);

void avancerAxeRotation(uint8_t vitesse);

void tournerGaucheCapteur();

void tournerDroiteCapteur();
