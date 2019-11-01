#include "loop_B.h"

const long DEPART_BOB_B = 60*1000 + 1000;
const long ARRET_BOB_B = 60*1000*2 - 1000;

bool departBobB(long tempsInitialBumper)
{
    static long tempsInitial = 0;
    static long delais = 0;
    if (tempsInitial==0) tempsInitial = tempsInitialBumper;

    delais = millis()-tempsInitial;

    if (delais>=DEPART_BOB_B && delais<ARRET_BOB_B) return true;
    else return false;
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
    static float distance = 0;
    
    /*Etapes:
        0: attendre l'appui
        1: attendre le temps
        2: avancer vers ballon au centre
        3: ramasser ballon
        4: calcul de l'itinéraire selon la couleur
        5: rotation en fonction de la couleur
        6: avancer jusqu'à la ligne
        7: avancer en suivant la ligne
        8: avancer jusqu'au noir
        9: déposer ballon
        10: reculer un peu
    */
    static int etape = 0;

    switch (etape)
    {
    case 0:
        etape = loopEstCliqueEtRelache(3);
        break;
    case 1;
    
    default:
    } break;
    }
}