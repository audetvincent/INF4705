#ifndef SOLUTION_H
#define SOLUTION_H

/*
 * Classe représentant une solution du problème
 */

#include "Exemplaire.h"

class Solution 
{
public:
  Solution(int nbPoints);
  ~Solution();
  bool verifier(Exemplaire& e);

private:
  int nbPoints;
  int* nbIncidents;
  float** sentiers;
};

#endif
