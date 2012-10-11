#include <iostream>
#include <vector>
#include <set>
#include <math.h>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;
long const MAX_NUMBER = 100;
void build_prime_numbers(vector<long> &primes, long maxN);
long get_power_of(vector<long> &primes, long number);
int main(int argc, char* argv[])
{
  //set<long long> debugset;
  vector<long> primes;
  build_prime_numbers(primes, 100);
  //build_prime_numbers(primes, 1000000);
  //{
  //  ofstream os("../primes_1mil.txt");
  //  time_t tms = time(0);
  //  cout << "Creating file" << endl;
  //  copy(primes.begin(), primes.end(), ostream_iterator<long>(os, "\n"));
  //  cout << time(0) - tms << endl;
  //}

  long i,j;
  //for (i = 2; i <= MAX_NUMBER; ++i) {
  //  for (j = 2; j <= MAX_NUMBER; ++j) {
  //    long long longlltmp = (long long)pow(i, j);
  //    debugset.insert(longlltmp);
  //    cout << longlltmp << endl;
  //  }
  //}
  //cout << "=============== " << debugset.size()
  //     << " ==================" << endl;

  long result = 0;
  for (i = 2; i <= MAX_NUMBER; ++i) {
    long powerOf = get_power_of(primes, i);
    if (powerOf < 2) {
      result += (MAX_NUMBER-1);
    } else {
      //cout << "?n: " << i << ": " << powerOf;
      for (j = 2; j <= MAX_NUMBER; ++j) {
        long new_powerOf = powerOf * j;
        if (new_powerOf > MAX_NUMBER) {
          bool bYes = true;
          for (long k = powerOf - 1; k >=2; --k) {
            if ((0 == new_powerOf % k) && (new_powerOf/k <=MAX_NUMBER)){
              //cout << ", k = " << k;
              bYes = false;
              break;
            }
          }
          if (bYes) {
            ++result;
            //} else {
            //  cout << ", pow = " << (long long)pow(i, j);
          }
        }
      }
      //cout << endl;
    }
  }
  cout << endl << result << endl;
  return 0;
}

long get_power_of(vector<long> &primes, long number)
{
  vector<long> tmp;
  size_t sz = 0;
  long new_max = (long)sqrt((double)number);
  for (size_t i = 0; i < primes.size(); ++i) {
    if (number % primes[i] == 0) {
      number /= primes[i];
      --i;
      if (sz +1 != tmp.size()) {
        tmp.push_back(0);
      }
      ++tmp[sz];
    } else {
      if (sz +1 == tmp.size()) {
        ++sz;
      }
    }
  }
  if (tmp.size() == 0) {
    return 0;
  }
  long tmprv = tmp[0];
  for (size_t isz = 1; isz < tmp.size(); ++isz) {
    if (tmp[isz] != tmprv) {
      return 0;
    }
  }
  return tmprv;
}

void build_prime_numbers(vector<long> &primes, long maxN)
{
  primes.push_back(2);
  primes.push_back(3);
  //time_t tms = time(0);
  for (long i = 4; i < maxN; ++i) {
    //if (0 == i % 10000) {
    //  cout << i << endl;
    //}
    bool is_prime = true;
    for (size_t j = 0; j < primes.size(); ++j) {
      if (i % primes[j] == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      primes.push_back(i);
    }
  }
  //cout << time(0) - tms << endl;
}
