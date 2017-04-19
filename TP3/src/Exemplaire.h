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
  int nbPoints; // nombre de points dans le parc
  std::vector<int> types; // vecteur indiquant le type de chaque point
  std::vector<int> maxSentiers; // vecteur indiquant pour chaque point son maximum de sentiers incidents autorise
  std::vector<std::vector<double> > couts; // matrice des couts entre chaque point
};

#endif
