/*
 * Idée : 1) trouver une première solution à la façon DSATUR (plus grand minimum en 1er, point avec la plus grandre différence entre les deux plus petites valeurs...)
 * 	  2) metaheuristique voisinage variable avec un voisinage par coeur
 */

#include "Solution.h"
#include "Exemplaire.h"
#include <iostream>
#include "utils.h"
#include "solveur.h"

int main(int argc, char* argv[])
{
  bool afficher = false;
  bool temps = false;
  if (argc == 4)
  {
    afficher = true;
    temps = true;
  }
  else if (argc == 3)
  {
    if (argv[2] == "-p")
    {
      afficher = true;
    }
    else if (argv[2] == "-t")
    {
      temps = true;
    }
  }

  Exemplaire* e = lireFichier(argv[1]);

  if (e == nullptr)
  {
    std::cout << "Erreur de création du probleme" << std::endl;
    return 0;
  }

  std::vector<std::vector<float> > couts = e->getCouts();
  int nbPoints = e->getNbPoints();
  std::vector<int> parent = primMST(couts, nbPoints);

  Solution* s = new Solution(e->getNbPoints());

  for (int i = 1; i < e->getNbPoints(); i++)
    s->setSentier(parent[i], i, e->getCouts()[i][parent[i]]);

	amelioration(*s, *e);

  delete e, s;

  return 0;
}
