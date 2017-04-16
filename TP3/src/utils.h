#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include "Exemplaire.h"
#include "Solution.h"
#include <limits.h>
#include <vector>

Exemplaire* lireFichier(std::string nom);

bool relieEntree(float** sentiers, int point, int* types, int nbPoints, bool* visites);

int sentierMin(int& noeud, Solution &s, Exemplaire &e);

int sentierMax(float* sentiers, int nbPoints);

int trouverNoeudEnfant(Solution &s, Exemplaire &e, int noeud, std::vector<bool>& visites);

#endif
