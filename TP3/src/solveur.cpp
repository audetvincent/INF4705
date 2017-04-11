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

  // Assignation vorace des points de vue
  for (int i = 0; i < nbPoints; ++i)
  {
    if (types[i] == PT_DE_VUE)
    {
      int min = 0;
      for (int j = 1; j < nbPoints; ++j)
      {
        if (couts[i][j] < couts[i][min] && types[j] != PT_DE_VUE)
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
      int min = 0;
      for (int j = 1; j < nbPoints; ++j)
      {
        if (couts[i][j] < couts[i][min] && types[j] != PT_DE_VUE)
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
  for (int i = 0; i < nbPoints; ++i)
  {
    if (types[i] == ETAPE)
    {
      int min = couts[i][0] < couts[i][1] ? 0 : 1;
      int min_deux = min == 0 ? 1 : 0;
      for (int j = 1; j < nbPoints; ++j)
      {
        if (couts[i][j] < couts[i][min_deux] && types[j] != PT_DE_VUE)
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

  return s;
}
