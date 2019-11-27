#include "capteur_couleur.h"

Adafruit_TCS34725 CapteurCouleur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

const uint16_t BORNES_COULEUR[] = {15, 165};

const int SEUIL_NOIR = 35;
const int SEUIL_BLANC = 85;
const int SEUIL_GRIS = 15;

void initialiserCapteurCouleur()
{
    if (CapteurCouleur.begin())
    {
        Serial.println("##Capteur couleur branché.##");
    }
    else
    {
        Serial.println("##Pas de capteur couleur... Verifiez la connection.##");
    }
    return;
}

void rgbEnHsl(uint16_t tableauRGB[4])
{
  uint16_t etendue = BORNES_COULEUR[1]-BORNES_COULEUR[0];
  
  float rouge = ((float)tableauRGB[0]-BORNES_COULEUR[0])/(etendue);
  float vert = ((float)tableauRGB[1]-BORNES_COULEUR[0])/(etendue);
  float bleu = ((float)tableauRGB[2]-BORNES_COULEUR[0])/(etendue);

  float Cmax = max(rouge, max(vert, bleu));
  float Cmin = min(rouge, min(vert, bleu));
  float delta = Cmax-Cmin;
  float preS;

  uint16_t H, S, L;

  if (delta==0) H = 0;
  else if (Cmax==rouge) H = (uint16_t)(60*(((vert-bleu)/delta) + (vert<bleu ? 6 : 0)));
  else if (Cmax==vert) H = (uint16_t)(60*(((bleu-rouge)/delta) + 2));
  else if (Cmax==bleu) H = (uint16_t)(60*(((rouge-vert)/delta) + 4));

  preS = (delta==0) ? 0 : delta/(1-fabs(2*((Cmax+Cmin)/2)-1));
  S = (uint16_t)(100*pow(preS, 0.5));

  L = (uint16_t)(100*(Cmax+Cmin)/2); 

  tableauRGB[0] = H;
  tableauRGB[1] = S;
  tableauRGB[2] = L;
   
  return;
}

void lireCapteurCouleur(uint8_t numeroDeCapteur, uint16_t tableauVide[4])
{    
    uint16_t rouge, vert, bleu, sansCouleur;

    CapteurCouleur.getRawData(&rouge, &vert, &bleu, &sansCouleur);
    
    tableauVide[0] = (uint16_t)(256*(float)rouge/sansCouleur);
    tableauVide[1] = (uint16_t)(256*(float)vert/sansCouleur);
    tableauVide[2] = (uint16_t)(256*(float)bleu/sansCouleur);
    tableauVide[3] = sansCouleur;

    rgbEnHsl(tableauVide);
   
    return;
}

int evaluerCouleur(uint16_t tableauRGB[4])
{
    int couleur = 0;

    //Blanc, noir, gris
    if (tableauRGB[1]<=SEUIL_GRIS || (tableauRGB[2]<=SEUIL_NOIR || tableauRGB[2]>=SEUIL_BLANC))
    {
        // Blanc?
        if (tableauRGB[2]>=SEUIL_BLANC) couleur = BLANC;
        //Noir?
        else if (tableauRGB[2]<=SEUIL_NOIR) couleur = NOIR;
        //Gris?
        else couleur = GRIS;
    }
    else
    {
        //Rouge?
        if (tableauRGB[0]>=345 || tableauRGB[0]<45) couleur = ROUGE;
        //Jaune?
        else if (tableauRGB[0]>=45 && tableauRGB[0]<90) couleur = JAUNE;
        //Vert?
        else if (tableauRGB[0]>=120 && tableauRGB[0]<150) couleur = VERT;
        //Bleu?
        else if (tableauRGB[0]>=150 && tableauRGB[0]<190) couleur = BLEU;
        //Aucune couleur reconnue
        else couleur = AUCUNE;
    }
    return couleur;
}

int obtenirCouleurLettre()
{
    uint16_t tableau[4];
    lireCapteurCouleur(0,tableau);
    return evaluerCouleur(tableau);
}

void debugCapteurCouleur()
{
    static uint16_t tableau[4];
    static String nomCouleur;
    lireCapteurCouleur(0, tableau);
    
    Serial.print("H: ");
    Serial.print(tableau[0]);
    Serial.print("\tS: ");
    Serial.print(tableau[1]);
    Serial.print("\tL: ");
    Serial.print(tableau[2]);
    Serial.print("\tC: ");
    Serial.print(tableau[3]);
    Serial.print("\tCouleur: ");
    allumerDELCouleur(evaluerCouleur(tableau));
    switch (evaluerCouleur(tableau))
    {
        case ROUGE:
            nomCouleur = "ROUGE";
            break;
        case BLEU:
            nomCouleur = "BLEU";
            break;
        case VERT:
            nomCouleur = "VERT";
            break;
        case JAUNE:
            nomCouleur = "JAUNE";
            break;
    }
    Serial.println(nomCouleur);
    delay(1000);
}