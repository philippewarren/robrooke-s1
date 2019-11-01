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
    
    static float angle1 = 0;
    static float angle2 = 0;
    static float distance = 0;
    static int etape = 0;
    static long timer = 0;
    if (etape !=0)
    {
    Serial.println(etape);
    }

    if (etape == 0 && loopEstCliqueEtRelache(3))
    {
        //initialisation
        timer = millis();
        switch (COULEURS_BOB[0])
        {
        case BLEU:
            angle1 = -90;
            angle2 = 0;
            distance = 0;
            break;
        
        case JAUNE:
            angle1 = 90;
            angle2 = 0;
            distance = 0;
            break;
        case ROUGE:
            angle1 = 50;
            angle2 = -50;
            distance = 30;
            break;
        case VERT:
            angle1 = -50;
            angle2 = 50;
            distance = 30;
            break;
        }
        etape = 1;
    }
    if (millis() - timer < 59500)
    {
        switch (etape)
        {
        case 1:
            if (tourner(0.5,angle1))etape = 2;
            break;
        case 2:
            if (avancerDroit(0.5,distance))etape = 3;
            break;
        case 3:
            if(tourner(0.5,angle2))etape = 0;
            break;
        case 4:
            if(traquerLigne(0.5))etape = 5;
            break;
        
        }
    }
}