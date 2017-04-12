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
  void setNbPoints(int nbPoints);
  void setNbIncidents(int* nbIncidents);
  void setSentier(int depart, int arrivee, float cout);
  void setSentiers(float** sentiers);
  void deleteSentier(int depart, int arrivee);
  int getNbPoints();
  int* getNbIncidents();
  float** getSentiers(); 
  float getCoutTotal();
  bool verifier(Exemplaire& e);
  void afficher();
  float calculer();

private:
  int nbPoints;
  int* nbIncidents;
  float** sentiers;
  float coutTotal;
};

#endif
