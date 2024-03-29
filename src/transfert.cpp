#include "transfert.h"

void afficher_tableau (int tableau[TAILLE_MAX][TAILLE_MAX],int& taille)
{
    Serial.print('\n');
     for (int i = 0;i<taille;i++) 
     {
        for (int j = 0;j<TAILLE_MAX;j++)
        {
            Serial.print(tableau[i][j]);
            Serial.print('\t');
        }
        Serial.print('\n');
     }  
    Serial.print('\n');
}

void detruire_ligne(int tableau[TAILLE_MAX][TAILLE_MAX],int& taille,int ligne)
{
    taille --;
    //décale le tableau à partir d'e ligne
    for (int i = ligne;i<taille;i++) 
        for (int j = 0;j<TAILLE_MAX;j++)
            tableau[i][j] = tableau[i+1][j];
}

void ajouter_ligne(int tableau[TAILLE_MAX][TAILLE_MAX],int& taille,int ajout[TAILLE_MAX])
{
    for (int j = 0; j<TAILLE_MAX;j++)
        tableau[taille][j] = ajout[j];
    taille++;
}

bool est_valide(int ligne[TAILLE_MAX],int taille_ligne)
{
    bool valide = true;

    for(int i = 0; i<taille_ligne;i++)
        for(int j = (i+1); j<taille_ligne;j++)
            if (ligne[i]==ligne[j])
                valide = false;

    return valide;
}

void calculer_trajet(int depart, int fin, int output[TAILLE_MAX])
{
    //variables locale
    bool bouclage = true;
    int trajet = -1;
    int distance = 0;

    int table_calcul [TAILLE_MAX][TAILLE_MAX];
    int taille = 0;

    //ajout de la ligne de départ
    int tampon [TAILLE_MAX] = {depart,-1};
    ajouter_ligne(table_calcul,taille,tampon);

    

    while (bouclage)
    {
        //initialisation de variables pratiques
        int i = 0;
        int branche = taille;

        //incrémentation de la distance
        distance ++;
        //mise à jour des branche
        while (i < branche)//pour chaque branche
        {
            //copie de la ligne
            for (int k = 0;k<TAILLE_MAX;k++)tampon[k] = table_calcul[0][k];
            //suppression de la ligne
            detruire_ligne(table_calcul,taille,0);

            //ajout de nouvelles lignes
            for (int j =0; j<NBR_RELATIONS[tampon[distance-1]];j++)
            {
                tampon[distance] = RELATION[tampon[distance-1]][j][0];
                tampon[distance+1]=-1;
                if (est_valide(tampon,distance+2))ajouter_ligne(table_calcul,taille,tampon);

            }
            i++;

        }

        //test si la fin du parcours est trouvée

        for(i=0;i<taille;i++)
             if (table_calcul[i][distance]==fin)//trajet trouvé
                {
                    trajet = i;
                    bouclage = false;
                }
        
        if (taille == 0)bouclage = false;//aucun trajet possible

    }

    //retour
    if (trajet == -1) output[0]=-1;
    else 
        for (int k = 0;k<TAILLE_MAX;k++)
            output[k] = table_calcul[trajet][k];
    
}


void afficher_trajet(int trajet[TAILLE_MAX])
{
    int i =0;
    while (trajet[i]!= -1 && i<TAILLE_MAX)
    {
        Serial.print(trajet[i]);
        Serial.print('\t');
        i++;
    }
    Serial.print('\n');
}