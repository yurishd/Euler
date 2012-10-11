#include <iostream>
#include <set>
#include <deque>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

struct PrimeCircTetster
{
  PrimeCircTetster(set<long> &primes) :
    m_result(0), m_primes(primes), m_count(0){}

  void operator() (long prime)
  {
    //if (0 == ++m_count % 100) {
    //  cout << m_count++ <<  ": " <<  m_result << endl;
    //}
    long prime_to_test = prime;
    deque<long> helper;
    while (prime_to_test > 0) {
      helper.push_front(prime_to_test % 10);
      prime_to_test /= 10;
    }
    helper.push_front(helper[helper.size()-1]);
    helper.pop_back();
    prime_to_test = 0;
    for (size_t isz = 0; isz < helper.size(); ++isz) {
      prime_to_test = prime_to_test*10 + helper[isz];
    }
    bool bGood = true;
    while (prime_to_test != prime) {
      if (m_primes.find(prime_to_test) == m_primes.end()) {
        bGood = false;
        break;
      }
      helper.push_front(helper[helper.size()-1]);
      helper.pop_back();
      prime_to_test = 0;
      for (size_t isz = 0; isz < helper.size(); ++isz) {
        prime_to_test = prime_to_test*10 + helper[isz];
      }
    }
    if (bGood) {
      ++m_result;
      cout << "prime: " << prime << ", result: " << m_result << endl;
    }
  }
  long m_result;
  set<long> &m_primes;
  int m_count;
};

int main(int argc, char* argv[])
{
  long tmp;
  set<long> primes;

  ifstream is("../primes_1mil.txt");
  is >> tmp;
  while (is) {
    primes.insert(tmp);
    is >> tmp;
  }
  primes.insert(tmp);

  PrimeCircTetster tester(primes);

  long result = for_each(primes.begin(), primes.end(), tester).m_result;
  cout << result << endl;
  return 0;
}
