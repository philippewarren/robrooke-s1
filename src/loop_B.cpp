#include "loop_B.h"

const long DEPART_BOB_B = 60*1000 + 1000;
const long ARRET_BOB_B = 60*1000*2 - 1000;

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
    static float distances[] = {25, 15};
    static int distance = 0;
    static float angleCouleur = 0;
    
    /*Etapes:
        0: attendre l'appui du bumper arrière
        1: attendre le temps d'une minute
        2: avancer vers ballon au centre
        3: ramasser ballon
        4: avancer au centre
        5: rotation en fonction de la couleur
        6: avancer jusqu'à la ligne
        : avancer en suivant la ligne
        : avancer jusqu'au noir
        : déposer ballon
        : reculer un peu
         (default): fini
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
        if (avancerDroit(0.1, distance++)) etape += 1;
        break;

    case 3:
        fermerPince();
        etape += 1;
        break;

    case 4:
        if (avancerDroit(0.1, distance++)) etape += 1;
        break;

    case 5:
        tourner(0.5, angleCouleur);
        break;

    case 6:
        
        break;

    case 7:
        etape = loopEstCliqueEtRelache(3);
        break;

    case 8:
        etape = loopEstCliqueEtRelache(3);
        break;

    case 9:
        etape = loopEstCliqueEtRelache(3);
        break;

    case 10:
        etape = loopEstCliqueEtRelache(3);
        break;

    default:
        break;
    }

    if (etape > 1 && !tempsBobB()) etape = 11;
}