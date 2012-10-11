#include <iostream>

using namespace std;

int const F_MAX = 4000000;
int main(int argc, char *argv[])
{
  int sum = 2;
  int prev_sum = 2;
  int f1 = 1;
  int f2 = 2;
  int f3 = 3;

  while (f3 <= F_MAX) {
    if (~f3 & 0x1) {
      prev_sum = sum;
      sum += f3;
      if (sum < prev_sum) {
        cout << "OVERFLOW!!!" << endl;
        return 1;
      }
    }
    f1 = f2;
    f2 = f3;
    f3 = f1 + f2;
  }
  cout << sum << endl;
  return 0;
}
