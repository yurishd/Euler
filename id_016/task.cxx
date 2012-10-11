#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>

using namespace std;
int const POWER_INPUT = 1000;
//int const POWER_INPUT = 100;
int main(int argc, char *argv[])
{
  deque<int> twoPower1000;
  twoPower1000.push_back(2);
  int curPower = 1;
  int tmpResult=0;
  bool moveOver = false;
  for (curPower = 2; curPower < POWER_INPUT + 1; ++curPower) {
    for (size_t sz = twoPower1000.size() - 1; sz > 0; --sz) {
      tmpResult = twoPower1000[sz]*2;
      if (moveOver) {
        ++tmpResult;
        moveOver = false;
      }
      twoPower1000[sz] = tmpResult % 10;
      if (tmpResult > twoPower1000[sz]) {
        moveOver = true;
      }
    }
    tmpResult = twoPower1000[0]*2;
    if (moveOver) {
      ++tmpResult;
      moveOver = false;
    }
    twoPower1000[0] = tmpResult % 10;
    if (tmpResult > twoPower1000[0]) {
      twoPower1000.push_front(1);
    }
  }
  copy(twoPower1000.begin(),
       twoPower1000.end(), ostream_iterator<long>(cout, ""));
  cout << endl;

  int prevResult, result = 0;
  for (size_t sz = 0; sz < twoPower1000.size(); ++sz) {
    prevResult = result;
    result += twoPower1000[sz];
    if (prevResult > result) {
      cout << "OVERFLOW" << endl;
      return 0;
    }
  }
  cout << "===============================" << endl;
  cout << result << endl;
  return 0;
}
