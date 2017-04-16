#include "solveur.h"
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <deque>

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
    int min_index;

    for (int v = 0; v < nbPoints; v++)
    {
        if (mstSet[v] == 0 && key[v] < mini)
        {
            mini = key[v], min_index = v;
            std::cout << min_index << std::endl;
        }
    }

    return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void printMST(std::vector<int>& parent, int n, std::vector<std::vector<float> >& graph, int nbPoints)
{
   printf("Edge   Weight\n");
   for (int i = 1; i < nbPoints; i++)
      printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
std::vector<int> primMST(std::vector<std::vector<float> >& graph, int nbPoints)
{
     std::vector<int> parent(nbPoints, 0); // Array to store constructed MST
     std::vector<float> key(nbPoints, LONG_MAX);   // Key values used to pick minimum weight edge in cut
     std::vector<int> mstSet(nbPoints);  // To represent set of vertices not yet included in MST

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

           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (graph[u][v] && mstSet[v] == 0 && graph[u][v] <  key[v])
             parent[v]  = u, key[v] = graph[u][v];
     }

	 return parent;
     // print the constructed MST
     //printMST(parent, nbPoints, graph, nbPoints);
}

void amelioration(Solution &s, Exemplaire &e)
{
	int nbPoints = e.getNbPoints();
	std::vector<std::vector<float> > sentiers = s.getSentiers();
	std::pair<Erreur, int> valide = s.verifier(e);
	std::deque<std::pair<int, float>> arcs;
	int mini = 0, maxi = 0;
	std::vector<std::vector<float> > couts = e.getCouts();

	if (valide.first == OK)
	{
		s.afficher();
	}

	while(1)
	{
		std::cout << valide.first << std::endl;
        s.afficher();
		switch(valide.first)
		{
			// TODO : CONTRAINTES
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

				std::cout << valide.second << "-" << mini << std::endl;
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
				maxi = sentierMax(s, valide.second);
				s.deleteSentier(valide.second, maxi);
				break;
			default:
				break;
		}

		//s.afficher();

		valide = s.verifier(e);
		if (valide.first == OK)
		{
			s.afficher();
			s.verifier(e);
			exit(0);
		}
	}
}
