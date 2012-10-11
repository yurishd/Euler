#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void increment(vector<long> &theNumberD);

int main(int argc, char *argv[])
{
  vector<long> factorials;
  factorials.push_back(1);//0!
  factorials.push_back(1);//1!
  factorials.push_back(2);//2!
  factorials.push_back(6);//3!
  factorials.push_back(24);//4!
  factorials.push_back(120);//5!
  factorials.push_back(720);//6!
  factorials.push_back(5040);//7!
  factorials.push_back(40320);//8!
  factorials.push_back(362880);//9!

  copy(factorials.begin(), factorials.end(),
       ostream_iterator<long>(cout, ""));
  cout << endl;
  vector<long> theNumberD(1,0);
  increment(theNumberD);
  increment(theNumberD);
  long result = 0;
  for (long i = 3; i < 3000000; ++i) {
    increment(theNumberD);
    long tmpResult = 0;
    for (size_t isz = 0; isz < theNumberD.size(); ++isz) {
      tmpResult += factorials[theNumberD[isz]];
    }
    //cout << "i = " << i << ", sz = " 
    //     << theNumberD.size() << ", r = " << tmpResult << endl;
    //copy(theNumberD.begin(), theNumberD.end(),
    //     ostream_iterator<long>(cout, ""));
    //cout << endl;
    if (i == tmpResult) {
      result += i;
    cout << "i = " << i << ", sz = " 
         << theNumberD.size() << ", r = " << tmpResult << endl;
    copy(theNumberD.begin(), theNumberD.end(),
         ostream_iterator<long>(cout, ""));
    cout << endl;
    }
  }
  cout << "=================================" << endl;
  copy(factorials.begin(), factorials.end(),
       ostream_iterator<long>(cout, ", "));
  cout << endl;
  cout << result << endl;
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
