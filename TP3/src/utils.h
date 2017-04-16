#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include "Exemplaire.h"
#include "Solution.h"
#include <limits.h>
#include <vector>

Exemplaire* lireFichier(std::string nom);

bool relieEntree(std::vector<std::vector<float> >& sentiers, int point, std::vector<int>& types, int nbPoints, std::vector<int>& visites);

int sentierMin(int& noeud, Solution &s, Exemplaire &e);

int sentierMax(Solution& s, int noeud);

int trouverNoeudEnfant(Solution &s, Exemplaire &e, int noeud, std::vector<int>& visites);

#endif
