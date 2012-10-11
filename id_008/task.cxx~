#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

bool build_primes(vector<long> &primes, size_t max_number_count);

int main(int argc, char *argv[])
{
  vector<long> primes;
  build_primes(primes, 10001);
  cout << primes.size() << " : " << primes[primes.size()-1] << endl;
  return 0;
}

bool build_primes(vector<long> &primes, size_t max_number_count)
{
  primes.clear();
  primes.push_back(2);
  primes.push_back(3);
  long prime = 3;
  long new_prime_max;
  bool is_prime;
  while (primes.size() < max_number_count) {
    if (prime + 2 < prime) {
      cout << "overflow!!!!!" << endl;
      return false;
    }
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
