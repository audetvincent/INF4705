#include "utils.h"

bool relieEntree(float** sentiers, int point, int nbPoints, bool* visites)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    if (sentiers[point][i] != 0)
    { 
      if(i == ENTREE)
      {
        return true;
      }
    }
  }

  for (int i = 0; i < nbPoints; ++i)
  {
    if (sentiers[point][i] != 0 && visites[i] == false)
    {
      visites[i] = true;
      return relieEntree(sentiers, i, nbPoints, visites);
    }
  }

  return false;
}
