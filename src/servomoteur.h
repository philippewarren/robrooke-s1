#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include <LibRobus.h>

#define PINCE 0
#define BRAS 1

//Initialise un servo à son angle initial (BRAS: 0 ou PINCE: 1)
void initialiserServo(uint8_t indexDuServomoteur, bool estFixe = false);

//Active un servomoteur s'il ne l'était pas déjà (BRAS: 0 ou PINCE: 1)
void activerServo(uint8_t indexDuServomoteur);
//Désactive un servomoteur s'il ne l'était pas déjà (BRAS: 0 ou PINCE: 1)
void desactiverServo(uint8_t indexDuServomoteur);

//Pose l'angle d'un servo (BRAS: 0 ou PINCE: 1)
void changerAngleServo(uint8_t indexDuServomoteur, uint8_t angle, bool estFixe = true);

//Ouvre la pince et la libère par défaut
void ouvrirPince(bool estFixe = false);
//Ferme la pince et la maintiens fermée par défaut
void fermerPince(bool estFixe = true);




#endif