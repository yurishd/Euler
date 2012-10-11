#include <iostream>

using namespace std;


int main(int argc, char*argv[])
{
  long result = 0;
  long prev_test;
  long test;
  long max_count = 0;
  long count;
  for (long sp = 3; sp < 1000000; ++sp) {
    cout << sp << " ";
    test = sp;
    count = 1;
    while (test > 1) {
      if (test & 0x1) {
        prev_test = test;
        test = test*3 + 1;
        if (prev_test > test) {
          cout << "OVERFLOW!!!" << endl;
          return 0;
        }
      } else {
        test = test / 2;
      }
      ++count;
    }
    if (count > max_count) {
      max_count = count;
      result = sp;
    }
    cout << result << ":" << max_count<< endl;
  }
  cout << "result : " << result;
  cout << endl;
  return 0;
}
