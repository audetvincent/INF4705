#include "utils.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

// fonction creant un exemplaire a partir d'un fichier
Exemplaire* lireFichier(std::string nom)
{
    std::ifstream fichier(nom, std::ios::in);

    if(fichier)
    {
        int nbPoints;
        std::vector<int> types;
        std::vector<int> maxSentiers;
        std::vector<std::vector<int> > couts;
        float temp;

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

        couts = std::vector<std::vector<int> >(nbPoints, std::vector<int>(nbPoints));
        for (int i = 0; i < nbPoints; ++i)
        {
            for (int j = 0; j < nbPoints; ++j)
            {
                fichier >> temp;
                couts[i][j] = temp * 1000;
                // Deux points de vue ne peuvent pas etre lies
                if (types[i] == PT_DE_VUE && types[j] == PT_DE_VUE)
                    couts[i][j] = 0;
                else if (types[i] == ENTREE && types[j] == ENTREE)  // Connecter deux entree serait penalisant
                    couts[i][j] = 0;
            }
        }

        Exemplaire* e = new Exemplaire(nbPoints, types, maxSentiers, couts);

        fichier.close();

        return e;
    }

    else
    {
        std::cout << "Erreur lors de l'ouverture du fichier " << nom << std::endl;
        return nullptr;
    }
}

// fonction recursive capable de determiner si il existe un chemin vers une entree a partir d'un point donne
bool relieEntree(std::vector<std::vector<int> >& sentiers, int point, std::vector<int>& types, int nbPoints, std::vector<int>& visites)
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

// Fonction retournant pour un noeud donne, son premier enfant dont le nombre de sentiers incidents est inferieur au maximum autorise
int trouverNoeudEnfant(Solution &s, Exemplaire &e, int noeud, std::vector<int>& visites)
{
    int nbPoints = e.getNbPoints();
    std::vector<std::vector<int> > sentiers = s.getSentiers();
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

// Fonction retournant pour un point donne la destination du sentier de cout minimum que l'on pourrait ajouter
int sentierMin(int& noeud, Solution &s, Exemplaire &e)
{
    int nbPoints = e.getNbPoints();
    int noeudEnfant;
    int mini = nbPoints;
    std::vector<std::vector<int> > couts = e.getCouts();
    std::vector<std::vector<int> > sentiers = s.getSentiers();
    std::vector<int> nbSentiers = s.getNbIncidents();
    std::vector<int> maxSentiers = e.getMaxSentiers();
    std::vector<int> types = e.getTypes();

    // si le noeud est plein, on doit trouver un de ses enfants (uniquement dans le cas d'une erreur LIEN)
    std::vector<int> visites(nbPoints, false);
    visites[noeud] = true;
    if (nbSentiers[noeud] >= maxSentiers[noeud])
    {
        noeudEnfant = trouverNoeudEnfant(s, e, noeud, visites);
        if (noeudEnfant != nbPoints)
            noeud = noeudEnfant;
    }

    // on construit une map pour profiter du fait qu'elle soit deja triee par defaut et de cette maniere on peut essayer
    // plusieurs candidats d'affile dans le cas ou une certaine configuration serait deja dans la liste tabou
    std::map<int, int> chemins;
    auto it = couts[noeud].begin();
    int i = 0;
    while(it != couts[noeud].end())
    {
        // on accepte de faire des liens avec des noeuds deja pleins pour faire avancer la recherche et eviter d'etre trop vite coinces
        if (*it > 0 && sentiers[noeud][i] == 0 && types[i] != PT_DE_VUE && nbSentiers[i] <= maxSentiers[i])
        {
            chemins.insert(std::pair<int, int>(*it, i));
        }
        i++;
        ++it;
    }

    auto mapIt = chemins.begin(); // map deja triee par defaut
    int nouveauCout = s.getCoutTotal() + mapIt->first;
    mini = mapIt->second;
    while(s.estTabou(nouveauCout) && mapIt != chemins.end())
    {
        nouveauCout -= mapIt->first;
        ++mapIt;
        nouveauCout += mapIt->first;
        mini = mapIt->second;
    }

    // si toutes les configurations sont dans la liste tabou on sait pas trop quoi faire alors on retourne le moins probable
    if (mapIt == chemins.end())
    {
        mini = chemins.rbegin()->second;
    }

    return mini;
}

// fonction retournant pour un point donnee son sentier incident de cout maximum
int sentierMax(Solution& s, int noeud)
{
    std::vector<std::vector<int> > sentiers = s.getSentiers();
    std::vector<int> nbSentiers = s.getNbIncidents();
    int nbPoints = s.getNbPoints();
    int maxi = nbPoints;

    // on construit une map pour profiter du fait qu'elle soit deja triee par defaut et de cette maniere on peut essayer
    // plusieurs candidats d'affile dans le cas ou une certaine configuration serait deja dans la liste tabou
    std::map<int, int> chemins;
    auto it = sentiers[noeud].begin();
    int i = 0;
    while(it != sentiers[noeud].end())
    {
        if (*it > 0)
        {
            chemins.insert(std::pair<int, int>(*it, i));
        }
        ++it;
        i++;
    }

    auto mapIt = chemins.rbegin(); // map deja triee par defaut
    int nouveauCout = s.getCoutTotal() - mapIt->first;
    maxi = mapIt->second;
    while(s.estTabou(nouveauCout) && mapIt != chemins.rend())
    {
        nouveauCout += mapIt->first;
        ++mapIt;
        nouveauCout -= mapIt->first;
        maxi = mapIt->second;
    }

    // si toutes les configurations sont dans la liste tabou on sait pas trop quoi faire alors on retourne le moins probable
    if (mapIt == chemins.rend())
    {
        maxi = chemins.begin()->second;
    }

    return maxi;
}

int arrondir(int chiffre)
{
    return round(chiffre * 1000.0) / 1000.0;
}
