#include <LibRobus.h>

void calculPulse180();
void calculPulseMin();
void calculPulseMax();

void initRot();

int readResetKeepDroit();
int readResetKeepGauche();
void encReset();

void DemiTour();

void Rot451Roue(int Nbr45 = 1 , bool dirGauche = false);

void Rot452Roue(int Nbr45 = 1 , bool dirGauche = false);