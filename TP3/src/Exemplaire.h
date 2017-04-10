/*
 * Classe représentant un exemplaire du problème
 */


class Exemplaire 
{
public:
  Exemplaire(int nbPoints);
  Exemplaire(int nbPoints, int* types, int* maxSentiers, float** couts);
  ~Exemplaire();
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
