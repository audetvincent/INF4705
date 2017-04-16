#ifndef SOLUTION_H
#define SOLUTION_H

/*
 * Classe représentant une solution du problème
 */

#include "Exemplaire.h"
#include <utility>

enum Erreur{OK, PT_DE_VUE, ENTREE, ETAPE, MAXI, LIEN};

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
  void setPrec(int depart, int arrivee);
  int getNbPoints();
  int* getNbIncidents();
  float** getSentiers();
  float getCoutTotal();
  std::pair<int, int> getPrec();
  std::pair<Erreur, int> verifier(Exemplaire& e);
  void afficher();
  float calculer();

private:
  int nbPoints;
  int* nbIncidents;
  float** sentiers;
  float coutTotal;
  std::pair<int, int> prec;
};

#endif
