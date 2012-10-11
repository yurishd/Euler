#include <iostream>
#include <vector>

using namespace std;

long divisors_sum(long N);

int main(int argc, char *argv[])
{
  long result = 0;
  vector<bool> index(10000+1, true);
  long divSum;
  for (size_t i = 1; i < index.size(); ++i) {
    if (index[i]) {
      divSum = divisors_sum(i);
      if (divSum != i) {
        if (divisors_sum(divSum) == i) {
          result += i;
          result += divSum;
          index[divSum] = false;
        }
      }
    }
  }
  cout << result << endl;
  return 0;
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
