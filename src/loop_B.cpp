#include "loop_B.h"

const long long DEPART_BOB_B = 2000;// 60*1000 + 1000;
const long long ARRET_BOB_B = 119000;

bool tempsBobB()
{
    bool retour = false;
    static long tempsInitial = 0;
    long delais = 0;
    if (tempsInitial==0) tempsInitial = millis();

    delais = millis()-tempsInitial;

    if (delais>=ARRET_BOB_B)
    {
        retour = false;
    }
    else if (delais>=DEPART_BOB_B)
    {
        retour = true;
    }

    Serial.println(delais);
    Serial.println(retour);

    return retour;
}

/* Plan de l'octogone
R # # # V
# # B # #
# # O # #
# # A # #
J # # # B
*/
//Ordre modifiable au besoin {R    , V   , B   , J    }
const int ORDRE_COULEURS[] = {ROUGE, VERT, BLEU, JAUNE};

float calculAngleCouleur(int COULEUR)
{
    float angle = 0;
    if (COULEUR == ORDRE_COULEURS[0])
    {
        angle = -(90+45);
    }
    else if (COULEUR == ORDRE_COULEURS[1])
    {
        angle = (90+45);
    }
    else if (COULEUR == ORDRE_COULEURS[2])
    {
        angle = (43);
    }
    else //COULEUR ==JAUNE
    {
        angle = (-45);
    }

    return angle;
}

/* Plan de l'octogone
R # # # V
# # B # #
# # O # #
# # A # #
J # # # B
*/
void loopOctogoneB()
{
    //Tableau lié aux étape:   {0, 1, 2, 03, 4, 05, 6, 07, 8, 09, 10, 11}
    static float distances[] = {0, 0, 0, 35.0, 0, 15.0, 0, 20.0, 0, 30.0, 0, -30.0};
    //static int distance = 0;
    static float angleCouleur = 0;
    
    /*Etapes:
        0: attendre l'appui du bumper arrière
        1: attendre le temps d'une minute
        2: ouvrir pince
        3: avancer vers ballon au centre
        4: ramasser ballon
        5: avancer au centre
        6: rotation en fonction de la couleur
        7: avancer jusqu'à la ligne
        8: suivre la ligne
        9: avancer jusqu'au noir
        10: déposer ballon
        11: reculer un peu
        12 (default): fini
    */
    static int etape = 0;

    if (etape!=11) Serial.println(etape);

    switch (etape)
    {
    case 0:
        if (angleCouleur == 0) angleCouleur = calculAngleCouleur(COULEURS_BOB[1]);
        if (loopEstCliqueEtRelache(3)) etape += 1;
        break;

    case 1:
        if (tempsBobB()) etape += 1;
        break;

    case 2:
        if (ouvrirPinceOctogone(true)) etape += 1;
        break;

    case 3:
        if (avancerDroit(0.3, distances[etape])) etape += 1;
        break;

    case 4:
        if (fermerPinceOctogone()) etape += 1;
        break;

    case 5:
        if (avancerDroit(0.3, distances[etape])) etape += 1;
        break;

    case 6:
        if (tourner(0.3, angleCouleur)) etape += 1;
        break;

    case 7:
        if (avancerDroit(0.3, distances[etape])) etape += 1;
        break;

    case 8:
       // if (traquerLigne(0.3)) etape += 1;
        if (avancerDroit(0.3, 65)) etape += 1;
        break;
    
    case 9:
        if (avancerDroit(0.3, distances[etape])) etape += 1;
        break;

    case 10:
        if (ouvrirPinceOctogone(true)) etape += 1;
        break;

    case 11:
        if (avancerDroit(0.2, distances[etape])) etape += 1;
        break;

    default:
        arreterDeuxMoteurs();
        desactiverServo(PINCE);
        break;
    }

    if (etape > 1 && !tempsBobB()) etape = 11;
}