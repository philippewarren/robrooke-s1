#ifndef CAPTEUR_COULEUR_H
#define CAPTEUR_COULEUR_H

#include <Adafruit_TCS34725.h>

#include "del_couleur.h"

//#define TCS34725_ADDRESS (0x29)

#define ROUGE 0
#define JAUNE 60
#define VERT 120
#define TURQUOISE 180
#define BLEU 240
#define MAUVE 300

#define BLANC -100
#define NOIR -10
#define GRIS -50

#define AUCUNE -2

extern Adafruit_TCS34725 CapteurCouleur;

extern const uint16_t BORNES_COULEUR[];

extern const int SEUIL_NOIR;
extern const int SEUIL_BLANC;
extern const int SEUIL_GRIS;

//Initialise le capteur couleurs
void initialiserCapteurCouleur();

//Convertit les 3 premiers nombres d'un tableau de 4 (r,g,b) en (h,s,l) dans le meme tableau, sans toucher la valeur 4 (sansCouleur)
void rgbEnHsl(uint16_t tableauRGB[4]);

//Lit les valeurs du capteur couleur et retourne les valeurs dans le tableau dans cet ordre: {hue, saturation, luminosité, sansCouleur}
void lireCapteurCouleur(uint8_t numeroDeCapteur, uint16_t tableauVide[4]);

//Transforme une couleur rgb dans un tableau en nom de couleur
int evaluerCouleur(uint16_t tableauRGB[4]);

//Lit la couleur de la lettre et retourne une valeur de couleur
int obtenirCouleurLettre();

void debugCapteurCouleur();


#endif