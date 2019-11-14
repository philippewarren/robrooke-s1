#include "loop_B.h"
#include "init_robot.h"

const long long DEPART_BOB_B = 2000;// 60*1000 + 1000;
const long long ARRET_BOB_B = 119000;

bool tempsBobB()
{
    bool retour = false;
    static long tempsInitial = 0;
    long delais = 0;
    if (tempsInitial==0) tempsInitial = millis();

    delais = millis()-tempsInitial;

    if (delais>=ARRET_BOB_B)
    {
        retour = false;
    }
    else if (delais>=DEPART_BOB_B)
    {
        retour = true;
    }

    Serial.println(delais);
    Serial.println(retour);

    return retour;
}

/* Plan de l'octogone
R # # # V
# # B # #
# # O # #
# # A # #
J # # # B
*/
//Ordre modifiable au besoin {R    , V   , B   , J    }
const int ORDRE_COULEURS[] = {ROUGE, VERT, BLEU, JAUNE};

float calculAngleCouleur(int COULEUR)
{
    float angle = 0;
    if (COULEUR == ORDRE_COULEURS[0])
    {
        angle = -(90+45);
    }
    else if (COULEUR == ORDRE_COULEURS[1])
    {
        angle = -360+(90+45);
    }
    else if (COULEUR == ORDRE_COULEURS[2])
    {
        angle = -360+(45);
    }
    else //COULEUR == ORDRE_COULEURS[3]
    {
        angle = (-45);
    }

    return angle;
}

/* Plan de l'octogone
R # # # V
# # B # #
# # O # #
# # A # #
J # # # B
*/


void loopOctogoneB(int COULEUR = -1500)
{
    //Tableau lié aux étape:   {0, 1, 2, 03, 4, 05, 6, 07, 8, 09, 10, 11, 012, 13}
    static float distances[] = {0, 0, 0, 42, 0, 00, 0, 20, 0, 65, 00, 35, -10, 00};
    //static int distance = 0;
    static float angleCouleur = 0;
    if (COULEUR == -1500) COULEUR = COULEURS_BOB[1];
    
    /*Etapes:
        0: attendre l'appui du bumper arrière
        1: attendre le temps d'une minute
        2: ouvrir pince
        3: avancer vers ballon au centre
        4: ramasser ballon
        5: avancer au centre
        6: rotation en fonction de la couleur
        7: avancer jusqu'à la ligne
        8: crise d'épilepsie
        9: suivre la ligne
        10: avancer jusqu'au noir
        11: déposer ballon
        12: reculer un peu
        13 (default): fini
    */
    static int etape = 0;

    if (etape!=12) Serial.println(etape);

    switch (etape)
    {
    case 0:
        if (angleCouleur == 0) angleCouleur = calculAngleCouleur(COULEUR);
        if (loopEstCliqueEtRelache(3)) etape += 1;
        break;

    case 1:
        if (tempsBobB()) etape += 1;
        break;

    case 2:
        if (ouvrirPinceOctogone(true)) etape += 1;
        break;

    case 3:
        if (avancerDroit(0.16, distances[etape])) etape += 1;
        break;

    case 4:
        if (fermerPinceOctogone(true)) etape += 1;
        break;

    case 5:
        if (avancerDroit(0.3, distances[etape])) etape += 1;
        break;

    case 6:
        if (tourner(0.15, angleCouleur)) etape += 1;
        break;

    case 7:
        if (avancerDroit(0.3, distances[etape])) etape += 1;
        break;
    
    case 8:
        //Étape bloquante
        centrerLigne();
        etape += 1;
        break;
    
    case 9:
        // if (traquerLigne(0.3)) etape += 1;
        // if (avancerDroit(0.3, 65)) etape += 1;
        if (avancerDroitLigne(0.3, distances[etape])) etape += 1;
        break;
    
    case 10:
        if (ouvrirPinceOctogone(true)) etape += 1;
        break;
    
    case 11:
        if (avancerDroit(0.3, distances[etape])) etape += 1;
        break;

    // case 12:
    //     if (avancerDroit(0.2, distances[etape])) etape += 1;
    //     break;

    default:
        arreterDeuxMoteurs();
        desactiverServo(PINCE);
        break;
    }

    if (etape > 1 && !tempsBobB()) etape = 13;
}

