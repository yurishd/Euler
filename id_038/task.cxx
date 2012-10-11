#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>

using namespace std;

int pdn [9] = {
  9, 8, 7, 6, 5, 4, 3, 2, 1
};

bool iterate(long theN, long multiplier, int nums[], int numsSize,
             deque<long> &debug);

int main(int argc, char* argv[])
{
  deque<long> debug;
  bool bFound = false;
  do {
    long test = 0;
    for (int i = 0; i < 4; ++i) {
      test = test * 10 + pdn[i];
      debug.clear();
      debug.push_back(test);
      if (iterate(test, test, pdn + i + 1, 9 - i - 1, debug)) {
        cout << "result: ";
        copy(pdn, pdn+9, ostream_iterator<long>(cout, ""));
        cout << endl;
        copy(debug.begin(), debug.end(), ostream_iterator<long>(cout, ", "));
        cout << endl;
        bFound = true;
        break;
      }
    }
    if (bFound) break;
  } while (prev_permutation(pdn, pdn + 9));
  cout << "DONE" << endl;
  return 0;
}

bool iterate(long theN, long multiplier, int *nums, int numsSize,
             deque<long> &debug)
{
  long newNumber = theN+multiplier;
  if (!newNumber) return false;

  long newNumberSave = newNumber;
  deque<long> newNums;
  while (newNumber > 0) {
    newNums.push_front(newNumber % 10);
    newNumber /= 10;
  }
  if ((int)newNums.size() <= numsSize) {
    size_t isz = 0;
    for (; isz < newNums.size(); ++isz) {
      if (newNums[isz] != nums[isz]) {
        break;
      }
    }
    if (isz == newNums.size()) {
      if (newNums.size() < numsSize) {
        if(!iterate(newNumberSave, multiplier,
                    nums + newNums.size(), numsSize - newNums.size(), debug)) {
          return false;
        }
      }
      debug.push_back(newNumberSave);
      return true;
    }
  }
  return false;
}
