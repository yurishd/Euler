#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int const MAX_P = 998001;
int arr[6] = 
  {
    9,9,8,8,9,9
  };

bool IsOk(int toTest);

int main(int argc, char *argv[])
{
  int start_result = arr[0] * 100000 + arr[1] * 10000 +
    arr[2] * 1000 + arr[3] * 100 + arr[4] * 10 + arr[5];

  int result;
  do {
    if (0 == arr[2]) {
      arr[2] = arr[3] = 9;
      if (0 == arr[1]) {
        arr[1] = arr[4] = 9;
        if (0 == arr[0]) {
          break;
        } else {
          --arr[0];
          --arr[5];
        }
      } else {
        --arr[1];
        --arr[4];
      }
    } else {
      --arr[2];
      --arr[3];
    }
    result = arr[0] * 100000 + arr[1] * 10000 +
    arr[2] * 1000 + arr[3] * 100 + arr[4] * 10 + arr[5];
    if (IsOk(result)) {
      cout << result << endl;
      return 0;
    }
  } while(result > 10000);

  arr[0] = arr[1] = arr[2] = arr[3] = arr[4] = 9;

  do {
    if (0 == arr[2]) {
      arr[2] = 9;
      if (0 == arr[1]) {
        arr[1] = arr[3] = 9;
        if (0 == arr[0]) {
          break;
        } else {
          --arr[0];
          --arr[4];
        }
      } else {
        --arr[1];
        --arr[3];
      }
    } else {
      --arr[2];
    }


    result = arr[0] * 10000 + arr[1] * 1000 +
    arr[2] * 100 + arr[3] * 10 + arr[4];
    if (IsOk(result)) {
      cout << result << endl;
      return 0;
    }
  } while(result > 10000);
  cout << "Failed" << endl;
  return 0;
}

bool test_dividers(vector<int> &dividers);

bool IsOk(int toTest)
{
  int imax = (int)sqrt((double)toTest);
  if (imax < 100) return false;
  if (imax > 999) return false;
  int test2;
  for (int i = 100; i < imax; ++i) {
    test2 = toTest / i;
    if ((test2 <= 999) && (test2 > 100) && (test2 * i == toTest)) {
      cout << i << " * " << test2 << " = ";
      return true;
    }
  }
  return false;
}

bool IsOk1(int toTest)
{
  vector<int> dividers;
  int div = 2;
  while (div < toTest) {
    if (0 == toTest % div) {
      dividers.push_back(div);
      toTest = toTest / div;
    } else {
      ++div;
    }
  }
  dividers.push_back(toTest);
  return test_dividers(dividers);
}

bool test_dividers(vector<int> &dividers)
{
  size_t sz = dividers.size();
  if ((sz < 2) || (dividers[sz-1] > 999)) {
    return false;
  }
  if (2 == sz) {
    return (dividers[0] >= 100) && (dividers[0] <= 999) &&
      (dividers[1] >= 100) && (dividers[1] <= 999);
  }
  return false;
}
