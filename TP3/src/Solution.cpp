#include "Solution.h"
#include <iostream>
#include "utils.h"
#include <algorithm>

Solution::Solution(int nbPoints) : nbPoints(nbPoints)
{
    sentiers = std::vector<std::vector<int> >(nbPoints, std::vector<int>(nbPoints, 0));

    nbIncidents = std::vector<int>(nbPoints, 0);

    coutTotal = 0;
}

Solution::~Solution()
{
}

void Solution::setNbPoints(int nbPoints)
{
    this->nbPoints = nbPoints;
}

void Solution::setNbIncidents(std::vector<int>& nbIncidents)
{
    this->nbIncidents = nbIncidents;
}

// Methode pour ajouter un sentier a la configuration courante
void Solution::setSentier(int depart, int arrivee, int cout)
{
    sentiers[depart][arrivee] = cout;
    nbIncidents[depart]++;
    sentiers[arrivee][depart] = cout;
    nbIncidents[arrivee]++;

    coutTotal += cout;
}

// methode pour retirer un sentier de la configuration courante
void Solution::deleteSentier(int depart, int arrivee)
{
    int cout = sentiers[depart][arrivee];
    sentiers[depart][arrivee] = 0;
    nbIncidents[depart]--;
    sentiers[arrivee][depart] = 0;
    nbIncidents[arrivee]--;

    coutTotal -= cout;
}

void Solution::addTabou(int coutTotal)
{
    tabou.push_back(coutTotal);
    /*if (tabou.size() > 30000)
    {
        tabou.pop_front();
    }*/
}

void Solution::setSentiers(std::vector<std::vector<int> >& sentiers)
{
    this->sentiers = sentiers;
}

int Solution::getNbPoints()
{
    return nbPoints;
}

std::vector<int> Solution::getNbIncidents()
{
    return nbIncidents;
}

std::vector<std::vector<int> > Solution::getSentiers()
{
    return sentiers;
}

int Solution::getCoutTotal()
{
    return coutTotal;
}

std::deque<int> Solution::getTabou()
{
    return tabou;
}

// methode de verification de la solution courante par rapport aux contraintes a respecter
std::pair<Erreur, int> Solution::verifier(Exemplaire& e)
{
    // 2. Chaque point doit etre present (Chaque entrée du parc doit être le départ d'au moins un sentier)
    for (int i = 0; i < nbPoints; ++i)
    {
        if (nbIncidents[i] < 1)
        {
            return std::pair<Erreur, int>(ENTREE, i);
        }
    }

    /*// 4. Les points de vue ne sont accessibles que par un seul sentier
    for (int i = 0; i < nbPoints; ++i)
    {
      if (e.getTypes()[i] == PT_DE_VUE && nbIncidents[i] > 1)
      {
        return std::pair<Erreur, int>(PT_DE_VUE, i);
      }
    }*/

    // 5. Chaque point d'interêt possède un nombre limité de sentiers incidents
    for (int i = 0; i < nbPoints; ++i)
    {
        if (nbIncidents[i] > e.getMaxSentiers()[i])
        {
            return std::pair<Erreur, int>(MAXI, i);
        }
    }

    // 3. Les points étape doivent avoir au moins 2 sentiers incidents
    for (int i = 0; i < nbPoints; ++i)
    {
        if (e.getTypes()[i] == ETAPE && nbIncidents[i] < 2)
        {
            return std::pair<Erreur, int>(ETAPE, i);
        }
    }

    // 1. Pour chaque point d'interêt, il doit exister un chemin qui le relie à une entrée du parc
    std::vector<int> visites(nbPoints, false);
    std::vector<int> types = e.getTypes();
    for (int i = 0; i < nbPoints; ++i)
    {
        if (e.getTypes()[i] != ENTREE)
        {
            if (nbIncidents[i] < 1)
            {
                return std::pair<Erreur, int>(LIEN, i);
            }
            std::fill(visites.begin(), visites.end(), false);
            // appel de la fonction recursive relieEntree qui va verifier si le point i est connecte a une entree
            bool relie = relieEntree(sentiers, i, types, nbPoints, visites);
            if (!relie)
            {
                return std::pair<Erreur, int>(LIEN, i);
            }
        }
    }

    return std::pair<Erreur, int>(OK, 0); // aucune erreur
}

void Solution::afficher()
{
    for (int i = 0; i < nbPoints; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (sentiers[i][j] > 0)
            {
                std::cout << i << " " << j << std::endl;
            }
        }
    }

    std::cout << "fin" << std::endl;
}

int Solution::calculer()
{
    coutTotal = 0;
    for (int i = 0; i < nbPoints; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            coutTotal += sentiers[i][j];
        }
    }

    return coutTotal;
}

// methode permettant de savoir si une valeur de cout total est presente dans la liste tabou ou pas
bool Solution::estTabou(int coutTotal)
{
    return std::find(tabou.begin(), tabou.end(), coutTotal) != tabou.end();
}

