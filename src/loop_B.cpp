#include "loop_B.h"

const long DEPART_BOB_B = 60*1000;

bool departBobB(long tempsInitialBumper)
{
    static long tempsInitial = 0;
    static long delais = 0;
    if (tempsInitial==0) tempsInitial = tempsInitialBumper;

    delais = millis()-tempsInitial;

    if (delais>=DEPART_BOB_B) return true;
    else return false;
}

void loopOctogoneB()
{
    //ajout;
    //retest;
}