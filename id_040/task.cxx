#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
long const MAX_DIG_N = 10000000;
void build_digit_numbers(vector<long>&, long MaxN);
long digit(long digitIndex, vector<long> const &digit_numbers);

int main(int argc, char *argv[])
{
  long result = 0;
  vector<long> digitN;
  build_digit_numbers(digitN, MAX_DIG_N);

  copy(digitN.begin(),
       digitN.end(), ostream_iterator<long>(cout, "\n"));
  


  cout << "==========" << endl;

  
  result = 
    digit(1, digitN)*
    digit(10, digitN)*
    digit(100, digitN)*
    digit(1000, digitN)*
    digit(10000, digitN)*
    digit(100000, digitN)*
    digit(1000000, digitN);
  cout << result << endl;
  
  return 0;
}

void build_digit_numbers(vector<long> &digitsN, long MaxN)
{
  long tenth = 10;
  long round = 1;
  for (long i = 1; i < MaxN+1; ++i) {
    if (i == tenth) {
      digitsN.push_back((i - tenth/10) * round);
      tenth *= 10;
      ++round;
    }
  }
}

long digit(long digitIndex, vector<long> const &digit_numbers)
{
  long TheNumber = 0;
  if (0 == digitIndex) return -1;
  cout << "Input: " << digitIndex
         << endl;
  for (size_t i = 0; i < digit_numbers.size(); ++i) {

    if (digitIndex > digit_numbers[i]) {
      TheNumber += digit_numbers[i] / (i+1);
      digitIndex -= digit_numbers[i];
      continue;
    }

    cout << "digitIndex: " << digitIndex
         << ", digit_numbers[i] :" << digit_numbers[i]
         << ", (i+1): " << (i+1)
         << ", digitIndex/(i+1) :" << digitIndex/(i+1)
         << "TheNumber: " << TheNumber
         << endl;
 
    TheNumber = TheNumber + digitIndex/(i+1);
    digitIndex = digitIndex % (i+1);
    if (digitIndex > 0) {
      ++TheNumber;
      digitIndex = (i+1) - digitIndex;
    }
    cout << "TheNumber: " << TheNumber
         << "  digitIndex: " << digitIndex
         << endl;
    while (digitIndex-- > 0) {
      TheNumber /= 10;
    }
    cout << "RetValue: " << TheNumber % 10 << endl;
    return TheNumber % 10;
  }
  return -1;
}
