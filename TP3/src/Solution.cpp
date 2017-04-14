#include "Solution.h"
#include <iostream>
#include "utils.h"

Solution::Solution(int nbPoints) : nbPoints(nbPoints)
{
  sentiers = new float*[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    sentiers[i] = new float[nbPoints];
  }
  nbIncidents = new int[nbPoints];

  for (int i = 0; i < nbPoints; ++i)
  {
    for (int j = 0; j < nbPoints; ++j)
    {
      sentiers[i][j] = 0;
    }
    nbIncidents[i] = 0;
  }

  coutTotal = 0;
}

Solution::~Solution()
{
  for (int i = 0; i < nbPoints; ++i)
  {
    delete [] sentiers[i];
  }
  delete [] sentiers;
  delete [] nbIncidents;
}

void Solution::setNbPoints(int nbPoints)
{
  this->nbPoints = nbPoints;
}

void Solution::setNbIncidents(int* nbIncidents)
{
  this->nbIncidents = nbIncidents;
}

void Solution::setSentier(int depart, int arrivee, float cout)
{
  sentiers[depart][arrivee] = cout;
  nbIncidents[depart]++;
  sentiers[arrivee][depart] = cout;
  nbIncidents[arrivee]++;
  
  coutTotal += cout;
}

void Solution::deleteSentier(int depart, int arrivee)
{
  float cout = sentiers[depart][arrivee];
  sentiers[depart][arrivee] = 0;
  nbIncidents[depart]--;
  sentiers[arrivee][depart] = 0;
  nbIncidents[arrivee]--;
  
  coutTotal -= cout;
}

void Solution::setSentiers(float** sentiers)
{
  this->sentiers = sentiers;
}

int Solution::getNbPoints()
{
  return nbPoints;
}

int* Solution::getNbIncidents()
{
  return nbIncidents;
}
              
float** Solution::getSentiers()
{
  return sentiers;
}

float Solution::getCoutTotal()
{
  return coutTotal;
}

std::pair<Erreur, int> Solution::verifier(Exemplaire& e)
{
  // 4. Les points de vue ne sont accessibles que par un seul sentier
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] == PT_DE_VUE && nbIncidents[i] > 1)
    {
      return std::pair<Erreur, int>(PT_DE_VUE, i);
    }
  }
  
  // 1. Pour chaque point d'interêt, il doit exister un chemin qui le relie à une entrée du parc
  bool* visites = new bool[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] != ENTREE)
    {
      if (nbIncidents[i] < 1)
      {
        return std::pair<Erreur, int>(LIEN, i);
      }
      for (int i = 0; i < nbPoints; ++i)
      {
        visites[i] = false;
      }
      bool relie = relieEntree(sentiers, i, nbPoints, visites);
      if (!relie)
      {
        return std::pair<Erreur, int>(LIEN, i);
      }
    }
  }
  delete [] visites;

  // 2. Chaque entrée du parc doit être le départ d'au moins un sentier
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] == ENTREE && nbIncidents[i] < 1)
    {
      return std::pair<Erreur, int>(ENTREE, i);
    }
  }

  // 3. Les points étape doivent avoir au moins 2 sentiers incidents
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] == ETAPE && nbIncidents[i] < 2)
    {
      return std::pair<Erreur, int>(ETAPE, i);
    }
  }

  // 5. Chaque point d'interêt possède un nombre limité de sentiers incidents
  for (int i = 0; i < nbPoints; ++i)
  {
    if (nbIncidents[i] > e.getMaxSentiers()[i])
    {
      return std::pair<Erreur, int>(MAXI, i);
    }
  }

  return std::pair<Erreur, int>(OK, 0);
}

void Solution::afficher()
{
  for (int i = 0; i < nbPoints; ++i)
  {
    for (int j = 0; j < i; ++j)
    {
      if (sentiers[i][j] != 0)
      {
        std::cout << i << " " << j << std::endl;
      }
    }
  }

  std::cout << "fin" << std::endl;
}

float Solution::calculer()
{
  coutTotal = 0;
  for (int i = 0; i < nbPoints; ++i)
  {
    for (int j = 0; j < i; ++j)
    {
      coutTotal += sentiers[i][j];
    }
  }

  return coutTotal;
}
