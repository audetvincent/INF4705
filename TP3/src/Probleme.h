/*
 * Classe représentant une solution du problème
 */


class Probleme 
{
public:
  Probleme(int nbPoints);
  Probleme(int nbPoints, int* types, int* maxSentiers, float** couts);
  ~Probleme();
  void setNbPoints(int nbPoints);
  void setTypes(int* types);
  void setMaxSentiers(int* maxSentiers);
  void setCouts(float** couts);
  int getNbPoints();
  int* getTypes();
  int* getMaxSentiers();
  float** getCouts();

private:
  int nbPoints;
  int* types;
  int* maxSentiers;
  float** couts;
};
