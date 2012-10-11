#include <iostream>
#include <math.h>

using namespace std;
bool isPrime(long p);

int main(int argc, char *argv[])
{
  long maxN = 0;
  long maxA = -1000;
  long maxB = -1000;
  for (long a = -999; a < 1000; ++a) {
    cout << a << endl;
    for (long b = -999; b < 1000; ++b) {
      long n = 0;
      while (isPrime(n*n + a*n + b)) {
        ++n;
      }
      if (maxN < n) {
        maxN = n;
        maxA = a;
        maxB = b;
        cout << maxN << ": n^2 + (" << maxA << ")*n + (" << maxB << ")" << endl;
     }
    }
  }

  cout << maxN << ": n^2 + (" << maxA << ")*n + (" << maxB << ")" << endl;
  cout << maxA*maxB<< endl;
  return 0;
}

bool isPrime(long p)
{
  if (p < 1) return false;
  long divisor = 2;
  long divisorMax = (long)sqrt((double)p);
  while (divisor <= divisorMax) {
    if (0 == p % divisor) return false;
    ++divisor;
  }
  return true;
}
