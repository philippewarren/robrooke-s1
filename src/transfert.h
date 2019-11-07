#ifndef TRANSFERT_H
#define TRANSFERT_H

#include <Arduino.h>

//utilisation de  vector pour pauvre//////////////////////////////////////////////////////////////////////

const int TAILLE_MAX = 10;

//pour débug
void afficher_tableau (int tableau[TAILLE_MAX][TAILLE_MAX],int& taille);

//pour ajouter et retirer une ligne

//Retire la ligne désirée du tableau, décale les autre ligne et réduit la taille de 1
void detruire_ligne(int tableau[TAILLE_MAX][TAILLE_MAX],int& taille,int ligne);
//ajoute la ligne à la fin du tableau et augmente la taille de 1
void ajouter_ligne(int tableau[TAILLE_MAX][TAILLE_MAX],int& taille,int ajout[TAILLE_MAX]);

//fin utilisation de vector pour pauvre//////////////////////////////////////////////////////////////////


//calcule de trajet//////////////////////////////////////////////////////////////////////////////////////

//constante et variable globale

//le concepte de noeud est important pour ce code. Chaque noeud représente une intersection et sont numéroté à partir de 0.

//orientation:
//    0
//    |
//90-----270
//    |
//   180

//position
/*
            0
            |
        3---1---4
            |
        5---2---6
*/
const int NBR_NOEUD = 7;

//nombre de relation pour chaque noeud
const int NBR_RELATIONS[NBR_NOEUD] = 
{
    1,
    4,
    3,
    1,
    1,
    1,
    1
};

/*Description des relations:
RELATION[numéro noeud][numéro de relation][0] = noeud 
RELATION[numéro noeud][numéro de relation][1] = angle d'accès 
*/
const int RELATION [NBR_NOEUD][NBR_NOEUD-1][2] =
{
    /*noeud 0*/
    {
        {1,180}
    },
    /*noeud 1*/
    {
        {0,0},
        {3,90},
        {2,180},
        {4,270}
    },
    /*noeud 2*/
    {
        {1,0},
        {5,90},
        {6,180}
    },
    /*noeud 3*/
    {
        {1,270}
        
    },
    /*noeud 4*/
    {
        {1,90}
    },
    /*noeud 5*/
    {
        {2,270}
    },
    /*noeud 6*/
    {
        {6,90}
    }
};

//calcule le trajet, la fonction retourne une suite de noeud débutant par le départ et finissant par -1, le départ doit exister et la fin ne doit pas être le départ
void calculer_trajet(int depart, int fin, int output[TAILLE_MAX]);

//pour debug
void afficher_trajet(int trajet[TAILLE_MAX]);

//Mouvement entre les noeuds/////////////////////////////////

//fonction pour modification de la position

//orientation:
//    0
//    |
//90-----270
//    |
//   180

//position
/*
            0
            |
        3---1---4
            |
        5---2---6
*/

void poserEtat(int position = -1, int orientation = -1);






#endif