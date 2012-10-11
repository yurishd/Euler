#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

struct Helper_t
{
  long m_prime;
  long m_count;

  Helper_t() : m_prime(0), m_count(0) {}
  Helper_t(long prime) : m_prime(prime), m_count(1) {}

  bool operator==(Helper_t const &other)
  { return ((m_prime == other.m_prime) && (m_count == other.m_count)); }
};

ostream& operator<<(ostream &os, Helper_t const& hlp);

void build_prime_divisors(vector<Helper_t>&prime_divisors,
                          vector<long>&primes,
                          long trgN);
bool check_and_apply(vector<Helper_t>&all_divisors,
                     vector<Helper_t>&new_divisors);

int main(int argc, char *argv[])
{
  vector<long> primes;
  long tmp;
  ifstream is("../primes_1mil.txt");
  is >> tmp;
  while (is) {
    primes.push_back(tmp);
    is >> tmp;
  }
  primes.push_back(tmp);


  vector<Helper_t> div_primes;
  vector<Helper_t> div_primes2;
  vector<Helper_t> debug1;
  vector<Helper_t> debug2;
  vector<Helper_t> debug3;
  for (long i = 0; i < 1000000; ++i) {
    if (0 == i % 10000) {
      cout << i << endl;
    }
    div_primes.clear();
    build_prime_divisors(div_primes, primes, i);
    if (div_primes.size() == 4) {
      vector<Helper_t> tmp(div_primes);
      div_primes2.clear();
      build_prime_divisors(div_primes2, primes, i+1);
      if (div_primes2.size() == 4) {
        debug1 = div_primes2;
        if (check_and_apply(tmp, div_primes2)) {
          div_primes2.clear();
          build_prime_divisors(div_primes2, primes, i+2);
          if (div_primes2.size() == 4) {
            debug2 = div_primes2;
            if (check_and_apply(tmp, div_primes2)) {
              div_primes2.clear();
              build_prime_divisors(div_primes2, primes, i+3);
              if (div_primes2.size() == 4) {
                debug3 = div_primes2;
                if (check_and_apply(tmp, div_primes2)) {
                  cout << i << " = ";
                  copy(div_primes.begin(), div_primes.end(), 
                       ostream_iterator<Helper_t>(cout, " * "));
                  cout << endl;
                  cout << i+1 << " = ";
                  copy(debug1.begin(), debug1.end(), 
                       ostream_iterator<Helper_t>(cout, " * "));
                  cout << endl;
                  cout << i+1 << " = ";
                  copy(debug2.begin(), debug2.end(), 
                       ostream_iterator<Helper_t>(cout, " * "));
                  cout << endl;
                  cout << i+1 << " = ";
                  copy(debug3.begin(), debug3.end(), 
                       ostream_iterator<Helper_t>(cout, " * "));
                  cout << endl;
                 return 0;
                }
              }
            }
          }
        }
      }
    }
  }
  cout << " NEVER FINISH"  << endl;
  return 0;
}

void build_prime_divisors(vector<Helper_t>&prime_divisors,
                          vector<long>&primes,
                          long trgN)
{
  size_t prsz = primes.size();
  size_t pri = 0;
  size_t prev_pri = 0xFFFFFFFF;
  prime_divisors.clear();
  long modulo;
  long count = 0;
  while (pri < prsz) {
    if (trgN < primes[pri]) return;
    modulo = trgN % primes[pri];
    //cout << trgN << "%" << primes[pri] << " = " << modulo << endl;
    if ( modulo == 0) {
      trgN /= primes[pri];
      if (pri == prev_pri) {
        ++prime_divisors[prime_divisors.size()-1].m_count;
      } else {
        prev_pri = pri;
        prime_divisors.push_back(Helper_t(primes[pri]));
        ++count;
        if (count > 4) return;
      }
    } else {
      ++pri;
    }
  }
}

ostream& operator<<(ostream &os, Helper_t const& hlp)
{
  os << hlp.m_prime << "^" << hlp.m_count;
  return os;
}

bool check_and_apply(vector<Helper_t>&all_divisors,
                     vector<Helper_t>&new_divisors)
{
  size_t sz = all_divisors.size();
  for (size_t isz = 0; isz < new_divisors.size(); ++isz) {
    for (size_t jsz = 0; jsz < sz; ++jsz) {
      if (new_divisors[isz] == all_divisors[jsz]) return false;
    }
    all_divisors.push_back(new_divisors[isz]);
  }
  return true;
}
