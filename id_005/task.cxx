#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <iterator>
#include <algorithm>

using namespace std;

struct prime_count_t
{
  int m_required;
  int m_support;

  prime_count_t() : m_required(1), m_support(1) {}
};

typedef map<long, prime_count_t> primes_t;

struct init_all_supports
{
  void operator() (std::pair<const long , prime_count_t>& it)
  {
    it.second.m_support = it.second.m_required;
  }
};

struct count_all
{
  count_all() :m_product(1) {}
  void operator() (std::pair<const long , prime_count_t>& it)
  {
    for(int i = 0; i < it.second.m_required; ++i){
      m_product = m_product * it.first;
    }
  }
  long m_product;
};

struct print_all
{
  print_all() : m_not_first(false), m_product(1) {}
  void operator() (std::pair<const long , prime_count_t>& it)
  {
    if (m_not_first) {
      cout << " * ";
    } else {
      m_not_first = true;
    }
    cout << "(" << it.first << " ^ " << it.second.m_required << ")";
    for(int i = 0; i < it.second.m_required; ++i){
      m_product = m_product * it.first;
    }
  }
  bool m_not_first;
  long m_product;
};


bool build_primes(vector<long> &primes, long max_number);
void test_prime_dividers(primes_t &prime_dividers,
                         vector<long> const &real_primes,
                         long i);
int main(int argc, char *argv[])
{
  vector<long> real_primes;
  if (!build_primes(real_primes, 20)) {
    cout << "Failed to build primes????" << endl;
    return 1;
  }
  copy(real_primes.begin(),
       real_primes.end(), ostream_iterator<long>(cout, ","));
  cout << endl;

  primes_t prime_dividers;

  prime_dividers.insert(primes_t::value_type(2, prime_count_t()));
  prime_dividers.insert(primes_t::value_type(3, prime_count_t()));

  for (long i = 4; i < 21; ++i) {
    cout << "test number " << i << endl;
    test_prime_dividers(prime_dividers, real_primes, i);
  }
  long result = for_each(prime_dividers.begin(), prime_dividers.end(), print_all()).m_product;
  cout << " = " << result << endl;
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

void test_prime_dividers(primes_t &prime_dividers,
                         vector<long> const &real_primes,
                         long number)
{
  size_t sz = real_primes.size();
  size_t i = 0;
  long tmp;
  for_each(prime_dividers.begin(), prime_dividers.end(), init_all_supports());
  while ((i < sz) && (number > 1)) {
    tmp = number / real_primes[i];
    //    cout << i << " : " << real_primes[i] << " : " << tmp << " : " <<  number << endl;
    if (number == tmp * real_primes[i]) {
      if (prime_dividers[real_primes[i]].m_support > 0) {
        prime_dividers[real_primes[i]].m_support--;
        cout << "SR for " << real_primes[i] << ", " << 
          prime_dividers[real_primes[i]].m_support << endl;
      } else {
        prime_dividers[real_primes[i]].m_required++;
        cout << "RI for " << real_primes[i] << ", " << 
          prime_dividers[real_primes[i]].m_required << endl;
      }
      number = tmp;
    } else {
      ++i;
    }
  }
}
