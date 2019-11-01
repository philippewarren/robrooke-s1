#include "loop_B.h"

const long DEPART_BOB_B = 60*1000 + 1000;
const long ARRET_BOB_B = 2*60*1000 - 1000;

bool tempsBobB()
{
    static long tempsInitial = 0;
    static long delais = 0;
    if (tempsInitial==0) tempsInitial = millis();

    delais = millis()-tempsInitial;

    if (delais>=DEPART_BOB_B && delais<=ARRET_BOB_B) return true;
    else return false;
}

float calculAngleCouleur(int COULEUR)
{
    float angle = 0;
    if (COULEUR == ROUGE)
    {
        angle = -(90+45);
    }
    else if (COULEUR == VERT)
    {
        angle = (90+45);
    }
    else if (COULEUR == BLEU)
    {
        angle = (45);
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
    static float distances[] = {25, 15, 20, 30, -30};
    static int distance = 0;
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
        ouvrirPince(true);
        etape += 1;
        break;

    case 3:
        if (avancerDroit(0.1, distance++)) etape += 1;
        break;

    case 4:
        fermerPince();
        etape += 1;
        break;

    case 5:
        if (avancerDroit(0.1, distance++)) etape += 1;
        break;

    case 6:
        if (tourner(0.5, angleCouleur)) etape += 1;
        break;

    case 7:
        if (avancerDroit(0.1, distance++)) etape += 1;
        break;

    case 8:
        if (traquerLigne(0.5)) etape += 1;
        break;
    
    case 9:
        if (avancerDroit(0.5, distance++)) etape += 1;
        break;

    case 10:
        ouvrirPince();
        etape += 1;
        break;

    case 11:
        if (avancerDroit(0.2, distance)) etape += 1;
        break;

    default:
        arreterDeuxMoteurs();
        desactiverServo(PINCE);
        break;
    }

    if (etape > 1 && !tempsBobB()) etape = 11;
}