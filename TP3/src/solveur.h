#ifndef SOLVEUR_H
#define SOLVEUR_H

#include "Solution.h"
#include "Exemplaire.h"
#include <vector>

Solution* trouverPremiereSolution(Exemplaire& e);

int minKey(std::vector<int> key, std::vector<bool> mstSet, int nbPoints);

void printMST(std::vector<int> parent, int n, float** graph, int nbPoints);

std::vector<int> primMST(float** graph, int nbPoints);

void amelioration(Solution &s, Exemplaire &e);

#endif
