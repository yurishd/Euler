#include <iostream>
#include <set>
#include <deque>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

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

  for (int i = 10; i < 100; ++i) {
    for (int j = 11; j < 100; ++j) {
      if (0 == j % 10) continue;
      if (0 == j % 11) continue;
      if ((i%10) != (j/10)) continue;
      if ((j * (i/10)) == (i*(j%10))) {
        cout << i << "/" << j << endl;
      }
    }
  }

  long result = 0;
  cout << result << endl;
  return 0;
}
