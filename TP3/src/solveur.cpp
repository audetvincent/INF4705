#include "solveur.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <deque>
#include <algorithm>
#include <ctime>

// Les 3 méthodes suivantes sont adaptess de  : http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(std::vector<double>& key, std::vector<int>& mstSet, int nbPoints)
{
   // Initialize min value
    double mini = LONG_MAX;
    int min_index = 0;

    for (int v = 0; v < nbPoints; v++)
    {
        if (mstSet[v] == 0 && key[v] < mini)
        {
            mini = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void printMST(std::vector<int>& parent, int n, std::vector<std::vector<double> >& graph, int nbPoints)
{
   printf("Edge   Weight\n");
   for (int i = 1; i < nbPoints; i++)
      printf("%d - %d    %f \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
std::vector<int> primMST(std::vector<std::vector<double> >& graph, int nbPoints)
{
     std::vector<int> parent(nbPoints, 0); // Array to store constructed MST
     std::vector<double> key(nbPoints, LONG_MAX);   // Key values used to pick minimum weight edge in cut
     std::vector<int> mstSet(nbPoints, 0);  // To represent set of vertices not yet included in MST

     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST

     // The MST will have V vertices
     for (int count = 0; count < nbPoints-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet, nbPoints);

        // Add the picked vertex to the MST Set
        mstSet[u] = 1;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < nbPoints; v++)
        {
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (graph[u][v] && mstSet[v] == 0 && graph[u][v] <  key[v])
          {
            parent[v]  = u;
            key[v] = graph[u][v];
          }
        }
     }

	 return parent;
     // print the constructed MST
     //printMST(parent, nbPoints, graph, nbPoints);
}

// methode principale de d'amelioration locale
void amelioration(Solution &s, Exemplaire &e, bool afficherSol, bool afficherTmp, clock_t debut)
{
	int nbPoints = e.getNbPoints();
	std::vector<std::vector<double> > sentiers = s.getSentiers();
	std::pair<Erreur, int> valide = s.verifier(e);
	std::deque<std::pair<int, double>> arcs;
	int mini = 0, maxi = 0;
	std::vector<std::vector<double> > couts = e.getCouts();
	double meilleurCout = LONG_MAX;
	std::vector<int> maxSentiers = e.getMaxSentiers();

	s.addTabou(s.getCoutTotal());
	//s.afficher();

        // on commence par verifier si l'arbre sous-tendant minimal retourne par l'algorithme de Prim n'est pas deja une solution
	if (valide.first == OK)
	{
	  if (afficherSol)
          {
            s.afficher();
          }
          if (afficherTmp)
          {
            std::cout << "Temps de calcul jusqu'a maintenant : " << (clock() - debut) / CLOCKS_PER_SEC << " secondes" << std::endl;
          }
          meilleurCout = s.getCoutTotal();
	}

	while(1)
	{
	    sentiers = s.getSentiers();
		//std::cout << valide.first << std::endl;
		switch(valide.first) // on défini un voisinage selon le type d'erreur detecte
		{
			case PT_DE_VUE: // ce cas n'est pas utilise dans la version actuelle, MAXI est equivalent
				for (int i = 0; i < nbPoints; ++i)
				{
					double cout = sentiers[valide.second][i];
					if (cout > 0)
					{
						if (arcs.empty())
							arcs.push_back(std::pair<int, double>(i, cout));
						else if (cout < arcs[0].second)
						{
							arcs.push_front(std::pair<int, double>(i, cout));
							s.deleteSentier(valide.second, arcs.back().first);
							arcs.pop_back();
						}
						else
							s.deleteSentier(valide.second, i);
					}
				}
				arcs.clear();
				break;
			 // dans le cas d'une erreur de lien a une entree, on ajoute un sentier le 
                         // moins couteux possible au point problematique
                        case LIEN:
			      mini = sentierMin(valide.second, s, e);
		              s.setSentier(valide.second, mini, couts[valide.second][mini]);
			      //std::cout << valide.second << "-" << mini << std::endl;
                              break;
                        // si un point etape n'a pas au moins deux sentiers incidents, on lui en ajoute un de cout minimum
			case ETAPE:
			      mini = sentierMin(valide.second, s, e);
			      s.setSentier(valide.second, mini, couts[valide.second][mini]);
			       //std::cout << valide.second << "-" << mini << std::endl;
			      break;
                        // Si un point n'a aucun sentier et n'est donc pas present dans la configuration, on l'ajoute
			case ENTREE:
			      mini = sentierMin(valide.second, s, e);
			      s.setSentier(valide.second, mini, couts[valide.second][mini]);
			       //std::cout << valide.second << "-" << mini << std::endl;
			      break;
                        // si un maximum des depasse, on supprime le sentier le plus cher du point concerné
			case MAXI:
			      while (s.getNbIncidents()[valide.second] > maxSentiers[valide.second])
                              {
                                maxi = sentierMax(s, valide.second);
                                s.deleteSentier(valide.second, maxi);
                              }
			      break;
                        // dans le cas ou la solution est valide, on l'affiche si c'est la meilleure a ce point
                        case OK:
                              if (s.getCoutTotal() < meilleurCout)
                              {
                                if (afficherSol)
                                {
                                  s.afficher();
                                  //std::cout << s.getCoutTotal() << std::endl;
                                }
                                if (afficherTmp)
                                {
                                  std::cout << "Temps de calcul jusqu'a maintenant : " << (clock() - debut) / CLOCKS_PER_SEC  << " secondes" << std::endl;
                                }
                                meilleurCout = s.getCoutTotal();
                              } 
                              deletePlusCherSentier(s);
                              break;
			default:
			      break;
		}

        // on ajoute la configuration actuelle a la liste tabou et on relance la verification
        s.addTabou(s.getCoutTotal());
	valide = s.verifier(e);
        //s.afficher();
    }
}


// fonction supprimant le sentier le plus cher du point le plus connecté
void deletePlusCherSentier(Solution& s)
{
    auto nbIncidents = s.getNbIncidents();

    auto itMax = std::max_element(nbIncidents.begin(), nbIncidents.end());
    int noeud = std::distance(nbIncidents.begin(), itMax);
    int maxi = sentierMax(s, noeud);
    s.deleteSentier(noeud, maxi);
}
