#ifndef CAPTEUR_COULEUR_H
#define CAPTEUR_COULEUR_H

#include <Adafruit_TCS34725.h>

#include "conversions.h"
#include "del_couleur.h"

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

extern Adafruit_TCS34725 CapteurCouleur;

extern const uint16_t TOUTES_COULEURS[];
extern const uint16_t COULEURS_OCTOGONE[];
extern const uint16_t COULEURS_LETTRES[];

extern const uint16_t BORNES_COULEUR[];

extern const int SEUIL_NOIR;
extern const int SEUIL_BLANC;
extern const int SEUIL_GRIS;

//Initialise le capteur couleurs
void initialiserCapteurCouleur();

//Lit les valeurs du capteur couleur et retourne les valeurs dans le tableau dans cet ordre: {rouge, vert, bleu, sansCouleur}
void lireCapteurCouleur(uint8_t numeroDeCapteur, uint16_t tableauVide[4]);

//Transforme une couleur rgb dans un tableau en nom de couleur
int evaluerCouleur(uint16_t tableauRGB[4], const uint16_t couleursPossibles[] = TOUTES_COULEURS);

//Lit la couleur de la lettre et retourne une valeur de couleur
int obtenirCouleurLettre();

void debugCapteurCouleur();


#endif