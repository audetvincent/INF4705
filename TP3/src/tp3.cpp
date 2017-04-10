/*
 * Idée : 1) trouver une première solution à la façon DSATUR (plus grand minimum en 1er, point avec la plus grandre différence entre les deux plus petites valeurs...)
 * 	  2) metaheuristique voisinage variable avec un voisinage par coeur
 */

#include "Solution.h"
#include "Exemplaire.h"
#include <string>
#include <iostream>
#include <fstream>

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

int main(int argc, char* argv[])
{
  Exemplaire* p = lireFichier(argv[1]);
  
  if (p == nullptr)
  {
    std::cout << "Erreur de création du probleme" << std::endl;
    return 0;
  }
  
  delete p;
  return 0;
}
