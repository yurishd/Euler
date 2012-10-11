#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

void build_factorial_in_primes(vector<long> const &primes,
                               vector<long> &out, long N);
void add_factorial_in_primes(vector<long> const &primes,
                               vector<long> &out, long N);
bool calc(vector<long> const &primes,
          vector<long> const &nominator,
          vector<long> &dom1,
          vector<long> &dom2);

int main(int argc, char* argv[])
{
  long tmp;
  vector<long> primes;

  ifstream is("../primes_1mil.txt");
  is >> tmp;
  while (is) {
    primes.push_back(tmp);
    is >> tmp;
  }
  primes.push_back(tmp);

  vector<long> main_factorial;
  vector<long> tmp_factorial1;
  vector<long> tmp_factorial2;

  build_factorial_in_primes(primes, main_factorial, 22);
  //copy(main_factorial.begin(),main_factorial.end(), ostream_iterator<long>(cout, ", "));
  //cout <<endl;
  //return 0;
  long result = 0;
  for (int i = 23; i < 101; ++i) {
    add_factorial_in_primes(primes, main_factorial, i);
    int max_m = i/2;
    int coeff = (i % 2 == 0 ? 1 : 2);
    if (1000 == i) {
    cout << "max_m = " << max_m << ", coeff = " << coeff << endl;
    copy(primes.begin(),primes.begin() + main_factorial.size(), ostream_iterator<long>(cout, ", "));
    cout <<endl;
    }
    for (int j = max_m; j > 0; --j) {
      build_factorial_in_primes(primes, tmp_factorial1, j);
      build_factorial_in_primes(primes, tmp_factorial2, i - j);
      if (1000 == i) {
      copy(main_factorial.begin(),main_factorial.end(), ostream_iterator<long>(cout, ", "));
      cout <<endl;
      copy(tmp_factorial1.begin(),tmp_factorial1.end(), ostream_iterator<long>(cout, ", "));
      cout <<endl;
      copy(tmp_factorial2.begin(),tmp_factorial2.end(), ostream_iterator<long>(cout, ", "));
      cout <<endl;
      }

      if (calc(primes, main_factorial, tmp_factorial1, tmp_factorial2)) {
        result += coeff;
      } else {
        if (1000 == i) {
        cout << "-------------" << endl;
        }
        break;
      }
      coeff = 2;
    }
  }
  cout << result << endl;
  return 0;
}

void build_factorial_in_primes(vector<long> const &primes,
                               vector<long> &out, long N)
{
  out.clear();
  for (long i = 2; i <= N; ++i) {
    //cout << "i = " << i << endl;
    add_factorial_in_primes(primes, out, i);
    //copy(out.begin(),out.end(), ostream_iterator<long>(cout, ", "));
    //cout << endl;
  }
}

void add_factorial_in_primes(vector<long> const &primes,
                               vector<long> &out, long N)
{
  vector<long> atmp;
  size_t isz = 0;
  atmp.push_back(0);

  long new_max = N; //(long)sqrt((double)N);
  //cout << "N = " << N << ", new_max = " << new_max << endl;
  while(primes[isz] <= new_max) {
    if (0 == N % primes[isz]) {
      ++atmp[isz];
      N /= primes[isz];
    } else {
      ++isz;
      atmp.push_back(0);
    }
  }
  
  while (atmp.size() && (0 == atmp[atmp.size() - 1])) {
    atmp.pop_back();
  }
  if (out.size() < atmp.size()) {
    for (isz = 0; isz < out.size(); ++isz) {
      out[isz] += atmp[isz];
    }
    while (out.size() < atmp.size()) {
      isz = out.size();
      out.push_back(atmp[isz]);
    }
  } else {
    for (isz = 0; isz < atmp.size(); ++isz) {
      out[isz] += atmp[isz];
    }
  }
}

bool calc(vector<long> const &primes,
          vector<long> const &nominator,
          vector<long> &dom1,
          vector<long> &dom2)
{
  size_t nsz = nominator.size();
  size_t d1sz = dom1.size();
  size_t d2sz = dom2.size();

  //MUST nsz > d1sz|d2sz
  long result = 1;
  long tmp;
  //cout << "---------------------" << endl;
  for (size_t isz = 0; isz < nsz; ++isz) {
    tmp = nominator[isz];
    if (isz < d1sz) {
      tmp -= dom1[isz];
    }
    if (isz < d2sz) {
      tmp -= dom2[isz];
    }
    //cout << primes[isz] <<"^" <<tmp << ": " << endl;
    for (long i = 0; i < tmp; ++i) {
      result *= primes[isz];
      if (result > 1000000) return true;
      //cout << result << ", ";
    }
    //cout << endl;
  }
  //cout << endl << "-------- " << result << " -------------" << endl;

  if (result > 1000000) return true;
  return false;
}
