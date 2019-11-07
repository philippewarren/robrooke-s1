#include "loop_normal.h"

void loopNormal()
{
    // loopAjustementServo(PINCE);
    // if(loopEstCliqueEtRelache(0)) ouvrirPince(true);
    // else if (loopEstCliqueEtRelache(1)) fermerPince(true);

    // if (loopEstCliqueEtRelache(3)) suivreLigneSimple(100, 0.5);

    if (Bob=='B')
    {
        if(loopEstCliqueEtRelache(3)) octogoneB(VERT);
        if(loopEstCliqueEtRelache(0)) octogoneB(ROUGE);
        if(loopEstCliqueEtRelache(1)) octogoneB(JAUNE);
    }
    else
    {
        if(loopEstCliqueEtRelache(3)) octogoneA(ROUGE);
        if(loopEstCliqueEtRelache(0)) octogoneAlternatifA(ROUGE);
        if(loopEstCliqueEtRelache(1)) octogoneA(JAUNE);
    }

    // if (loopEstCliqueEtRelache(3)) suivreLigneSimpleHuit(120, 0.2);
}