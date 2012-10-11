#include <iostream>
#include <vector>

int const MAX_NUMBER = 10000000;

using namespace std;

int main(int argc, char *argv[])
{
  int sum = 0;
  vector<int> nums(MAX_NUMBER+1, 0);

  nums[1] = 1;
  nums[89] = 89;
  for (int i = 1; i < MAX_NUMBER; ++i) {
    if (nums[i]) continue;
    int itmp = i;
    while ((itmp != 1) && (itmp != 89)) {
      sum = 0;
      while (itmp > 0) {
        int mod = itmp % 10;
        itmp /= 10;
        sum += (mod*mod);
      }
      itmp = sum;
      if (nums[itmp]) itmp = nums[itmp];
    }
    nums[i] = itmp;
  }
  sum = 0;
  for (size_t isz = 0; isz < nums.size(); ++isz) {
    if (89 == nums[isz]) ++sum;
  }
  cout << sum << endl;
  return 0;
}