void octogoneB(int COULEUR = -1500)
{
    //initialisation
    float angle = 0;
    float vitesse = 0.3;
    float distanceCentre = 35;
    float distanceLigne = 20;
    float distanceZoneCouleur = 65;
    float distancePousserBallon = 35;
    if (COULEUR == -1500) COULEUR = COULEURS_BOB[1];

    angle = calculAngleCouleur(COULEUR);
    switch (COULEUR)
    {
    case BLEU:
        distanceCentre = 35;
        distanceLigne = 20;
        distanceZoneCouleur = 65;
        distancePousserBallon = 35;
        break;
    case JAUNE:
        distanceCentre = 35;
        distanceLigne = 20;
        distanceZoneCouleur = 65;
        distancePousserBallon = 35;
        break;
    case ROUGE:
        distanceCentre = 35;
        distanceLigne = 20;
        distanceZoneCouleur = 65;
        distancePousserBallon = 35;
        break;
    case VERT:
        distanceCentre = 35;
        distanceLigne = 20;
        distanceZoneCouleur = 65;
        distancePousserBallon = 35;
        break;
    }

    delay(2000);

    ouvrirPince(true);
    delay(1500);
    avancerDroitBloque(vitesse-0.15, distanceCentre);
    fermerPince(true);
    delay(1500);
    avancerDroitBloque(vitesse-0.1, 5);
    tournerBloque(vitesse/2, angle);
    avancerDroitBloque(vitesse, distanceLigne);
    // centrerLigne(30);
    avancerDroitLigneBloque(vitesse, distanceZoneCouleur);
    // suivreLigneSimple(distanceZoneCouleur, vitesse);
    ouvrirPince(true);
    delay(1500);
    avancerDroitBloque(vitesse+0.2, distancePousserBallon);
    delay(60000);
}

void octogoneAlternatifB(int couleur = -1500)
{
    //initialisation
    float sensInitial = 0;
    bool rotation180Debut = true;
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
            sensInitial = 1;
            rotation180Debut = false;
            distanceDebut = 30;
            distanceMilieu = 70;
            pythagoreDiagonale = 0;
            distanceSortieCouleur = 45;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
        case JAUNE:
            sensInitial = -1;
            rotation180Debut = false;
            distanceDebut = 30;
            distanceMilieu = 70;
            pythagoreDiagonale = 0;
            distanceSortieCouleur = 48;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
        case ROUGE:
            sensInitial = 1;
            rotation180Debut = true;
            distanceDebut = 30;
            distanceMilieu = 70;
            pythagoreDiagonale = 0;
            distanceSortieCouleur = 45;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
        case VERT:
            sensInitial = -1;
            rotation180Debut = true;
            distanceDebut = 30;
            distanceMilieu = 70;
            pythagoreDiagonale = 1;
            distanceSortieCouleur = 45;
            distanceLigne = 50;
            distanceCoin = -95;
            break;
    }
    
    
    delay(68000);                                        //attend 61 secondes

    ouvrirPince(true);
    delay(1500);
    avancerDroitBloque(vitesse-0.15, distanceDebut);    //avance au milieu
    fermerPince(true);
    avancerDroitBloque(vitesse-0.15, 5);
    delay(1500);
    if (rotation180Debut==true)
    {
        // avancerDroitBloque(vitesse-0.1, 5);             //Se centre
        // delay(300);
        avancerDroitBloque(vitesse, distanceDebut+15);
        delay(300);
        tournerBloque(vitesse/2, 168);                  //Demi-tour
        avancerDroitBloque(vitesse, 2*distanceDebut+15);     //Sort du centre
    }
    else avancerDroitBloque(vitesse, 5+distanceDebut);  //
    delay(500);
    tournerBloque(vitesse/2,sensInitial*85);              //tourne de 90 à droite ou à gauche selon la couleur
    avancerDroitBloque(vitesse, pythagoreDiagonale);    //avance jusqu'à la diagonale
    suivreLigneSimpleHuit(150, vitesse-0.1);            //suit la ligne jusqu'à la zone noire et fonce dans le ballon
    // avancerDroitBloque(vitesse-0.1, -40);
    // ouvrirPince(true);
    // delay(2000);
    // avancerDroitBloque(vitesse, 20);
    delay(60000);
}