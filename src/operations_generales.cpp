#include "operations_generales.h"

void classerTableauCroissant(uint16_t tableau[], const int NB_ELEMENTS)
{
    uint16_t temp;
    
    for (int i=0; i<NB_ELEMENTS-1; i++)
    {
        for (int j=i+1; j<NB_ELEMENTS-1; j++)
        {
            if(tableau[i]>tableau[j])
            {
                temp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = temp;
            }
        }
    }
    return;
}

uint16_t calculerMediane(uint16_t tableau[], const int NB_ELEMENTS)
{
    int position;
    uint16_t mediane;

    classerTableauCroissant(tableau, NB_ELEMENTS);
    position = ((NB_ELEMENTS-1)/2);
    mediane = tableau[position];

    return mediane;
}

// int sensRotationAngle(float angle)
// {
//     if (angle>=0) return 1;
//     else return 0;
// }