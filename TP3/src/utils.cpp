#include "utils.h"
#include <iostream>

Exemplaire* lireFichier(std::string nom)
{
  std::ifstream fichier(nom, std::ios::in);

  if(fichier)
  {
    int nbPoints;
    std::vector<int> types;
    std::vector<int> maxSentiers;
    std::vector<std::vector<float> > couts;

    fichier >> nbPoints;

    types = std::vector<int>(nbPoints);
    for (int i = 0; i < nbPoints; ++i)
    {
      fichier >> types[i];
    }

    maxSentiers = std::vector<int>(nbPoints);
    for (int i = 0; i < nbPoints; ++i)
    {
      fichier >> maxSentiers[i];
    }

    couts = std::vector<std::vector<float> >(nbPoints, std::vector<float>(nbPoints, 0));
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

    fichier.close();

    return p;
  }

  else
  {
    std::cout << "Erreur lors de l'ouverture du fichier " << nom << std::endl;
    return nullptr;
  }
}


bool relieEntree(std::vector<std::vector<float> >& sentiers, int point, std::vector<int>& types, int nbPoints, std::vector<int>& visites)
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
    if (sentiers[point][i] != 0 && visites[i] == 0)
    {
      visites[i] = 1;
      if (relieEntree(sentiers, i, types, nbPoints, visites))
        return true;
    }
  }

  return false;
}


int trouverNoeudEnfant(Solution &s, Exemplaire &e, int noeud, std::vector<int>& visites)
{
    int nbPoints = e.getNbPoints();
	std::vector<std::vector<float> > sentiers = s.getSentiers();
	std::vector<int> nbSentiers = s.getNbIncidents();
	std::vector<int> maxSentiers = e.getMaxSentiers();
	std::vector<int> types = e.getTypes();

    for(int i = 0; i < nbPoints; ++i)
	{
		if(sentiers[noeud][i] > 0 && nbSentiers[i] < maxSentiers[i] && visites[i] == 0)
			return i;
	}
	for(int i = 0; i < nbPoints; ++i)
	{
		if(sentiers[noeud][i] > 0 && types[i] != PT_DE_VUE && visites[i] == 0)
        {
            visites[i] = 1;
            return trouverNoeudEnfant(s, e, i, visites);
        }
	}

	return nbPoints;
}

int sentierMin(int& noeud, Solution &s, Exemplaire &e)
{
	int nbPoints = e.getNbPoints();
	int mini = nbPoints, miniCout = 0, noeudEnfant;
	float coutMin = LONG_MAX;
	std::vector<std::vector<float> > couts = e.getCouts();
	std::vector<std::vector<float> > sentiers = s.getSentiers();
	std::vector<int> nbSentiers = s.getNbIncidents();
	std::vector<int> maxSentiers = e.getMaxSentiers();
	std::vector<int> types = e.getTypes();
	std::pair<int, int> prec = s.getPrec();

	std::vector<int> visites(nbPoints, false);
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

int sentierMax(Solution& s, int noeud)
{
    int nbPoints = s.getNbPoints();
	std::vector<std::vector<float> > sentiers = s.getSentiers();
	std::pair<int, int> prec = s.getPrec();

	int maxi = 0;
	float coutMax = 0;
	for (int i = 0; i < nbPoints; ++i)
	{
		if ((sentiers[noeud][i] > coutMax) &&
            !((noeud == prec.first && i == prec.second) || (noeud == prec.second && i == prec.first)))
        {
            coutMax = sentiers[noeud][i];
			maxi = i;
        }
	}

    s.setPrec(noeud, maxi);
	return maxi;
}

