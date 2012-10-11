#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

long const HIEGHT = 20;
long const WIDTH  = 20;

bool build_primes(vector<long> &primes, long max_number);
bool add_divisors(vector<long> const &primes,
                  vector<long> &divisors,
                  long N);

void debug_print(vector<long> const &divisors, long N)
{
  cout << N << ": ";
  copy(divisors.begin(), divisors.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;
}

int main(int argc, char*argv[])
{
  long ALL_MOVES = HIEGHT + WIDTH;
  vector<long> primes;
  build_primes(primes, ALL_MOVES);
  copy(primes.begin(), primes.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;

  vector<long> up_numbers;
  vector<long> up_divisors;
  vector<long> down_numbers;
  vector<long> down_divisors;
  vector<long> result_divisors;

  long sp = HIEGHT;
  if (sp < WIDTH) {
    sp = WIDTH;
  }
  ++sp;
  for (; sp <= ALL_MOVES; ++sp) {
    up_numbers.push_back(sp);
  }
  sp = HIEGHT;
  if (sp > WIDTH) {
    sp = WIDTH;
  }
  for (long i = 2; i <= sp; ++i) {
    down_numbers.push_back(i);
  }
  size_t sz = primes.size();
  size_t isz;
  for ( isz = 0; isz < sz; ++isz) {
    down_divisors.push_back(0);
    up_divisors.push_back(0);
    result_divisors.push_back(0);
  }

  sz = up_numbers.size();
  for (isz = 0; isz < sz; ++isz) {
    //add_divisors(primes, up_divisors, up_numbers[isz]);
    add_divisors(primes, result_divisors, up_numbers[isz]);
    debug_print(result_divisors, up_numbers[isz]);
    for (size_t iisz = 0; iisz < result_divisors.size(); ++iisz) {
      up_divisors[iisz] += result_divisors[iisz];
      result_divisors[iisz] = 0;
    }
  }
  cout << "=======================" << endl;
  sz = down_numbers.size();
  for (isz = 0; isz < sz; ++isz) {
    //add_divisors(primes, down_divisors, down_numbers[isz]);
    add_divisors(primes, result_divisors, down_numbers[isz]);
    debug_print(result_divisors, down_numbers[isz]);
    for (size_t iisz = 0; iisz < result_divisors.size(); ++iisz) {
      down_divisors[iisz] += result_divisors[iisz];
      result_divisors[iisz] = 0;
    }
  }
  sz = down_divisors.size();
  for (isz = 0; isz < sz; ++isz) {
    result_divisors[isz] = up_divisors[isz] - down_divisors[isz];
    if (result_divisors[isz] < 0) {
      cout << "What?!?!?" << endl;
    }
  }
  copy(up_numbers.begin(), up_numbers.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;
  copy(up_divisors.begin(), up_divisors.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;
  copy(down_numbers.begin(), down_numbers.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;
  copy(down_divisors.begin(), down_divisors.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;
  copy(result_divisors.begin(), result_divisors.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;

  long result = 1;
  sz = primes.size();
  cout << result << endl;
  for (isz = 0; isz < sz; ++isz) {
    for (long i = 0; i < result_divisors[isz]; ++i) {
      result *= primes[isz];
    }
    cout << primes[isz] << "/" << result_divisors[isz]
         << ": " << result << endl;
  }

  cout << "result : ";
  cout << result;
  cout << endl;
  long testlong = 68923264410;
  cout << numeric_limits<long>::max()<< endl;
  cout <<"68923264410" << endl;

  sz = primes.size();
  for (isz = 0; isz < sz; ++isz) {
    result_divisors[isz] = 0;
  }
  add_divisors(primes, result_divisors, testlong);
  copy(result_divisors.begin(), result_divisors.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;

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

bool add_divisors(vector<long> const &primes,
                  vector<long> &divisors,
                  long N)
{
  if (primes.size() != divisors.size()) return false;
  size_t isz = 0;
  cout << "N=" << N;
  while (isz < primes.size() && (N >= primes[0])) {
    if (0 == (N % primes[isz])) {
      N=N/primes[isz];
      ++divisors[isz];
      cout << ": " << primes[isz] << "/" << isz;
    } else {
      ++isz;
    }
  }
  cout << endl;
  return true;
}
