#include "interactions.h"

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
    if (numeroDEL==1||2||3||4)
    {
        digitalWrite(portDEL[numeroDEL], HIGH);
    }
    else if (numeroDEL==0)
    {
        for (int i=1; i<=4; i++)
        {
            digitalWrite(portDEL[i], HIGH);
        }
    }
}

void eteindreDEL(uint8_t numeroDEL = 1)
{
    if (numeroDEL==1||2||3||4)
    {
        digitalWrite(portDEL[numeroDEL], LOW);
    }
    else if (numeroDEL==0)
    {
        for (int i=1; i<=4; i++)
        {
            digitalWrite(portDEL[i], LOW);
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