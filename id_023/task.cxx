#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <iterator>
#include <algorithm>
#include <set>

using namespace std;
int const UPPER_LIMIT = 28123;
//int  UPPER_LIMIT = 281;

void build_abundant_numbers(vector<long>& out, long MaxN);

int main(int argc, char *argv[])
{
  vector<long> abundant;
  build_abundant_numbers(abundant, UPPER_LIMIT);
  //copy(abundant.begin(),
  //     abundant.end(), ostream_iterator<long>(cout, "\n"));
  //cout << "======================================" << endl;

  vector<bool> wrongN(UPPER_LIMIT+1, true);
  wrongN[0] = false;
  long result = 0;

  size_t isz;
  size_t jsz;
  size_t tmp;
  for (isz = 0; isz < abundant.size(); ++isz) {
    for ( jsz = isz; jsz < abundant.size(); ++jsz) {
      tmp = abundant[isz] + abundant[jsz];
      if (tmp < wrongN.size()) {
        wrongN[abundant[isz] + abundant[jsz]] = false;
      }
    }
  }
  for (long il = 1; il < UPPER_LIMIT + 1; ++il) {
    //cout << setw(5) << il << ": ";
    if (wrongN[il]) {
      //cout << "true" << endl;
      if (result > result + isz) {
        cout << "OVERFLOW!!!" << endl;
        return 0;
      }
      result += il;
    } else {
      //cout << "false" << endl;
    }
  }
  cout << result << endl;
  return 0;
}

long divisors_sum(long N);

void build_abundant_numbers(vector<long>& out, long MaxN)
{
  long ind = 1;
  long sum;
  while (ind <= MaxN) {
    sum = divisors_sum(ind);
    if (ind < sum) {
      out.push_back(ind);
    }
    ++ind;
  }
}

long divisors_sum(long N)
{
  long retValue = 1;
  for (long i = 2; i < N/2 + 1; ++i) {
    if (N % i == 0) {
      retValue += i;
    }
  }
  return retValue;
}
