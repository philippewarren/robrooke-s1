#include "loop_normal.h"

int tableau[8];

void loopNormal()
{
    // loopAjustementServo(PINCE);
    // if(loopEstCliqueEtRelache(0)) ouvrirPince(true);
    // else if (loopEstCliqueEtRelache(1)) fermerPince(true);

    // if (loopEstCliqueEtRelache(3)) suivreLigneSimple(100, 0.5);

    if (Bob=='B')
    {
        if(loopEstCliqueEtRelache(3)) octogoneAlternatifB(VERT);
        if(loopEstCliqueEtRelache(0)) octogoneAlternatifB(JAUNE);
        if(loopEstCliqueEtRelache(1)) octogoneAlternatifB(ROUGE);
    }
    else
    {
        if(loopEstCliqueEtRelache(3)) octogoneAlternatifA(BLEU);
        if(loopEstCliqueEtRelache(0)) octogoneAlternatifA(ROUGE);
        if(loopEstCliqueEtRelache(1)) octogoneAlternatifA(JAUNE);
    }

    // if (loopEstCliqueEtRelache(3)) suivreLigneSimpleHuit(120, 0.2);

    // lireSuiveurLigne(tableau);
    // afficherLigne(tableau);
    // delay(800);
}