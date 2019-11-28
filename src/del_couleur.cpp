#include "del_couleur.h"

int allumerDELCouleur(int couleur)
{
    int portsCouleurs[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU, PORT_JAUNE};
    for (int port : portsCouleurs) digitalWrite(port, LOW);

    if (couleur==ROUGE) digitalWrite(PORT_ROUGE, HIGH);
    if (couleur==VERT) digitalWrite(PORT_VERT, HIGH);
    if (couleur==BLEU) digitalWrite(PORT_BLEU, HIGH);
    if (couleur==JAUNE) digitalWrite(PORT_JAUNE, HIGH);

    return couleur;
}

void eteindreDELCouleur()
{
    int portsCouleurs[] = {PORT_ROUGE, PORT_VERT, PORT_BLEU, PORT_JAUNE};
    for (int port : portsCouleurs) digitalWrite(port, LOW);
    
    return;
}