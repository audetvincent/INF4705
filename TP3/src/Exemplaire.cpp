#include "Exemplaire.h"
#include <iostream>

Exemplaire::Exemplaire(int nbPoints) : nbPoints(nbPoints)
{
  types = std::vector<int>(nbPoints);

  maxSentiers = std::vector<int>(nbPoints);

  couts = std::vector<std::vector<double> >(nbPoints, std::vector<double>(nbPoints, 0));
}

Exemplaire::Exemplaire(int nbPoints, std::vector<int>& types, std::vector<int>& maxSentiers, std::vector<std::vector<double> >& couts) : nbPoints(nbPoints)
{
  this->types = std::vector<int>(types);
  this->maxSentiers = std::vector<int>(maxSentiers);
  this->couts = std::vector<std::vector<double> >(couts);
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

void Exemplaire::setCouts(std::vector<std::vector<double> >& couts)
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

std::vector<std::vector<double> > Exemplaire::getCouts()
{
  return couts;
}
