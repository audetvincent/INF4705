#ifndef SOLUTION_H
#define SOLUTION_H

/*
 * Classe représentant une solution du problème
 */

#include "Exemplaire.h"
#include <utility>
#include <deque>

enum Erreur {OK, PT_DE_VUE, ENTREE, ETAPE, MAXI, LIEN};

class Solution
{
public:
    Solution(int nbPoints);
    ~Solution();
    void setNbPoints(int nbPoints);
    void setNbIncidents(std::vector<int>& nbIncidents);
    void setSentier(int depart, int arrivee, int cout);
    void setSentiers(std::vector<std::vector<int> >& sentiers);
    void deleteSentier(int depart, int arrivee);
    void addTabou(int coutTotal);
    int getNbPoints();
    std::vector<int> getNbIncidents();
    std::vector<std::vector<int> > getSentiers();
    int getCoutTotal();
    std::deque<int> getTabou();
    std::pair<Erreur, int> verifier(Exemplaire& e);
    void afficher();
    int calculer();
    bool estTabou(int coutTotal);

private:
    int nbPoints; // nombre de points dans le parc
    std::vector<int> nbIncidents; // vecteur indiquant pour chaque point le nombre de sentiers incidents
    std::vector<std::vector<int> > sentiers; // matrice representant la solution courante
    int coutTotal; // cout total de la configuration courante
    std::deque<int> tabou; // liste tabou des couts des configurations
};

#endif
