#ifndef SOLUTION_H
#define SOLUTION_H

/*
 * Classe représentant une solution du problème
 */

#include "Exemplaire.h"
#include <utility>
#include <deque>

enum Erreur{OK, PT_DE_VUE, ENTREE, ETAPE, MAXI, LIEN};

class Solution
{
public:
  Solution(int nbPoints);
  ~Solution();
  void setNbPoints(int nbPoints);
  void setNbIncidents(std::vector<int>& nbIncidents);
  void setSentier(int depart, int arrivee, float cout);
  void setSentiers(std::vector<std::vector<float> >& sentiers);
  void deleteSentier(int depart, int arrivee);
  void addTabou(float coutTotal);
  int getNbPoints();
  std::vector<int> getNbIncidents();
  std::vector<std::vector<float> > getSentiers();
  float getCoutTotal();
  std::deque<float> getTabou();
  std::pair<Erreur, int> verifier(Exemplaire& e);
  void afficher();
  float calculer();
  bool estTabou(float coutTotal);

private:
  int nbPoints;
  std::vector<int> nbIncidents;
  std::vector<std::vector<float> > sentiers;
  float coutTotal;
  std::deque<float> tabou;
};

#endif
