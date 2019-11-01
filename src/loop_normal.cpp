#include "loop_normal.h"

int itt = 0;
float vitesse = 0.3;
bool lecture = false;
bool avancerLigne = false;
bool avancerDroit2 = false;
bool ligne = false;
long timerFinLigne = 0;
bool timerLance = false;
int angleCourrant = 0;
void loopNormal()
{
    if (Bob=='A') loopOctogoneA();
    else loopOctogoneB();
    if (loopEstCliqueEtRelache(0))
    {
        //test couleur
        
        Serial.println("lecture de la couleur");
        uint16_t couleur [4];
        uint16_t couleur2 [4];
        lireCapteurCouleur(0,couleur);
        for (int i=0;i<4;i++)
        {
            couleur2[i] = couleur[i];
            Serial.print(couleur[i]);
            Serial.print('\t');
        }
        couleur2[4] = couleur[4];
        Serial.println();
        //rgbEnHsl(couleur2);
        for (int i=0;i<4;i++)
        {
            Serial.print(couleur2[i]);
            Serial.print('\t');
        }
        Serial.print('\n');
        Serial.print ("couleur: ");
        int resultat = evaluerCouleur(couleur, COULEURS_OCTOGONE);
        if (resultat == ROUGE)Serial.print("rouge");
        if (resultat == JAUNE)Serial.print("jaune");
        if (resultat == VERT)Serial.print("vert");
        if (resultat == TURQUOISE)Serial.print("turquoise");
        if (resultat == BLEU)Serial.print("bleu");
        if (resultat == MAUVE)Serial.print("mauve");
        if (resultat == NOIR)Serial.print("noir");
        if (resultat == BLANC)Serial.print("blanc");
        if (resultat == GRIS)Serial.print("gris");
        Serial.println(resultat);
        Serial.print('\n');

        //test distance
        Serial.println("lecture de la distance");
        Serial.println(lireDistanceIR(0));

        //test suiveur de ligne
        int ligne[8];
        lireSuiveurLigne(ligne);
        Serial.println("lecture de la ligne");
        for (int i = 0; i<8;i++)
        {
            Serial.print(ligne[i]);
            Serial.print('\t');
        }
        Serial.print('\n');
        Serial.println("presence de ligne");
        Serial.println(detecterLigne());
        
        
        lecture = false;


    }
    

    // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
}