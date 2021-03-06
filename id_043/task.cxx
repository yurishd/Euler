#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>

using namespace std;

int pdn [10] = {
  9, 8, 7, 6, 5, 4, 3, 2, 1, 0
};

bool test_the_pdn();

int main(int argc, char* argv[])
{
  long sum = 0, prevSum;
  do {
    if (0 == pdn[0]) break;
    if (test_the_pdn()) {
      long tmp = 0;
      for (int i = 0; i < 10; ++i) {
        tmp = tmp*10 + pdn[i];
      }
      prevSum = sum;
      sum += tmp;
      if (prevSum > sum) {
        cout << "OVERFLOW!!!" << endl;
        return 0;
      }
    }
  } while (prev_permutation(pdn, pdn + 10));
  cout << "sum = " << sum << endl;
  return 0;
}

bool test_the_pdn()
{
  if (0 != ((pdn[1]*100 + pdn[2] * 10 + pdn[3]) % 2)) {
    return false;
  }
  if (0 != ((pdn[2]*100 + pdn[3] * 10 + pdn[4]) % 3)) {
    return false;
  }
  if (0 != ((pdn[3]*100 + pdn[4] * 10 + pdn[5]) % 5)) {
    return false;
  }
  if (0 != ((pdn[4]*100 + pdn[5] * 10 + pdn[6]) % 7)) {
    return false;
  }
  if (0 != ((pdn[5]*100 + pdn[6] * 10 + pdn[7]) % 11)) {
    return false;
  }
  if (0 != ((pdn[6]*100 + pdn[7] * 10 + pdn[8]) % 13)) {
    return false;
  }
  if (0 != ((pdn[7]*100 + pdn[8] * 10 + pdn[9]) % 17)) {
    return false;
  }
  return true;
}
