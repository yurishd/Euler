#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
  long result = 0;
  long MAX_NUMBER = 6 * (long)pow(9,5);
  long MIN_NUMBER = (long)pow(2,5);
  for (long i = MIN_NUMBER; i <= MAX_NUMBER; ++i) {
    long test = i;
    long digit;
    long tmpsum = 0;
    while (test > 0) {
      digit = test % 10;
      tmpsum += (long)pow(digit,5);
      test /= 10;
    }
    if (tmpsum == i) {
      cout << i << endl;
      result += i;
    }
  }
  cout << MIN_NUMBER << "/" << MAX_NUMBER
       << endl << result << endl;
  return 0;
}
