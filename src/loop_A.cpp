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
    static int ancEtape = 0;
    if (etape != ancEtape)
    {
    Serial.println(etape);
    ancEtape = etape;
    }

    if (etape == 0 && loopEstCliqueEtRelache(3))
    {
        //initialisation
        timer = millis();
        switch (COULEURS_BOB[0])
        {
        case BLEU:
            angle1 = -135;
            break;
        
        case JAUNE:
            angle1 = 135;
            break;
        case ROUGE:
            angle1 = 45;
            break;
        case VERT:
            angle1 = -45;
            break;
        }
        etape = 1;
    }
    if (millis() - timer < 59500)
    {
        switch (etape)
        {
        case 1:
            //aller au milieu
            if (avancerDroit(0.3,50))etape = 101;
            break;
        case 101:
            //ouvrir la pince
            if (ouvrirPinceOctogone(true))etape = 2;
            break;
        case 2:
            //tourner vers couleur
            if (tourner(0.3,angle1))etape = 3;
            break;
        case 3:
            //sortir milieu
            if (avancerDroit(0.3,20))etape = 4;
            break;
        case 4:
            //suivre ligne
            if (avancerDroitLigne(0.3,75))etape = 602;
            break;
        case 602:
            //aller au ballon
            if (avancerDroitLigne(0.3,40))etape = 7;
        case 7:
            //prendre ballon
            if (fermerPinceOctogone(true))etape = 8;
            break;
        case 8:
            //demi-tour
            if(tourner(0.3,210))etape = 10;
            break;
        case 10:
            //aller au milieu
            if(avancerDroit(0.3,50))etape = 1004;
            break;
       
        case 1004:
            if(avancerDroitLigne(0.3,70+35))etape = 11;
            break;
        case 11:
            //lacher ballon
            if(ouvrirPinceOctogone(true))etape = 12;
            break;
        case 12:
            //reculer
            if (avancerDroit(-0.3,-50))etape = 13;
            break;
        case 13:
            //tourner
            if (tourner(0.3,90))etape = 14;
            break;
        case 14:
            //avancer
            if(avancerDroitLigne(0.3,50))etape = 0;
            break;


        
        }
    }
}