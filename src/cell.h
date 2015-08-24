#ifndef CELL_H
#define CELL_H

#include "helper.h"

//Définition et listing de l'ensemble des cases existantes
#define CELL_EMPTY 0
#define CELL_GROUND 1

//cases de "téléportation"
#define CELL_DOOR 64

//cases non traversables (>=128)
#define CELL_WALL 128 //0x1000000

#endif