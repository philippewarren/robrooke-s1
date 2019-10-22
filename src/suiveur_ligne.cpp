#include "suiveur_ligne.h"

void lireSuiveurLigne(int output [8])
{
    //constante
    int const NOMBRE_DE_LECTURE = 3;
    //lecture des donnée
    output[0] = analogRead(A0);
    output[1] = analogRead(A1);
    output[2] = analogRead(A2);
    output[3] = analogRead(A3);
    output[4] = analogRead(A4);
    output[5] = analogRead(A5);
    output[6] = analogRead(A6);
    output[7] = analogRead(A7);
    for (int i=1;i<NOMBRE_DE_LECTURE;i++)
    {
    delay(1);
    output[0] += analogRead(A0);
    output[1] += analogRead(A1);
    output[2] += analogRead(A2);
    output[3] += analogRead(A3);
    output[4] += analogRead(A4);
    output[5] += analogRead(A5);
    output[6] += analogRead(A6);
    output[7] += analogRead(A7);
    }

    for (int i = 0; i<8; i++)output[i] /= NOMBRE_DE_LECTURE;
}

void suivreLigne(float vitesse)
{
    //constante proportionnelle à la différence de réflectivité des deux surfaces
    // 1000 = sol blanc et ligne noir
    const short CONTRASTE = 1000;

    //lecture des données
    int lectureSuiveurDeLigne [8];
    lireSuiveurLigne(lectureSuiveurDeLigne);

    //calcul des différences entre capteurs opposés
    float delta1 = lectureSuiveurDeLigne[3]-lectureSuiveurDeLigne[4];
    float delta2 = lectureSuiveurDeLigne[2]-lectureSuiveurDeLigne[5];
    float delta3 = lectureSuiveurDeLigne[1]-lectureSuiveurDeLigne[6];
    float delta4 = lectureSuiveurDeLigne[0]-lectureSuiveurDeLigne[7];

    //calcul du facteur de correction
    float facteur = delta1 + delta2 * 2+ delta3 * 3+ delta4 * 4;
    if (facteur > 4*CONTRASTE) facteur = 4*CONTRASTE;
    else if (facteur < -4*CONTRASTE) facteur = -4*CONTRASTE;
    facteur = facteur / (4 * CONTRASTE);

    //modification de la vitesse des roues
    changerVitesseDeuxMoteurs(vitesse*(1+facteur),vitesse*(1-facteur));

}