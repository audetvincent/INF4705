#include "Exemplaire.h"
#include <iostream>

Exemplaire::Exemplaire(int nbPoints) : nbPoints(nbPoints)
{
  types = new int[nbPoints];

  maxSentiers = new int[nbPoints];

  couts = new float*[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    couts[i] = new float[nbPoints];
  }
}

Exemplaire::Exemplaire(int nbPoints, int* types, int* maxSentiers, float** couts) : nbPoints(nbPoints)
{
  this->types = new int[nbPoints];
  setTypes(types);
  
  this->maxSentiers = new int[nbPoints];
  setMaxSentiers(maxSentiers);

  this->couts = new float*[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    this->couts[i] = new float[nbPoints];
  }
  setCouts(couts);
}

Exemplaire::~Exemplaire()
{
  for (int i = 0; i < nbPoints; ++i)
  {
    delete [] couts[i];
  }
  delete [] couts;

  delete [] types;

  delete [] maxSentiers;
}

void Exemplaire::setNbPoints(int nbPoints)
{
  this->nbPoints = nbPoints;
}

void Exemplaire::setTypes(int* types)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    this->types[i] = types[i];
  }
}

void Exemplaire::setMaxSentiers(int* maxSentiers)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    this->maxSentiers[i] = maxSentiers[i];
  }
}

void Exemplaire::setCouts(float** couts)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    for (int j = 0; j < nbPoints; ++j)
    {
      this->couts[i][j] = couts[i][j];
    }
  }
}

int Exemplaire::getNbPoints()
{
  return nbPoints;
}

int* Exemplaire::getTypes()
{
  return types;
}

int* Exemplaire::getMaxSentiers()
{
  return maxSentiers;
}

float** Exemplaire::getCouts()
{
  return couts;
}
