#include "loop_normal.h"

int itt = 0;
float vitesse = 0.3;
bool lecture = false;
bool avancerLigne = false;
bool avancerDroit2 = false;
bool ligne = false;
long timerFinLigne = 0;
bool timerLance = false;
int angleCourrant = 0;
void loopNormal()
{
    if (Bob=='A') loopOctogoneA();
    else loopOctogoneB();

}