#include "interactions.h"

const byte PORT_DEL[] = {0, 45, 47, 49, 48};
const byte PORT_BOUTON[] = {40, 41, 42, 43, 44};

const byte PORT_INTERRUPT = 2;
const byte PORT_RESTART = PORT_BOUTON[BOUTON_RESTART];

bool loopEstCliqueEtRelache(uint8_t bumper)
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

void allumerDEL(uint8_t numeroDEL = 1)
{
    if (numeroDEL==1 || numeroDEL==2 || numeroDEL==3 || numeroDEL==4)
    {
        digitalWrite(PORT_DEL[numeroDEL], HIGH);
    }
    else
    {
        for (int i=1; i<=4; i++)
        {
            digitalWrite(PORT_DEL[i], HIGH);
        }
    }
    return;
}

void eteindreDEL(uint8_t numeroDEL = 1)
{
    if (numeroDEL==1 || numeroDEL==2 || numeroDEL==3 || numeroDEL==4)
    {
        digitalWrite(PORT_DEL[numeroDEL], LOW);
    }
    else
    {
        for (int i=1; i<=4; i++)
        {
            digitalWrite(PORT_DEL[i], LOW);
        }
    }
}

void flasherDEL(uint8_t numeroDEL = 1, int delais = 1000)
{
    allumerDEL(numeroDEL);
    delay(delais);
    eteindreDEL(numeroDEL);
    delay(delais);
}