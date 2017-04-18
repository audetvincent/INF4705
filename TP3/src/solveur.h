#ifndef SOLVEUR_H
#define SOLVEUR_H

#include "Solution.h"
#include "Exemplaire.h"
#include <vector>
#include <ctime>

Solution* trouverPremiereSolution(Exemplaire& e);

int minKey(std::vector<double>& key, std::vector<int>& mstSet, int nbPoints);

void printMST(std::vector<int>& parent, int n, std::vector<std::vector<double> >& graph, int nbPoints);

std::vector<int> primMST(std::vector<std::vector<double> >& graph, int nbPoints);

void amelioration(Solution &s, Exemplaire &e, bool afficherSol, bool afficherTmp, clock_t debut);

void deletePlusCherSentier(Solution& s);

#endif
