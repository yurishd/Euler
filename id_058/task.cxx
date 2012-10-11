#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <math.h>

int const MAX_NUMBER = 1000;

using namespace std;
bool isPrime(set<long> const & primes, long prime);

int main(int argc, char *argv[])
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
  cout << "FINISHED READING PRIMES" << endl;
  /*
  while (tmp < 200000000) {
    if (0 == tmp % 10000) cout << tmp << endl;
    ++tmp;
    long tmpl = tmp;
    if (isPrime(primes, tmp)) {
      primes.insert(tmp);
    }
  }
  {
    ofstream os("../primes_200mil.txt");
    copy(primes.begin(), primes.end(), ostream_iterator<long>(os, "\n"));
  }
  */
  long side_length = 7;
  long primeN = 8;
  long notPrimeN = 13;
  long N = 49;

  long ltmp;
  long lastPrime = 0;
  while (N < 2000000000) {
    side_length += 2;
    for (int i = 0; i < 4; ++i) {
      ltmp = N + side_length - 1;
      if (ltmp < N) {
        cout << "OVERFLOW" << endl;
        return 0;
      }
      //if (ltmp < 200000000) {
      if (ltmp < 2) {
        if (primes.find(ltmp) != primes.end()) {
          lastPrime = ltmp;
          ++primeN;
        }
      } else {
        if (isPrime(primes, ltmp)) {
          lastPrime = ltmp;
          ++primeN;
        }
      }
      N = ltmp;
    }
    notPrimeN += 4;
    if (primeN * 10 < notPrimeN) {
      cout << "YES!! ->" << lastPrime << ", " << side_length << endl;
      return 0;
    }
  }
  cout << "NO results: " << side_length << ", " << primeN << endl;
  return 0;
}

bool isPrime(set<long> const & primes, long prime)
{
  long maxN = (long)sqrt((double)prime);

  set<long>::const_iterator it = primes.begin();
  while ((*it) <= maxN) {
    if (prime % (*it) == 0) return false;
    ++it;
  }
  return true;
}
