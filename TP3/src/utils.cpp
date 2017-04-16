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
        // Deux points de vue ne peuvent pas etre lies
        if (types[i] == PT_DE_VUE && types[j] == PT_DE_VUE)
            couts[i][j] = 0;
        else if (types[i] == ENTREE && types[j] == ENTREE)  // Connecter deux entree serait penalisant
            couts[i][j] = 0;
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


bool relieEntree(float** sentiers, int point, int* types, int nbPoints, bool* visites)
{
  for (int i = 0; i < nbPoints; ++i)
  {
    if (sentiers[point][i] != 0)
    {
      if(types[i] == ENTREE)
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
      if (relieEntree(sentiers, i, types, nbPoints, visites))
        return true;
    }
  }

  return false;
}


int trouverNoeudEnfant(Solution &s, Exemplaire &e, int noeud, std::vector<bool>& visites)
{
    int nbPoints = e.getNbPoints();
	float** sentiers = s.getSentiers();
	int* nbSentiers = s.getNbIncidents();
	int* maxSentiers = e.getMaxSentiers();
	int* types = e.getTypes();

    for(int i = 0; i < nbPoints; ++i)
	{
		if(sentiers[noeud][i] > 0 && nbSentiers[i] < maxSentiers[i] && visites[i] == false)
			return i;
	}
	for(int i = 0; i < nbPoints; ++i)
	{
		if(sentiers[noeud][i] > 0 && types[i] != PT_DE_VUE && visites[i] == false)
        {
            visites[i] = true;
            return trouverNoeudEnfant(s, e, i, visites);
        }
	}

	return nbPoints;
}

int sentierMin(int& noeud, Solution &s, Exemplaire &e)
{
	int nbPoints = e.getNbPoints();
	int coutMin = INT_MAX, mini = nbPoints, miniCout = 0, noeudEnfant;
	float** couts = e.getCouts();
	float** sentiers = s.getSentiers();
	int* nbSentiers = s.getNbIncidents();
	int* maxSentiers = e.getMaxSentiers();
	int* types = e.getTypes();
	std::pair<int, int> prec = s.getPrec();

	std::vector<bool> visites(nbPoints, false);
	visites[noeud] = true;
	if (nbSentiers[noeud] >= maxSentiers[noeud])
    {
        noeudEnfant = trouverNoeudEnfant(s, e, noeud, visites);
        if (noeudEnfant != nbPoints)
            noeud = noeudEnfant;
    }

	for (int i = 0; i < nbPoints; ++i)
	{
		if (couts[noeud][i] > 0 && couts[noeud][i] < coutMin
				&& sentiers[noeud][i] == 0)
        {
            if (types[i] != PT_DE_VUE)
                miniCout = i;
            if(nbSentiers[i] < maxSentiers[i])
            {
                mini = i;
            }
            coutMin = couts[noeud][i];
		}
	}

	if ((mini == nbPoints) ||
        (noeud == prec.first && mini == prec.second) ||
        (noeud == prec.second && mini == prec.first))
    {
        s.setPrec(noeud, miniCout);
        return miniCout;
    }
    s.setPrec(noeud, mini);
	return mini;
}

int sentierMax(float* sentiers, int nbPoints)
{
	int coutMax = 0, maxi = 0;
	for (int i = 0; i < nbPoints; ++i)
	{
		if (sentiers[i] > coutMax)
        {
            coutMax = sentiers[i];
			maxi = i;
        }
	}

	return maxi;
}

