#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include <LibRobus.h>
#include "init_robot.h"

#define PINCE 0
#define BRAS 1

//Appelée par initialiserBob, set les angles des servos ouverts et fermés selon le robot.
void initialiserConstantesServos();

//Initialise un servo à son angle initial (BRAS: 0 ou PINCE: 1)
bool initialiserServo(uint8_t indexDuServomoteur, bool estFixe = false);

void initialiserDeuxServos();

//Active un servomoteur s'il ne l'était pas déjà (BRAS: 0 ou PINCE: 1)
void activerServo(uint8_t indexDuServomoteur);
//Désactive un servomoteur s'il ne l'était pas déjà (BRAS: 0 ou PINCE: 1)
void desactiverServo(uint8_t indexDuServomoteur);

//Pose l'angle d'un servo (BRAS: 0 ou PINCE: 1)
bool changerAngleServo(uint8_t indexDuServomoteur, uint8_t angle, bool estFixe = true);

//Ouvre la pince et la maintiens ouverte par défaut
bool ouvrirPince(bool estFixe = true);
//Ferme la pince et la maintiens fermée par défaut
bool fermerPince(bool estFixe = true);

//Lève le bras et le maintiens levé par défaut
bool leverBras(bool estFixe = true);
//Baisse le bras et le maintiens baissé par défaut
bool baisserBras(bool estFixe = true);
//Lève le bras verticalement et le maintiens levé par défaut
bool leverBrasDeplacement(bool estFixe = true);

//Ouvre la pince et attend un délais non-bloquant, puis retourne true
bool ouvrirPinceOctogone(bool estFixe = true);
//Ferme la pince et attend un délais non-bloquant, puis retourne true
bool fermerPinceOctogone(bool estFixe = true);

//Utilisée pour ajuster les angles des servos
//BRAS: 0 PINCE: 1
void loopAjustementServo(uint8_t indexDuServomoteur);


#endif