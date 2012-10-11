#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

bool build_primes(vector<long> &primes, long max_number);
bool is_prime(long);
long const MAX_PRIME = 987654321;

int main(int argc, char *argv[])
{
  vector<long> primes;

  //cout << "PRIMES" << endl;
  //if (!build_primes(primes, MAX_PRIME)) return 1;


  cout << "PERMUTATINS" << endl;
  long A[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  long *p1 = A;
  long *p2 = A+9;
  while (p1 < p2) {
    copy(p1, p2, ostream_iterator<long>(cout, ""));
    cout  << endl;
    cout <<  "===========" << endl;
    while (prev_permutation(p1, p2)) {
      //copy(p1, p2, ostream_iterator<long>(cout, ""));
      //cout <<  endl;

      long *p3 = p1;
      long tmp = 0;
      while (p3 < p2) {
        tmp = tmp*10 + *p3++;
      }
      //cout << tmp << endl;
      //copy(p1, p2, ostream_iterator<long>(cout, ""));
      if (is_prime(tmp)) {
        cout << "RESULT: " << tmp << endl;
        return 0;
      }
    }
    p1++;
  }
  return 0;
}

bool is_prime(long i)
{
  long prime_max = (int)sqrt((double)i);
  long prime = 2;
  while (prime <= prime_max) {
    if (0 == i % prime++) return false;
  }
  return true;
}

bool build_primes(vector<long> &primes, long max_number)
{
  primes.clear();
  size_t cur_cap = primes.capacity();
  long new_cap = max_number/2;
  if (new_cap > cur_cap) {
    primes.reserve(new_cap);
    if (primes.capacity() != new_cap) {
      cout << "CAN'T BUILD ARRAY OF PRIMES" << endl;
      return false;
    }
  }
  //not checking...
  long prime = 3;
  primes.push_back(2);
  primes.push_back(prime);
  long new_prime_max;
  bool is_prime;
  while (prime + 2 < max_number) {
    prime += 2;
    new_prime_max = (long)sqrt((double)prime);
    is_prime = true;
    for (size_t i = 0; i < primes.size(); ++i) {
      if (primes[i] > new_prime_max){
        break;
      }
      if (prime % primes[i] == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) primes.push_back(prime);
  }
  return true;
}
