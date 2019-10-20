#include "loop_normal.h"
bool lecture = false;
void loopNormal()
{
    if (lecture)
    {
        //test couleur
        /*
        Serial.println("lecture de la couleur");
        uint16_t couleur [4];
        lireCapteurCouleur(0,couleur);
        for (int i=0;i<4;i++)
        {
            Serial.print(couleur[i]);
            Serial.print('\t');
        }
        Serial.print('\n');
        Serial.print ("couleur: ");
        int resultat = evaluerCouleur(couleur);
        if (resultat == ROUGE)Serial.print("rouge");
        if (resultat == JAUNE)Serial.print("jaune");
        if (resultat == VERT)Serial.print("vert");
        if (resultat == TURQUOISE)Serial.print("turquoise");
        if (resultat == BLEU)Serial.print("bleu");
        if (resultat == MAUVE)Serial.print("mauve");
        if (resultat == NOIR)Serial.print("noir");
        if (resultat == BLANC)Serial.print("blanc");
        if (resultat == GRIS)Serial.print("gris");
        Serial.print('\n');*/

        //test distance
        
        
        lecture = false;
    }
    else lecture = loopEstCliqueEtRelache(3);

    // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
}