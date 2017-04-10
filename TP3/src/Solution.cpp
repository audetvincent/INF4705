#include "Solution.h"
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

bool Solution::verifier(Exemplaire& e)
{
  // 2. Chaque entrée du parc doit être le départ d'au moins un sentier
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] == ENTREE && nbIncidents[i] < 1)
    {
      return false;
    }
  }

  // 3. Les points étape doivent avoir au moins 2 sentiers incidents
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] == ETAPE && nbIncidents[i] < 2)
    {
      return false;
    }
  }

  // 4. Les points de vue ne sont accessibles que par un seul sentier
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] == PT_DE_VUE && nbIncidents[i] > 1)
    {
      return false;
    }
  }

  // 5. Chaque point d'interêt possède un nombre limité de sentiers incidents
  for (int i = 0; i < nbPoints; ++i)
  {
    if (nbIncidents[i] > e.getMaxSentiers()[i])
    {
      return false;
    }
  }
  
  // 1. Pour chaque point d'interêt, il doit exister un chemin qui le relie à une entrée du parc
  bool* visites = new bool[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    visites[i] = false;
  }
  for (int i = 0; i < nbPoints; ++i)
  {
    if (e.getTypes()[i] != ENTREE)
    {
      if (nbIncidents[i] < 1)
      {
        return false;
      }
      
      bool relie = relieEntree(sentiers, i, nbPoints, visites);
      if (!relie)
      {
        return relie;
      }
    }
  }
  delete [] visites;


  return true;
}

