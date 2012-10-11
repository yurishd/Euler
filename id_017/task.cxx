#include <iostream>
#include <string.h>

using namespace std;

char const *units[] = {
  "One",
  "Two",
  "Three",
  "Four",
  "Five",
  "Six",
  "Seven",
  "Eight",
  "Nine"
};


int units_sz[sizeof(units)/sizeof(char const *)];

char const *tens[] = {
  "Ten",
  "Eleven",
  "Twelve",
  "Thirteen",
  "Fourteen",
  "Fifteen",
  "Sixteen",
  "Seventeen",
  "Eighteen",
  "Nineteen"
};
int tens_sz[sizeof(tens)/sizeof(char const *)];

char const *till100[] = {
  "Twenty",
  "Thirty",
  "Forty",
  "Fifty",
  "Sixty",
  "Seventy",
  "Eighty",
  "Ninety"
};
int till100_sz[sizeof(till100)/sizeof(char const *)];

const char *thousand = "one thousand";
int thousand_sz;

int count_letters(int inp);

int main(int argc, char *argv[])
{
  int i;
  thousand_sz = strlen(thousand)-1;
  for (i = 0; i < sizeof(till100)/sizeof(char const *); ++i) {
    till100_sz[i] = strlen(till100[i]);
  }
  for (i = 0; i < sizeof(tens)/sizeof(char const *); ++i) {
    tens_sz[i] = strlen(tens[i]);
  }
  for (i = 0; i < sizeof(units)/sizeof(char const *); ++i) {
    units_sz[i] = strlen(units[i]);
  }


  int result = 0;
  for (i = 1; i < 1001; ++i) {
    result += count_letters(i);
    cout << " : " << result << endl;
  }
  cout << result << endl;
  return 0;
}

int count_letters(int inp)
{
  string strunits;
  string strtens;
  string strhunds;
  int result = 0;
  if (inp == 1000) {
    cout << thousand << thousand_sz;
    return thousand_sz;
  }
  if (inp < 1 || inp > 1000) {
    cout << "BAD NUMBER" << endl;
    return 0;
  }

  int hundred = inp % 100;
  inp = inp / 100;
  if ((hundred > 9) && (hundred < 20)) {
    result += tens_sz[hundred - 10];
    strtens = tens[hundred - 10];
  } else {
    int unit = hundred % 10;
    hundred /= 10;

    if (unit > 0) {
      result += units_sz[unit - 1];
      strunits = units[unit - 1];
    }
    if (hundred > 0) {
      result += till100_sz[hundred - 2];
      strtens = till100[hundred - 2];
    }
  }
  if (inp > 0){
    strhunds = units[inp-1];
    strhunds += " hundred";
    if (result) {//if there are som numbers
      strhunds += " and";
      result += 3; //"and"
    }
    result += 7; //"hundred"
    result += units_sz[inp-1];
  }
  cout << strhunds << (strhunds.length()?" ":"")
       << strtens << (strtens.length()?" ":"")
       << strunits << " = " << result;
  return result;
}
