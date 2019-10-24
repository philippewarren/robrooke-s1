#include "loop_normal.h"
int itt = 0;
float vitesse = 0.5;
bool lecture = false;
bool avancerLigne = false;
bool avancerDroit2 = false;
bool ligne = false;
long timerFinLigne = 0;
bool timerLance = false;
void loopNormal()
{
    if (lecture)
    {
        //test couleur
        
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
    else lecture = loopEstCliqueEtRelache(3);
    if (avancerLigne)
    {
        suivreLigne(vitesse);
        if(detecterLigne())
        {
            ligne = true;
            timerLance = false;
        }
        else if(ligne)
        {
            if (!timerLance)
            {
                timerLance = true;
                timerFinLigne = millis();
            }
            //si aucune ligne n'est détecter durant 0.300s, arret de la séquence
            else if ((millis()-timerFinLigne)>300)
            {
                avancerLigne=false;
                changerVitesseDeuxMoteurs(0);
                timerLance = false;
            }
        }
    }
    else
    {
        avancerLigne = loopEstCliqueEtRelache(2);
    }
    if (avancerDroit2)
    {
        changerVitesseDeuxMoteurs(vitesse);
        Serial.println(ENCODER_Read(0));
        Serial.println(ENCODER_Read(1));
        /*float corr = vitesse*partielIntegralDerive()/2;
        Serial.println(corr);
        changerVitesseDeuxMoteurs(vitesse-corr,vitesse+corr);*/

        itt++;
        if (itt >500)
        {avancerDroit2 = false;
        changerVitesseDeuxMoteurs(0);}
    }
    else
    {
        partielIntegralDerive(true);
        avancerDroit2 = loopEstCliqueEtRelache(0);
        itt=0;
    }
    

    // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
}