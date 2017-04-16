#ifndef SOLVEUR_H
#define SOLVEUR_H

#include "Solution.h"
#include "Exemplaire.h"
#include <vector>

Solution* trouverPremiereSolution(Exemplaire& e);

int minKey(std::vector<float>& key, std::vector<int>& mstSet, int nbPoints);

void printMST(std::vector<int>& parent, int n, std::vector<std::vector<float> >& graph, int nbPoints);

std::vector<int> primMST(std::vector<std::vector<float> >& graph, int nbPoints);

void amelioration(Solution &s, Exemplaire &e);

#endif
