/*
 * Classe représentant une solution du problème
 */


class Solution 
{
public:
  Solution(int nbPoints);
  ~Solution();
  bool verifier();

private:
  int nbPoints;
  float** sentiers;
};
