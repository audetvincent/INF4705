#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include "Exemplaire.h"
#include "Solution.h"
#include <limits.h>

Exemplaire* lireFichier(std::string nom);

bool relieEntree(float** sentiers, int point, int nbPoints, bool* visites);

int sentierMin(int noeud, Solution &s, Exemplaire &e);

int sentierMax(float* sentiers, int nbPoints);

#endif
