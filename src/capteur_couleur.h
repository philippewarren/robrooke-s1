#ifndef CAPTEUR_COULEUR_H
#define CAPTEUR_COULEUR_H

#include <Adafruit_TCS34725.h>

#define ROUGE 0
#define JAUNE 60
#define VERT 120
#define TURQUOISE 180
#define BLEU 240
#define MAUVE 300

#define BLANC -100
#define NOIR -1
#define GRIS -50


//Initialise le capteur couleurs
void initialiserCapteurCouleur();

//Lit les valeurs du capteur couleur et retourne les valeurs dans le tableau dans cet ordre: {rouge, vert, bleu, sansCouleur}
void lireCapteurCouleur(uint8_t numero, uint16_t tableau[4]);


#endif