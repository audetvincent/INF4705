#include "utils.h"
#include <iostream>

Exemplaire* lireFichier(std::string nom)
{
  std::ifstream fichier(nom, std::ios::in);

  if(fichier)
  {
    int nbPoints;
    int* types;
    int* maxSentiers;
    float** couts;

    fichier >> nbPoints;
    
    types = new int[nbPoints]; 
    for (int i = 0; i < nbPoints; ++i)
    {
      fichier >> types[i];
    }

    maxSentiers = new int[nbPoints];
    for (int i = 0; i < nbPoints; ++i)
    {
      fichier >> maxSentiers[i];
    }
    
    couts = new float*[nbPoints];
    for (int i = 0; i < nbPoints; ++i)
    {
      couts[i] = new float[nbPoints];
    }
    for (int i = 0; i < nbPoints; ++i)
    {
      for (int j = 0; j < nbPoints; ++j)
      {
        fichier >> couts[i][j];
      }
    }

    Exemplaire* p = new Exemplaire(nbPoints, types, maxSentiers, couts);
   
    for (int i = 0; i < nbPoints; ++i)
    {
      delete [] couts[i];
    }
    delete [] couts;
    delete [] maxSentiers;
    delete [] types;
    fichier.close();

    return p;
  }
  
  else
  {
    std::cout << "Erreur lors de l'ouverture du fichier " << nom << std::endl;
    return nullptr;
  }
}


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
