#include "loop_A.h"
#include "init_robot.h"
#include "Arduino.h"
#include "interactions.h"
#include "mouvement.h"
#include "suiveur_ligne.h"
#include "operations_generales.h"

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
void octogoneA(int couleur = -1500)
{
    //initialisation
    float angle = 0;
    float angleRetour = 0;
    float vitesse = 0.3;
    float distanceCentre = 0;
    float distanceRetour = 0;
    float distanceSortie = 20;
    if (couleur == -1500)couleur = COULEURS_BOB[0];
    switch (couleur)
        {
        case BLEU:
            angle = -135;
            angleRetour = 180;
            distanceCentre = 42;
            distanceRetour = 54;
            break;
        case JAUNE:
            angle = -235;
            angleRetour = 180;
            distanceCentre = 42;
            distanceRetour = 68;
            break;
        case ROUGE:
            angle = -34;
            angleRetour = 180;
            distanceCentre = 37;
            distanceRetour = 54;
            distanceSortie = 30;
            break;
        case VERT:
            angle = -45;
            angleRetour = 180;
            distanceCentre = 42;
            distanceRetour = 60;
            break;
        }
    
    avancerDroitBloque(vitesse-0.1,distanceCentre);
    delay(300);
    tournerBloque(vitesse,angle);
    avancerDroitBloque(vitesse,distanceSortie);
    centrerLigne(10);
    //trouverLigne(sensRotationAngle(angle));
    avancerDroitLigneBloque(vitesse,55);
    // suivreLigneSimple(55, vitesse);
    ouvrirPince(true);
    delay(2000);
    avancerDroitBloque(vitesse,45);
    avancerDroitBloque(vitesse, -2);
    fermerPince();
    delay(2000);
    avancerDroitBloque(vitesse,-35);
    tournerBloque(vitesse,angleRetour);
    //centrerLigne(10);
    avancerDroitLigneBloque(vitesse,distanceRetour);
    // suivreLigneSimple(distanceRetour, vitesse);
    ouvrirPince();
    delay(2000);
    avancerDroitBloque(vitesse,-50);
    tournerBloque(vitesse+0.1,90);
    avancerDroitBloque(vitesse,60);
    }

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

void octogoneAlternatifA(int couleur = -1500)
{
    //initialisation
    int sensInitial = 0;
    bool passeParCentreDebut = true;
    float distanceDebut = 0;
    float distanceMilieu = 0;
    float pythagoreDiagonale = 0;
    float distanceSortieCouleur = 0;
    float distanceLigne = 0;
    float distanceCoin = 0;
    
    float vitesse = 0.3;    
    
    if (couleur == -1500) couleur = COULEURS_BOB[0];
    
    switch (couleur)
        {
        case BLEU:
            sensInitial = -1;
            passeParCentreDebut = false;
            distanceDebut = 45;
            distanceMilieu = 70;
            pythagoreDiagonale = 20;
            distanceSortieCouleur = 45;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
        case JAUNE:
            sensInitial = 1;
            passeParCentreDebut = false;
            distanceDebut = 45;
            distanceMilieu = 70;
            pythagoreDiagonale = 30;
            distanceSortieCouleur = 48;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
        case ROUGE:
            sensInitial = 1;
            passeParCentreDebut = true;
            distanceDebut = 45;
            distanceMilieu = 70;
            pythagoreDiagonale = 38;
            distanceSortieCouleur = 45;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
        case VERT:
            sensInitial = -1;
            passeParCentreDebut = true;
            distanceDebut = 45;
            distanceMilieu = 70;
            pythagoreDiagonale = 20;
            distanceSortieCouleur = 45;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
        }
    
    if (passeParCentreDebut==true)
    {
        avancerDroitBloque(vitesse-0.1, distanceDebut);     //avance au milieu
        delay(300);
        tournerBloque(vitesse,sensInitial*90);              //tourne de 90 à droite ou à gauche selon la couleur
        avancerDroitBloque(vitesse,distanceDebut);          //sort du milieu
        tournerBloque(vitesse, -sensInitial*90);            //tourne vers l'avant (vers la couleur)
        avancerDroitBloque(vitesse, pythagoreDiagonale);    //avance jusqu'à la diagonale
        ouvrirPince(true);
        delay(2000);
        suivreLigneSimpleHuit(150, vitesse-0.1);            //suit la ligne jusqu'à la zone noire et fonce dans le ballon
        avancerDroitBloque(vitesse-0.15, -1);               //recule un peu
        fermerPince(true);
        delay(2000);
        tournerBloque(vitesse, sensInitial*(180-40));       //tourne vers la ligne du carré
        avancerDroitBloque(vitesse, distanceSortieCouleur); //sort de la couleur vers la ligne du carré
        suivreLigneSimpleHuit(distanceLigne, vitesse-0.1);  //suit la ligne jusqu'au milieu
        tournerBloque(vitesse, sensInitial*90);             //tourne face au milieu
        avancerDroitBloque(vitesse, distanceMilieu);        //avance au milieu
        ouvrirPince(true);
        delay(2000);
        avancerDroitBloque(vitesse,distanceCoin);           //recule dans le coin
    }
    else
    {
        // avancerDroitBloque(vitesse-0.1, distanceDebut);     //avance au milieu
        // delay(300);
        tournerBloque(vitesse,sensInitial*90);              //tourne de 90 à droite ou à gauche selon la couleur
        // avancerDroitBloque(vitesse,distanceDebut);          //sort du milieu
        // tournerBloque(vitesse, -sensInitial*90);            //tourne vers l'avant (vers la couleur)
        avancerDroitBloque(vitesse, pythagoreDiagonale);    //avance jusqu'à la diagonale
        ouvrirPince(true);
        delay(2000);
        suivreLigneSimpleHuit(150, vitesse-0.1);            //suit la ligne jusqu'à la zone noire et fonce dans le ballon
        avancerDroitBloque(vitesse-0.15, -1);               //recule un peu
        fermerPince(true);
        delay(2000);
        tournerBloque(vitesse, sensInitial*(180-40));          //tourne vers la ligne du carré
        avancerDroitBloque(vitesse, distanceSortieCouleur); //sort de la couleur vers la ligne du carré
        suivreLigneSimpleHuit(distanceLigne, vitesse-0.1);  //suit la ligne jusqu'au milieu
        tournerBloque(vitesse, sensInitial*90);             //tourne face au milieu
        avancerDroitBloque(vitesse, distanceMilieu);        //avance au milieu
        ouvrirPince(true);
        delay(2000);
        avancerDroitBloque(vitesse,distanceCoin);           //recule dans le coin
        delay(60000);
    }
    
}