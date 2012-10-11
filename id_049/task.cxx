#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;
 
bool build_permutations(long prime, set<long> const &primes, set<long> &out);

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

  set<long>::iterator it = primes.begin();
  set<long>::iterator it_end = primes.end();
  for (; *it < 1000; ++it) {}

  set<long> perm_primes;
  for (; it != it_end; ++it) {
    if (*it == 1487) continue;
    if (!build_permutations(*it, primes, perm_primes)) break;
    if (perm_primes.size() < 2) continue;
    set<long>::iterator it_pp = perm_primes.begin();
    set<long>::iterator it_pp_end = perm_primes.end();
    while (it_pp != it_pp_end) {
      tmp = *it_pp + (*it_pp - *it);
      if (perm_primes.find(tmp) != it_pp_end) {
        cout << *it << ":" << *it_pp << ":" << tmp << endl;
        cout << *it << *it_pp << tmp << endl;
        return 0;
      }
      ++it_pp;
    }
  }
  
  cout << "NOT FOUND" << endl;
  return 0;
}

bool build_permutations(long prime, set<long> const &primes, set<long> &out)
{
  if (prime > 9999) return false;
  out.clear();
  long atmp[4];
  for (size_t i = 0; i < 4; ++i) {
    atmp[3 - i] = prime % 10;
    prime /= 10;
  }

  while (next_permutation(atmp, atmp+4)) {
    prime = atmp[0] * 1000 + atmp[1] * 100 + atmp[2] * 10  + atmp[3];
    if (primes.find(prime) != primes.end()) {
      out.insert(prime);
    }
  }
  
  return true;
}
