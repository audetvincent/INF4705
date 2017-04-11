#include <string>
#include <fstream>
#include "Exemplaire.h"

#define PT_DE_VUE 1
#define ENTREE 2
#define ETAPE 3

Exemplaire* lireFichier(std::string nom);

bool relieEntree(float** sentiers, int point, int nbPoints, bool* visites);
