#include "Probleme.h"
#include <iostream>

Probleme::Probleme(int nbPoints) : nbPoints(nbPoints)
{
  types = new int[nbPoints];

  maxSentiers = new int[nbPoints];

  couts = new float*[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    couts[i] = new float[nbPoints];
  }
}

Probleme::Probleme(int nbPoints, int* types, int* maxSentiers, float** couts) : nbPoints(nbPoints)
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

Probleme::~Probleme()
{
  for (int i = 0; i < nbPoints; ++i)
  {
    delete [] couts[i];
  }
  delete [] couts;

  delete [] types;

  delete [] maxSentiers;
}

void Probleme::setNbPoints(int nbPoints)
{
  this->nbPoints = nbPoints;
}

void Probleme::setTypes(int* types)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    this->types[i] = types[i];
  }
}

void Probleme::setMaxSentiers(int* maxSentiers)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    this->maxSentiers[i] = maxSentiers[i];
  }
}

void Probleme::setCouts(float** couts)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    for (int j = 0; j < nbPoints; ++j)
    {
      this->couts[i][j] = couts[i][j];
    }
  }
}

int Probleme::getNbPoints()
{
  return nbPoints;
}

int* Probleme::getTypes()
{
  return types;
}

int* Probleme::getMaxSentiers()
{
  return maxSentiers;
}

float** Probleme::getCouts()
{
  return couts;
}
