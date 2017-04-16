#include "Exemplaire.h"
#include <iostream>

Exemplaire::Exemplaire(int nbPoints) : nbPoints(nbPoints)
{
  types = std::vector<int>(nbPoints);

  maxSentiers = std::vector<int>(nbPoints);

  couts = std::vector<std::vector<float> >(nbPoints, std::vector<float>(nbPoints, 0));
}

Exemplaire::Exemplaire(int nbPoints, std::vector<int>& types, std::vector<int>& maxSentiers, std::vector<std::vector<float> >& couts) : nbPoints(nbPoints)
{
  this->types = std::vector<int>(nbPoints);
  setTypes(types);

  this->maxSentiers = std::vector<int>(nbPoints);
  setMaxSentiers(maxSentiers);

  couts = std::vector<std::vector<float> >(nbPoints, std::vector<float>(nbPoints, 0));
  setCouts(couts);
}

Exemplaire::~Exemplaire()
{
}

void Exemplaire::setNbPoints(int nbPoints)
{
  this->nbPoints = nbPoints;
}

void Exemplaire::setTypes(std::vector<int>& types)
{
  this->types = types;
}

void Exemplaire::setMaxSentiers(std::vector<int>& maxSentiers)
{
  this->maxSentiers = maxSentiers;
}

void Exemplaire::setCouts(std::vector<std::vector<float> >& couts)
{
  this->couts = couts;
}

int Exemplaire::getNbPoints()
{
  return nbPoints;
}

std::vector<int> Exemplaire::getTypes()
{
  return types;
}

std::vector<int> Exemplaire::getMaxSentiers()
{
  return maxSentiers;
}

std::vector<std::vector<float> > Exemplaire::getCouts()
{
  return couts;
}
