#include <LibRobus.h>
#include <fonctions_generales.h>

void avancerDroit(float distanceEnCm)
{
  float delta = -0.025;
  static float vitesseG = 0.4;
  static float vitesseD = vitesseG - delta;

  static float vitesseGPre = 2*vitesseG;
  static float vitesseDPre = 2*vitesseD;

  long clicsG = 0;
  long clicsD = 0;
  bool estRalenti = false;
  bool estAccelere = true;

  const float FACTEUR_P = 5E-2;  //4E-2; 7E-2
  const float FACTEUR_I = 5E-4;  //5E-5; 5E-4
  const float FACTEUR_D = 1.8E-5;   //1.7E-5; 1.8E-4
  const int TEMPS = 200;          //temps en microsecondes

  static float erreur = 0;
  long long cumulClics = 0;
  static float derniereErreur = 0;
  static float integrale = 0;  
  static float differentielle = 0;

  int i=0;
  int nb=100;
  int vitesseDebugG[nb];
  int vitesseDebugD[nb];
  int erreurDebug[nb];
  int integraleDebug[nb];
  int differentielleDebug[nb];
  float correctionDebug[nb];

  estRalenti = false;
  estAccelere = true;
  vitesseG=0.5*vitesseGPre;
  vitesseD=0.5*vitesseDPre;
  vitesseD=0.5*vitesseDPre;

	do
  {
		resetDeuxEncodeurs();
		
		changerVitesseDeuxMoteurs(vitesseG,vitesseD);
		
		delay(TEMPS);
    clicsG = (long)ENCODER_Read(0);
		clicsD = (long)ENCODER_Read(1);
    cumulClics+=clicsG;
    
		Serial.print("G: ");
    Serial.print(clicsG);
    Serial.print(" et D: ");
    Serial.print(clicsD);
    Serial.println();

	  erreur=(double)clicsG/TEMPS-(double)clicsD/TEMPS;
    integrale+=erreur;
    differentielle=erreur-derniereErreur;
    erreurDebug[i]=100000000*erreur*FACTEUR_P;
    vitesseDebugG[i]=1000*vitesseG;
    vitesseDebugD[i]=1000*vitesseD;
    integraleDebug[i]=100000000*integrale*FACTEUR_I;
    differentielleDebug[i]=100000000*differentielle*FACTEUR_D;
    correctionDebug[i]=FACTEUR_P*erreur+FACTEUR_I*integrale+FACTEUR_D*differentielle;
    i++;
	  vitesseD=vitesseD+FACTEUR_P*erreur+FACTEUR_I*integrale+FACTEUR_D*differentielle;
		changerVitesseMoteur(1,vitesseD);

    derniereErreur=erreur;

    if (!estRalenti)
    {
      vitesseGPre=vitesseG;
      vitesseDPre=vitesseD;
    }

    if (vitesseG >= 0.80) estAccelere=false;

    if (estAccelere)
    {
      vitesseG*=1.1;
      vitesseD*=1.1;
      changerVitesseDeuxMoteurs(vitesseG, vitesseD);
    }

    if (cumulClics > cmEnClics(distanceEnCm-50))
    {
      estRalenti=true;
      estAccelere=false;
      vitesseG*=0.8;
      vitesseD*=0.8;
      changerVitesseDeuxMoteurs(vitesseG, vitesseD);
    }
  }
	while (cumulClics < cmEnClics(distanceEnCm));

	arreterDeuxMoteurs();

  while (!ROBUS_IsBumper(0)) ;
  int nombre=i;
  i=0;
  Serial.println("Début des vitesses");
  for (i=0; i<nombre; i++)
  {
   // Serial.println(erreurDebug[i]);
   // Serial.println(integraleDebug[i]);
   // Serial.println(differentielleDebug[i]);
    Serial.print("G: ");
    Serial.print(vitesseDebugG[i]);
    Serial.print(" et D: ");
    Serial.print(vitesseDebugD[i]);
    Serial.println();
  }

  while (!ROBUS_IsBumper(1)) ;
  i=0;
  Serial.println("Début des erreur");
  for (i=0; i<nombre; i++)
  {
   // Serial.println(erreurDebug[i]);
   // Serial.println(integraleDebug[i]);
   // Serial.println(differentielleDebug[i]);
    Serial.print("P: ");
    Serial.print(erreurDebug[i]);
    Serial.print(" et I: ");
    Serial.print(integraleDebug[i]);
    Serial.print(" et D: ");
    Serial.print(differentielleDebug[i]);
    Serial.print(" pour une corr de: ");
    Serial.print(100000*correctionDebug[i]); 
    Serial.println();
  }
  return;
}