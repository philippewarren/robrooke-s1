#ifndef CAPTEUR_COULEUR_H
#define CAPTEUR_COULEUR_H

#include <Adafruit_TCS34725.h>

#include "conversions.h"

//#define TCS34725_ADDRESS (0x29)

#define ROUGE 0
#define JAUNE 60
#define VERT 120
#define TURQUOISE 180
#define BLEU 240
#define MAUVE 300

#define BLANC -100
#define NOIR -1
#define GRIS -50

extern const uint16_t TOUTES_COULEURS[];
extern const uint16_t COULEURS_OCTOGONE[];
extern const uint16_t COULEURS_LETTRES[];

//Initialise le capteur couleurs
void initialiserCapteurCouleur();

//Lit les valeurs du capteur couleur et retourne les valeurs dans le tableau dans cet ordre: {rouge, vert, bleu, sansCouleur}
void lireCapteurCouleur(uint8_t numeroDeCapteur, uint16_t tableauVide[4]);

//Transforme une couleur rgb dans un tableau en nom de couleur
int evaluerCouleur(uint16_t tableauRGB[4], const uint16_t couleursPossibles[] = TOUTES_COULEURS);

#endif