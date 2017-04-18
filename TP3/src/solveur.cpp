#include "solveur.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <deque>
#include <algorithm>
#include <ctime>

/*Solution* trouverPremiereSolution(Exemplaire& e)
{
  int nbPoints = e.getNbPoints();
  std::vector<int> types = e.getTypes();
  std::vector<int> maxSentiers = e.getMaxSentiers();
  std::vector<std::vector<float> > couts = e.getCouts();
  Solution* s = new Solution(nbPoints);
  std::vector<int> nbIncidents = s->getNbIncidents();
  std::vector<std::vector<float> > sentiers = s->getSentiers();

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
  std::vector<int> visites = new bool[nbPoints];
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
        int min;
        int min_deux;
        if (i == 0)
        {
          min = couts[i][1] < couts[i][2] ? 1 : 2;
          min_deux = min == 1 ? 2 : 1;
        }
        else if (i == 1)
        {
          min = couts[i][0] < couts[i][2] ? 0 : 2;
          min_deux = min == 0 ? 3 : 0;
        }
        else
        {
          min = couts[i][0] < couts[i][1] ? 0 : 1;
          min_deux = min == 0 ? 1 : 0;
        }

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
}*/

// From  : http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(std::vector<float>& key, std::vector<int>& mstSet, int nbPoints)
{
   // Initialize min value
    float mini = LONG_MAX;
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
void printMST(std::vector<int>& parent, int n, std::vector<std::vector<float> >& graph, int nbPoints)
{
   printf("Edge   Weight\n");
   for (int i = 1; i < nbPoints; i++)
      printf("%d - %d    %f \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
std::vector<int> primMST(std::vector<std::vector<float> >& graph, int nbPoints)
{
     std::vector<int> parent(nbPoints, 0); // Array to store constructed MST
     std::vector<float> key(nbPoints, LONG_MAX);   // Key values used to pick minimum weight edge in cut
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

void amelioration(Solution &s, Exemplaire &e, bool afficherSol, bool afficherTmp, clock_t debut)
{
	int nbPoints = e.getNbPoints();
	std::vector<std::vector<float> > sentiers = s.getSentiers();
	std::pair<Erreur, int> valide = s.verifier(e);
	std::deque<std::pair<int, float>> arcs;
	int mini = 0, maxi = 0;
	std::vector<std::vector<float> > couts = e.getCouts();
	float meilleurCout = LONG_MAX;
	std::vector<int> maxSentiers = e.getMaxSentiers();

	s.addTabou(s.getCoutTotal());
	//s.afficher();

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
		switch(valide.first)
		{
			case PT_DE_VUE:
				for (int i = 0; i < nbPoints; ++i)
				{
					float cout = sentiers[valide.second][i];
					if (cout > 0)
					{
						if (arcs.empty())
							arcs.push_back(std::pair<int, float>(i, cout));
						else if (cout < arcs[0].second)
						{
							arcs.push_front(std::pair<int, float>(i, cout));
							s.deleteSentier(valide.second, arcs.back().first);
							arcs.pop_back();
						}
						else
							s.deleteSentier(valide.second, i);
					}
				}
				arcs.clear();
				break;
			case LIEN:
				mini = sentierMin(valide.second, s, e);
				s.setSentier(valide.second, mini, couts[valide.second][mini]);

				//std::cout << valide.second << "-" << mini << std::endl;
				break;
			case ETAPE:
				mini = sentierMin(valide.second, s, e);
				s.setSentier(valide.second, mini, couts[valide.second][mini]);
				break;
			case ENTREE:
				mini = sentierMin(valide.second, s, e);
				s.setSentier(valide.second, mini, couts[valide.second][mini]);
				break;
			case MAXI:
			    while (s.getNbIncidents()[valide.second] > maxSentiers[valide.second])
                {
                    maxi = sentierMax(s, valide.second);
                    s.deleteSentier(valide.second, maxi);
                }
				break;
            case OK:
                if (s.getCoutTotal() < meilleurCout)
                {
                    if (afficherSol)
                    {
                        s.afficher();
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


        s.addTabou(s.getCoutTotal());
		//s.afficher();

		valide = s.verifier(e);
	}
}

void deletePlusCherSentier(Solution& s)
{
    auto sentiers = s.getSentiers();
    int i = 0, j = 0;
    float mini = INT_MAX;
    std::vector<float>::iterator itMini;

    auto itExt = sentiers.begin();
    while(itExt != sentiers.end())
    {
        itMini = std::max_element(itExt->begin(), itExt->end());
        if (*itMini < mini)
        {
            i = std::distance(sentiers.begin(), itExt);
            j = std::distance(itExt->begin(), itMini);
            mini = *itMini;
        }
        ++itExt;
    }

    s.deleteSentier(i, j);
}
