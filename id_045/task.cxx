#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

int main(int argc, char *argv[])
{
  long hindex = 143;
  long pindex = 165;
  long tindex = 285;
  long hN = 40755;
  long pN = 40755;
  long tN = 40755;
  long tmp;
  cout << numeric_limits<long>::max() << endl;
  //return 0;
  while (1) {
    if (hindex > 100000000) {
      cout << "H 100000000!?!" << endl;
      cout << pN << endl;
      return 0;
    }
    ++hindex;
    tmp = (hindex * 2 - 1) * hindex;
    //cout << tmp << endl;
    if (tmp < hN) {
      cout << "H OVERFLOW!?!" << endl;
      return 0;
    }
    hN = tmp;
    while (pN < hN) {
      ++tindex;
      if (tindex & 0x1) {
        tmp = (3*tindex - 1) / 2 * tindex;
      } else {
        tmp = tindex / 2 * (3*tindex - 1);
      }
      if (tmp < pN) {
        cout << "P OVERFLOW!?!" << endl;
        return 0;
      }
      pN = tmp;
    }
    if (pN == hN) {
      while (tN < hN) {
        ++tindex;
        if (tindex & 0x1) {
          tmp = (tindex + 1) / 2 * tindex;
        } else {
          tmp = tindex / 2 * (tindex + 1);
        }
        if (tmp < tN) {
          cout << "T OVERFLOW!?!" << endl;
          return 0;
        }
        tN = tmp;
      }
      if (tN == hN) {
        cout << "hIndex = " << hindex << ", pIndex = " << pindex
             << ", tIndex = " << tindex << endl;
        cout << "NUMBER: " << hN << endl;
        return 0;
      }
    }
  }
  cout << "!?!?!?!?!" <<endl;
  return 0;
}
