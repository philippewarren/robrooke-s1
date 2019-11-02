#include "loop_normal.h"


void loopNormal()
{
    if(loopEstCliqueEtRelache(3)) octogoneA(VERT);
    if(loopEstCliqueEtRelache(0)) octogoneA(BLEU);
    if(loopEstCliqueEtRelache(1)) octogoneA(JAUNE);

}