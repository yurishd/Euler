#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <fstream>
#include <set>

using namespace std;

void increment(vector<long> &theNumberD);
bool multiply(vector<long> &theNumberD, long N);

bool test_on_ok(vector<long> const &theNumberD,
                vector<int> const &testDig,
                long multiplier,
                vector<long> &debug);

int main(int argc, char *argv[])
{
  vector<long> theNumberD(1,0);
  vector<long> tmp2;
  vector<long> tmp3;
  vector<long> tmp4;
  vector<long> tmp5;
  vector<long> tmp6;

  vector<int> test(10, 0);
  long prev = 0;
  long iter = 0;
  size_t isz;
  while (1) {
    ++iter;
    if (prev > iter) {
      cout << "OVERFLOW!?!?!?!?!?!" <<endl;
      return 0;
    }
    //if (iter % 10000 == 0) {
    //  cout << iter << endl;
    //}
    if (iter > 200000) {
      cout << "LIMIT!?!?!?!?!?!" <<endl;
      return 0;
    }
    prev = iter;
    increment(theNumberD);
    //if (1 != theNumberD[theNumberD.size() - 1]) continue;
    for (isz = 0; isz < 10; ++isz) {
      test[isz] = 0;
    }
    for (isz = 0; isz < theNumberD.size(); ++isz) {
      ++test[theNumberD[isz]];
    }
    if (
        test_on_ok(theNumberD, test, 6, tmp2) &&
        test_on_ok(theNumberD, test, 5, tmp3) &&
        test_on_ok(theNumberD, test, 4, tmp4) &&
        test_on_ok(theNumberD, test, 3, tmp5) &&
        test_on_ok(theNumberD, test, 2, tmp6)
        ) {

      cout << "RESULT!! = " << iter << endl;
      copy(theNumberD.rbegin(), theNumberD.rend(),
           ostream_iterator<long>(cout, ""));
      cout << endl;
      copy(tmp2.rbegin(), tmp2.rend(), ostream_iterator<long>(cout, ""));
      cout << endl;
      copy(tmp3.rbegin(), tmp3.rend(), ostream_iterator<long>(cout, ""));
      cout << endl;
      copy(tmp4.rbegin(), tmp4.rend(), ostream_iterator<long>(cout, ""));
      cout << endl;
      copy(tmp5.rbegin(), tmp5.rend(), ostream_iterator<long>(cout, ""));
      cout << endl;
      copy(tmp6.rbegin(), tmp6.rend(), ostream_iterator<long>(cout, ""));
      cout << endl;
      return 0;
    }
  }
  long result = 0;
  cout << "RESULT = " << result << endl;
  return 0;
}

void increment(vector<long> &theNumberD)
{
  size_t isz = 0;
  ++theNumberD[0];
  while (1) {
    if (theNumberD[isz] < 10) {
      break;
    }
    theNumberD[isz] = 0;
    if (isz + 1 == theNumberD.size()) {
      theNumberD.push_back(0);
    }
    ++isz;
    ++theNumberD[isz];
  }
}

bool multiply(vector<long> &theNumberD, long N)
{
  if (N > 9) return false;
  long moveOver = 0;
  for (size_t isz = 0; isz < theNumberD.size(); ++isz) {
    theNumberD[isz] = theNumberD[isz] * N + moveOver;
    moveOver = theNumberD[isz] / 10;
    if (theNumberD[isz] > 9) {
      theNumberD[isz] = theNumberD[isz] % 10;
    }
  }
  if (moveOver > 0) return false;
  return true;
}

bool test_on_ok(vector<long> const &theNumberD, vector<int> const &testDig,
                long multiplier, vector<long> &debug)
{
  vector<long> tmp = theNumberD;
  if (!multiply(tmp, multiplier)) {
    if (multiplier < 6) {
      cout << "*? ";
      copy(tmp.rbegin(),tmp.rend(),
           ostream_iterator<long>(cout,""));
      cout << endl;
    }
    return false;
  }
  vector<int> testtmp = testDig;
  size_t isz;
  for (isz = 0; isz < tmp.size(); ++isz) {
    if (!testtmp[tmp[isz]]) {
      if (multiplier < 6) {
        cout << "n? ";
        copy(tmp.rbegin(),tmp.rend(),
             ostream_iterator<long>(cout,""));
        cout << endl;
      }
      return false;
    }
    --testtmp[tmp[isz]];
  }
  debug = tmp;
  //if (multiplier < 5) {
    copy(theNumberD.rbegin(),theNumberD.rend(),
         ostream_iterator<long>(cout,""));
    cout << "  PASSED " << multiplier << endl;
    copy(tmp.rbegin(),tmp.rend(),
         ostream_iterator<long>(cout,""));
    cout << endl;
    //}
  return true;
}
