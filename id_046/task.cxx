#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
  set<long> primes;
  long tmp;
  ifstream is("../primes_1mil.txt");
  is >> tmp;
  while (is) {
    primes.insert(tmp);
    is >> tmp;
  }
  primes.insert(tmp);
  set<long>::iterator prime_it = primes.begin();

  long sqrtMax = (long) sqrt((double)(tmp/2));

  vector<long> squares(sqrtMax);
  long i;
  for (i = 0; i < sqrtMax; ++i) {
    squares[i] = ((i+1) * (i+1)*2);
  }

  while ((*prime_it) < 9) {
    ++prime_it;
  }

  long j;
  long sqIndex = 2; //2x3^2
  for (i = 9; i < squares[sqrtMax-1]; i += 2) {
    if (i > squares[sqIndex]) {
      ++sqIndex;
    }
    if ((*prime_it) == i) {
      ++prime_it;
      continue;
    }
    for (j = 0; j < sqIndex; ++j) {
      if (primes.find(i - squares[j]) != primes.end()) {
        break;
      }
    }
    if (j == sqIndex) {
      cout << i << endl;
      return 0;
    }
  }

  cout << "NEVER ENDS" <<  endl;
  return 0;
}
