#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

long const THE_NUMBER = 600851475143;

bool build_primes(vector<long> &primes, long max_number);

int main(int argc, char *argv[])
{
  long cur_the_number = THE_NUMBER;
  long MAX_PRIME = (long)sqrt((double)THE_NUMBER);
  vector<long> primes;

  if (!build_primes(primes, MAX_PRIME)) return 1;

  cout << "Primes are built!!!" << endl;

  for (size_t i = primes.size()-1; i >= 0; --i) {
    if (THE_NUMBER % primes[i] == 0) {
      cout << primes[i] << endl;
      return 0;
    }
  }

  cout << THE_NUMBER << endl;
  cout << primes.size() << endl;
  cout << primes[primes.size()-1] << endl;
  return 0;
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
