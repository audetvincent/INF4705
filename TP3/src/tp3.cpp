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
  Exemplaire* e = lireFichier(argv[1]);
  
  if (e == nullptr)
  {
    std::cout << "Erreur de création du probleme" << std::endl;
    return 0;
  }
 
  Solution* s = new Solution(e->getNbPoints());

  /*s->setSentier(0, 1, 1);
  s->setSentier(0, 6, 1);
  s->setSentier(1, 2, 1);
  s->setSentier(1, 4, 1);
  s->setSentier(2, 3, 1);
  s->setSentier(3, 7, 1);
  s->setSentier(4, 8, 1);
  s->setSentier(4, 5, 1);
  s->setSentier(5, 9, 1);
  s->setSentier(5, 6, 1);
  s->setSentier(2, 4, 1);
  bool good = s->verifier(*e);
  std::cout << std::boolalpha << good << std::endl;*/

  delete e, s;
  return 0;
}
