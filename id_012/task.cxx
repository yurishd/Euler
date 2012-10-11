#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void build_prime_divisors(vector<long>&, vector<long>&, long);

int main(int argc, char *argv[])
{
  long result = 1;
  long ind = 1;


  vector<long> primes;
  primes.reserve(500);
  //  primes.push_back(2);

  //vector<long> prime_divisors;
  vector<long> prime_divisors;

  while (1) {
    ++ind;
    if (result > result + ind) {
      cout << "Overflow!!!!" << endl;
      return 0;
    }
    result += ind;
    build_prime_divisors(prime_divisors, primes, result);
    long tmp = 1;
    for (size_t i = 0; i < prime_divisors.size(); ++i) {
      tmp *= (prime_divisors[i]+1);
    }
    if (tmp > 500) {
      cout << tmp << " divisors" << endl;
      break;
    }
    //if (ind % 100 == 0) {
      //return 0;
      //cout << ind << ":" << primes.size() << 
      //  " : " << tmp << endl;
    //}
    
  }
  cout << result << endl;
  return 0;
}

void add_more_primes(vector<long>& primes, long trgN);

void build_prime_divisors(vector<long>&prime_divisors,
                          vector<long>&primes,
                          long trgN)
{
  add_more_primes(primes, (long)sqrt((double)trgN));

  size_t prsz = primes.size();
  size_t pri = 0;
  size_t prev_pri = 0xFFFFFFFF;
  prime_divisors.clear();
  long modulo;
  while (pri < prsz) {
    modulo = trgN % primes[pri];
    //cout << trgN << "%" << primes[pri] << " = " << modulo << endl;
    if ( modulo == 0) {
      trgN /= primes[pri];
      if (pri == prev_pri) {
        ++prime_divisors[prime_divisors.size()-1];
      } else {
        prev_pri = pri;
        prime_divisors.push_back(1);
      }
    } else {
      ++pri;
    }
  }
}

void add_more_primes(vector<long>& primes, long max_number)
{
  long prime = 0;
  if (primes.size() > 0) {
    prime = primes[primes.size()-1];
    if (2 == prime){
      prime = 1;
    }
  } else {
    primes.push_back(2);
    if (max_number < 3) {
      cout << "2 max_number"  << endl;
      return;
    }
    prime = 1;
  }
  long new_prime_max;
  bool is_prime;
  while (prime + 2 < max_number) {
    prime += 2;
    new_prime_max = (long)sqrt((double)prime);
    is_prime = true;
    for (size_t i = 2; i < primes.size(); ++i) {
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
    }
  }
}
