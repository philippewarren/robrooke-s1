#include "loop_urgence.h"

void loopUrgence()
{
    static int compteur = 0;
    allumerDEL(0);
    Serial.print("Interrompu ");
    Serial.println(compteur++);
    if (digitalRead(PORT_RESTART))
    {
        eteindreDEL(0);
        arretUrgence = false;
    }
}