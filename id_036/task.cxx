#include <iostream>
#include <vector>

using namespace std;

void increment(vector<int> &theNumberB, vector<int> &theNumberD);
bool is_polindromic(vector<int> &theNumberB, vector<int> &theNumberD);

int main(int argc, char *argv[])
{
  vector<int> theNumberB(1,0);
  vector<int> theNumberD(1,0);
  int result = 0;
  for (int i = 1; i < 1000000; ++i) {
    increment(theNumberB, theNumberD);
    if (is_polindromic(theNumberB, theNumberD)) {
      result += i;
    }
  }
  cout << result << endl;
  return 0;
}

void increment(vector<int> &theNumberB, vector<int> &theNumberD)
{
  ///////////////
  //Increment Binary
  ///////////////
  theNumberB[0] += 1;
  size_t isz = 0;
  while (1) {
    if (theNumberB[isz] < 2) {
      break;
    }
    theNumberB[isz] = 0;
    if (isz + 1 == theNumberB.size()) {
      theNumberB.push_back(0);
    }
    ++isz;
    ++theNumberB[isz];
  }
  ///////////////
  //Increment Dec
  ///////////////
  theNumberD[0] += 1;
  isz = 0;
  while (1) {
    if (theNumberD[isz] < 10) {
      break;
    }
    theNumberD[isz] = 0;
    if (isz + 1 == theNumberD.size()) {
      theNumberD.push_back(0);
    }
    ++isz;
    ++theNumberD[isz];
  }
}

bool is_polindromic(vector<int> &theNumberB, vector<int> &theNumberD)
{
  size_t isz;
  size_t szb = theNumberB.size();
  for (isz = 0; isz < szb/2; ++isz) {
    if (theNumberB[isz] != theNumberB[szb - isz - 1]) {
      return false;
    }
  }
  size_t szd = theNumberD.size();
  for (isz = 0; isz < szd/2; ++isz) {
    if (theNumberD[isz] != theNumberD[szd - isz - 1]) {
      return false;
    }
  }
  return true;
}
