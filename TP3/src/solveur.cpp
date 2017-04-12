#include "solveur.h"
#include "utils.h"
#include <iostream>

Solution* trouverPremiereSolution(Exemplaire& e)
{
  int nbPoints = e.getNbPoints();
  int* types = e.getTypes();
  int* maxSentiers = e.getMaxSentiers();
  float** couts = e.getCouts();
  Solution* s = new Solution(nbPoints);
  int* nbIncidents = s->getNbIncidents();
  float** sentiers = s->getSentiers();

  // Assignation vorace des points de vue
  for (int i = 0; i < nbPoints; ++i)
  {
    if (types[i] == PT_DE_VUE)
    {
      int min = i == 0 ? 1 : 0;
      for (int j = 0; j < nbPoints; ++j)
      {
        if (i != j && couts[i][j] < couts[i][min] && types[j] != PT_DE_VUE && sentiers[i][j] == 0)
        {
          min = j; 
        }
      }

      s->setSentier(i, min, couts[i][min]);
    }
  }
  
  // Assignation vorace des entrees en fonction des assignations precedentes
  for (int i = 0; i < nbPoints; ++i)
  {
    if (types[i] == ENTREE)
    {
      int min = i == 0 ? 1 : 0;
      for (int j = 0; j < nbPoints; ++j)
      {
        if (i != j && couts[i][j] < couts[i][min] && types[j] != PT_DE_VUE && sentiers[i][j] == 0)
        {
          min = j; 
        }
      }

      if (nbIncidents[i] < maxSentiers[i] && nbIncidents[min] < maxSentiers[min]) 
      {
        s->setSentier(i, min, couts[i][min]);
      }
    }
  }
  
  // Assignation vorace des etapes en fonction des assignations precedentes
  bool* visites = new bool[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    if (types[i] == ETAPE)
    {
      for (int j = 0; j < nbPoints; ++j)
      {
        visites[j] = false;
      }
      visites[i] = true;
      while (nbIncidents[i] < 2)
      {
        int min = i != 0 ? (couts[i][0] < couts[i][1] ? 0 : 1) : (couts[i][1] < couts[i][2] ? 1 : 2);
        int min_deux = i != 0 ? (min == 0 ? 1 : 0) : (min == 1 ? 2 : 1);
        for (int j = 0; j < nbPoints; ++j)
        {
          if (visites[j] == false)
          {
            if (i != j && couts[i][j] < couts[i][min_deux] && types[j] != PT_DE_VUE && sentiers[i][j] == 0)
            {  
              if (couts[i][j] < couts[i][min])
              {
                min_deux = min;
                min = j;
              }
              else
              {
                min_deux = j;
              }
            }
          }
        }
    
        visites[min] = true;
        visites[min_deux] = true;
        if (nbIncidents[i] < maxSentiers[i] && nbIncidents[min] < maxSentiers[min]) 
        {
          s->setSentier(i, min, couts[i][min]);
        }
        if (nbIncidents[i] < maxSentiers[i] && nbIncidents[min_deux] < maxSentiers[min_deux]) 
        {
          s->setSentier(i, min_deux, couts[i][min_deux]);
        }
      }
    }
  }

  return s;
}
