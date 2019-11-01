#include "loop_A.h"
#include "init_robot.h"
#include "Arduino.h"
#include "interactions.h"
#include "mouvement.h"
#include "suiveur_ligne.h"

//COULEUR_DEPART
//COULEUR_FIN
//COULEUR_OCTOGONE

//etape
//0 attendre
//1 rotation
//2 avancer (vert / rouge)
//3 rotation (vert / rouge)
//4 intercepter et suivre ligne
//5 prendre ballon
//6 demi tour
//7 suivre ligne
//8 lacher ballon
//9 rotation
//10 aller se cacher

void loopOctogoneA()
{
    static int etape = 0;
    static long timer = 0;
    if (etape = 0 & loopEstCliqueEtRelache(3))
    {
        timer = millis();
        etape = 1;
    }
    if (millis() - timer < 59500)
    {
        switch (etape)
        {
        case 1:
            break;
        case
        
        }
    }
}