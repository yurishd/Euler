#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <set>

using namespace std;

long test_pen_n(set<long> &penNumbers, set<long>::iterator it, size_t N);

int main(int argc, char* argv[])
{
  set<long> penNumbers;
  penNumbers.insert(1);
  penNumbers.insert(5);
  size_t isz_test = 1;
  set<long>::iterator it = penNumbers.begin();
  ++it;
  long smallPenN;
  while (1) {
    //cout << *it << endl;
    smallPenN = test_pen_n(penNumbers, it, isz_test);
    if (0 != smallPenN) {
      cout << "PenB -PenS = " << (*it) - smallPenN << endl;
      cout << "PenB = " << (*it) <<", PenS = " << smallPenN << endl;
      return 0;
    }
    ++isz_test;
    if (isz_test == penNumbers.size()) {
      long tmp = isz_test + 1;
      penNumbers.insert(((3 * tmp - 1) * tmp) / 2);
    }
    ++it;
  }
  cout << "NEVER ENDS" <<  endl;
  return 0;
}

long test_pen_n(set<long> &penNumbers, set<long>::iterator it, size_t N)
{
  set<long>::iterator it_begin = penNumbers.begin();
  set<long>::iterator it_iter = it;
  set<long>::iterator it_tmp;
  size_t N_Save = N;
  do {
    --it_iter;
    if (penNumbers.find((*it) - (*it_iter)) != penNumbers.end()) {
      cout << "Candidates: " << (*it) << ":" << (*it_iter) << endl;

      long boundary = (*it) + (*it_iter);
      size_t sz = penNumbers.size();
      N = N_Save+1;
      long penN = ((3 * N - 1) * N) / 2;
      long penN1 = penN;
      while (penN < boundary) {
        if (N == sz) {
          penNumbers.insert(penN);
          ++sz;
        }
        ++N;
        penN = ((3 * N - 1) * N) / 2;
      }
      penNumbers.insert(penN);
      if (penN == boundary) {
        return (*it_iter);
      }
      cout << "Not: " << N << ":" << penN1 << "|" << penN << ":" << boundary << endl;
    }
  } while(it_begin != it_iter);
  return 0;
}
