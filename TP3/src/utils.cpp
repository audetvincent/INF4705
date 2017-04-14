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

		// Deux points de vue ne peuvent pas etre lies
		for (int i = 0; i < nbPoints; ++i)
    {
    	if (types[i] == PT_DE_VUE)
    	{
		    for (int j = 0; j < nbPoints; ++j)
		    {	
		      if (types[j] == PT_DE_VUE)
		      {
		      	couts[i][j] = 0;
		      }     
		    }
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

int sentierMin(int noeud, Solution &s, Exemplaire &e)
{
	int nbPoints = e.getNbPoints();
	int coutMin = INT_MAX, min = 0;
	float** couts = e.getCouts();
	float** sentiers = s.getSentiers();
	int* nbIncidents = s.getNbIncidents();
	int* maxSentiers = e.getMaxSentiers();
	
	int i = 0;
	int noeudEnfant = noeud;
	//std::cout << nbIncidents[noeudEnfant] << std::endl;
	while(nbIncidents[noeudEnfant] >= maxSentiers[noeudEnfant])
	{
		if(sentiers[noeudEnfant][i] > 0)
			noeudEnfant = i;
		i++;
		if (i > 9)
		{
			std::cout << "FATAL ERROR HEHEHE" << std::endl;
			exit(0);
		}
	}
	noeud = noeudEnfant;
		
	for (int i = 0; i < nbPoints; ++i)
	{
		if (couts[noeud][i] > 0 && couts[noeud][i] < coutMin 
				&& sentiers[noeud][i] == 0 && nbIncidents[i] < maxSentiers[i])
			min = i;
	}
	
	return min;
}

int sentierMax(float* sentiers, int nbPoints)
{
	int coutMax = 0, max = 0;
	for (int i = 0; i < nbPoints; ++i)
	{
		if (sentiers[i] > coutMax)
			max = i;
	}
	
	return max;
}

