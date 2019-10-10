#include "mouvement.h"

bool estClicEtRelache(uint8_t bumper)
{
    const int NBR_BUMPER = 4;
    bool resultat = false;
    static bool listeBumperEtat[NBR_BUMPER] = {false, false, false, false};
    if(ROBUS_IsBumper(bumper))
        listeBumperEtat[bumper] = true;
    else
        if(listeBumperEtat[bumper])
        {
            resultat = true;
            listeBumperEtat[bumper] = false;
        }
    return resultat;
}