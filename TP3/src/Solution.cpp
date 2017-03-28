#include "Solution.h"

Solution::Solution(int nbPoints) : nbPoints(nbPoints)
{
  sentiers = new float*[nbPoints];
  for (int i = 0; i < nbPoints; ++i)
  {
    sentiers[i] = new float[nbPoints];
  }
}

Solution::~Solution()
{
  for (int i = 0; i < nbPoints; ++i)
  {
    delete [] sentiers[i];
  }
  delete [] sentiers;
}

bool Solution::verifier()
{
}

