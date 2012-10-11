#include <iostream>

using namespace std;

long const SIDE_SIZE = 1001;

int main(int argc, char *argv[])
{
  long result = 1;
  long lastN = SIDE_SIZE*SIDE_SIZE;

  long curSide = 3;
  long curN = 1;
  long prevN = 1;

  long sideNumber = 0;

  while (curN < lastN) {
    ++curN;
    if (curN - prevN == curSide - 1) {
      result += curN;
      prevN = curN;
      if (4 == ++sideNumber) {
        sideNumber = 0;
        curSide += 2;
      }
    }
  }

  cout << result << endl;
  return 0;
}
