#include "del_couleur.h"

void initialiserPortsDELCouleur()
{
    pinMode(PORT_ROUGE, OUTPUT);
    pinMode(PORT_VERT, OUTPUT);
    pinMode(PORT_BLEU, OUTPUT);
    pinMode(PORT_JAUNE, OUTPUT);

    return;
}

int allumerDELCouleur(int couleur)
{ 
    // uint8_t etatRGB[] = {LOW, LOW, LOW};
    // int portRGB[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU}; 

    // if(couleur==ROUGE || couleur==JAUNE)
    // {
    //     etatRGB[0] = HIGH;
    // }
    // if(couleur==VERT || couleur==JAUNE)
    // {
    //     etatRGB[1] = HIGH;
    // }
    // if(couleur==BLEU)
    // {
    //     etatRGB[2] = HIGH;
    // }

    // for (int i=0; i<3; i++) digitalWrite(portRGB[i], etatRGB[i]);

    int portsCouleurs[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU, PORT_JAUNE};
    int portAllume = -1;
    for (int port : portsCouleurs) digitalWrite(port, LOW);

    if (couleur==ROUGE) portAllume = PORT_ROUGE;
    if (couleur==VERT) portAllume = PORT_VERT;
    if (couleur==BLEU) portAllume = PORT_BLEU;
    if (couleur==JAUNE) portAllume = PORT_JAUNE;

    if(portAllume!=-1) digitalWrite(portAllume, HIGH);

    return couleur;
}

void eteindreDELCouleur()
{
    // int portRGB[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU};
    // for (int i=0; i<3; i++) digitalWrite(portRGB[i], LOW);
    int portsCouleurs[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU, PORT_JAUNE};
    for (int port : portsCouleurs) digitalWrite(port, LOW);
    
    return;
}