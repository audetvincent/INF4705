#ifndef EXEMPLAIRE_H
#define EXEMPLAIRE_H

/*
 * Classe représentant un exemplaire du problème
 */

#include <vector>

class Exemplaire
{
public:
  Exemplaire(int nbPoints);
  Exemplaire(int nbPoints, std::vector<int>& types, std::vector<int>& maxSentiers, std::vector<std::vector<double> >& couts);
  ~Exemplaire();
  void setNbPoints(int nbPoints);
  void setTypes(std::vector<int>& types);
  void setMaxSentiers(std::vector<int>& maxSentiers);
  void setCouts(std::vector<std::vector<double> >& couts);
  int getNbPoints();
  std::vector<int> getTypes();
  std::vector<int> getMaxSentiers();
  std::vector<std::vector<double> > getCouts();

private:
  int nbPoints;
  std::vector<int> types;
  std::vector<int> maxSentiers;
  std::vector<std::vector<double> > couts;
};

#endif
