#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
long g_sum = 0;

bool build_primes(vector<long> &primes, long max_prime_number);

int main(int argc, char *argv[])
{
  vector<long> primes;
  build_primes(primes, 2000000);
  cout << g_sum + 5 << endl;
  return 0;
}

bool build_primes(vector<long> &primes, long max_prime_number)
{
  primes.clear();
  primes.push_back(2);
  primes.push_back(3);
  long prime = 3;
  long new_prime_max;
  bool is_prime;
  while (prime < max_prime_number+1) {
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
    if (is_prime) {
      primes.push_back(prime);
      long new_sum = g_sum + prime;
      if (new_sum < g_sum) {
        cout << "OVERFLOW IN SUM!?!?!?!" << endl;
        return false;
      }
      g_sum = new_sum;
    }
  }
  return true;
}
