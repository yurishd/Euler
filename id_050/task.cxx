#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

struct Helper_t
{
  set<long>::iterator m_lastPrime;
  long m_count;
  long m_sum;

  Helper_t() : m_lastPrime(0), m_count(0), m_sum(0) {}
};

ostream& operator<<(ostream& os, Helper_t const &hlp);

int main(int argc, char *argv[])
{
  long thePrime = -1;
  long theCount = 0;
  set<long> primes;
  long tmp;
  ifstream is("../primes_1mil.txt");
  is >> tmp;
  while (is) {
    primes.insert(tmp);
    is >> tmp;
  }
  primes.insert(tmp);


  map<long, Helper_t> sums;
  set<long>::reverse_iterator itr = primes.rbegin();
  set<long>::reverse_iterator itr_end = primes.rend();
  set<long>::iterator it = primes.begin();
  set<long>::iterator it_end = primes.end();
  set<long>::iterator it_tmp = primes.begin();
  map<long, Helper_t>::iterator it_sums;

  while (it_tmp != it_end) {
    Helper_t hlp;
    it = it_tmp;
    for (; hlp.m_sum + (*it) <= *itr; ++it) {
      hlp.m_sum += *it;
      ++hlp.m_count;
      hlp.m_lastPrime = it;
    }
    //cout << *it_tmp << " -> " << hlp << endl;
    sums.insert(map<long, Helper_t>::value_type(*it_tmp, hlp));
    ++it_tmp;
  }

  for (;itr != itr_end; ++itr) {
    it_sums = sums.begin();
    //cout << *itr << endl;
    while (it_sums->first <= (*itr/2)) {
      while (it_sums->second.m_sum > *itr) {
        it_sums->second.m_sum -= *it_sums->second.m_lastPrime;
        --it_sums->second.m_lastPrime;
        --it_sums->second.m_count;
      }
      
      if (it_sums->second.m_sum == *itr) {
        if (theCount < it_sums->second.m_count) {
          theCount = it_sums->second.m_count;
          thePrime = *itr;
        }
        break;
      }
      ++it_sums;
    }
  }
  cout << thePrime << ":" << theCount << endl;
  return 0;
}

ostream& operator<<(ostream& os, Helper_t const &hlp)
{
  os << "sum: " << hlp.m_sum << ", count: " << hlp.m_count
     << ", last prime: " <<  *hlp.m_lastPrime;
  return os;
}
