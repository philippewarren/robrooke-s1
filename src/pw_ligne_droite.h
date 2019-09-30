const double CLICS_PAR_CM;

double clicsEnCm(long nbClics);

long long cmEnClics(float nbCm);

void resetDeuxEncodeurs();

void changerVitesseMoteur(uint8_t moteur, float nouvelleVitesse);

void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD);

void arreterDeuxMoteurs();

void avancerDroit(float distanceEnCm);