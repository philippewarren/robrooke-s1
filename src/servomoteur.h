#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include <LibRobus.h>

#define PINCE 0
#define BRAS 1

//Initialise un servo à son angle initial (BRAS: 0 ou PINCE: 1)
void initialiserServoFixe(uint8_t indexDuServomoteur);

//Initialise un servo à son angle initial, puis le libère (BRAS: 0 ou PINCE: 1)
void initialiserServoLibre(uint8_t indexDuServomoteur);

//Active un servomoteur s'il ne l'était pas déjà (BRAS: 0 ou PINCE: 1)
void activerServo(uint8_t indexDuServomoteur);

//Désactive un servomoteur s'il ne l'était pas déjà (BRAS: 0 ou PINCE: 1)
void desactiverServo(uint8_t indexDuServomoteur);

//Pose l'angle d'un servo (BRAS: 0 ou PINCE: 1)
void changerAngleServoFixe(uint8_t indexDuServomoteur, uint8_t angle);

//Pose l'angle d'un servo, puis le libère (BRAS: 0 ou PINCE: 1)
void changerAngleServoLibre(uint8_t indexDuServomoteur, uint8_t angle);

//Ouvre la pince et la libère par défaut
void ouvrirPince(bool estFixe = false);
//Ferme la pince et la maintiens fermée par défaut
void fermerPince(bool estFixe = true);




#endif