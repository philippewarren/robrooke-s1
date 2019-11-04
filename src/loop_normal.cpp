#include "loop_normal.h"

int angle = 0;

void loopNormal()
{
    changerAngleServo(PINCE, angle);
    Serial.println(angle);
    // if (Bob=='B')
    // {
    //     if(loopEstCliqueEtRelache(3)) octogoneB(VERT);
    //     if(loopEstCliqueEtRelache(0)) octogoneB(BLEU);
    //     if(loopEstCliqueEtRelache(1)) octogoneB(JAUNE);
    // }
    // else
    // {
    //     if(loopEstCliqueEtRelache(3)) octogoneA(VERT);
    //     if(loopEstCliqueEtRelache(0)) octogoneA(BLEU);
    //     if(loopEstCliqueEtRelache(1)) octogoneA(JAUNE);
    // }

    if (loopEstCliqueEtRelache(0)) angle += 5;
    if (loopEstCliqueEtRelache(1)) angle -= 5;
    if (loopEstCliqueEtRelache(3)) angle = 0;
    angle = (angle>180) ? 0 : angle;
    angle = (angle<0) ? 180 : angle;


}