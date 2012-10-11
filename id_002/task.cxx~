#include <iostream>
#include <vector>

int const NATURAL_SET = 1000;

int const DIVIDER_1=3;
int const DIVIDER_2=5;

using namespace std;

void init(vector<int> *pArrToInit)
{
  pArrToInit->clear();
  pArrToInit->push_back(DIVIDER_1);
  pArrToInit->push_back(DIVIDER_2);
}

int main(int argc, char *argv[])
{
  int sum = 0;
  vector<int> dividers;
  init(&dividers);
  for (int i = 1; i < NATURAL_SET; ++i) {
    for (size_t j = 0; j < dividers.size(); ++j){
      if (0 == i % dividers[j]) {
        sum += i;
        break;
      }
    }
  }
  cout << sum << endl;
  return 0;
}
