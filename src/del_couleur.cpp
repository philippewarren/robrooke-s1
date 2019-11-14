#include "del_couleur.h"

void initialiserPortsDELCouleur()
{
    pinMode(PORT_ROUGE, OUTPUT);
    pinMode(PORT_VERT, OUTPUT);
    pinMode(PORT_BLEU, OUTPUT);
}

int allumerDELCouleur(int couleur)
{ 
    uint8_t etatRGB[] = {LOW, LOW, LOW};
    int portRGB[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU}; 

    if(couleur==ROUGE || couleur==JAUNE)
    {
        etatRGB[0] = HIGH;
    }
    if(couleur==VERT || couleur==JAUNE)
    {
        etatRGB[1] = HIGH;
    }
    if(couleur==BLEU)
    {
        etatRGB[2] = HIGH;
    }

    for (int i=0; i<3; i++) digitalWrite(portRGB[i], etatRGB[i]);

    return couleur;
}

void eteindreDELCouleur()
{
    int portRGB[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU};
    for (int i=0; i<3; i++) digitalWrite(portRGB[i], LOW);
}