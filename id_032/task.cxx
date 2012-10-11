#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

long const MAX_CANDIDATE = 98765;
//long const MAX_CANDIDATE = 98593;

bool is_candidate(long test, vector<bool> &numbers);
struct Helper
{
  long m_multiplicand;
  long m_multiplier;

  Helper(long mcand, long mplier) :
    m_multiplicand(mcand), m_multiplier(mplier){}
};

ostream& operator<<(ostream& os, pair<long, Helper> const &pr)
{
  os << pr.first << " = " << pr.second.m_multiplicand
     << " * " << pr.second.m_multiplier;
  return os;
}

int main(int argc, char *argv[])
{
  map<long, Helper> products;
  long test = 123;
  //long test = 98592;
  vector<bool> prod_numbers(10,false);
  while (test <= MAX_CANDIDATE) {
    //cout << test << endl << "-------" << endl;
    if (is_candidate(test, prod_numbers)) {
      //cout << test << "<=>";
      vector<bool> mcand_numbers(prod_numbers);
      long mcand_max = test/2;
      long mcand = 2;
      while (mcand < mcand_max) {
        if (0 == test % mcand) {
          if (is_candidate(mcand, mcand_numbers)) {
            //cout << mcand << "<*>";
            long mplier = test / mcand;
            if (is_candidate(mplier, mcand_numbers)) {
              //cout << mplier << endl;
              bool byes = true;
              for (int i = 1; i < 10; ++i) {
                if (!mcand_numbers[i]) {
                  byes = false;
                }
              }
              if (byes) {
                products.insert(pair<long,Helper>(test, Helper(mcand, mplier)));
                break;
              }
            }
            mcand_numbers = prod_numbers;
          }
        }
        ++mcand;
      }
      //cout << endl;
      bool new_value = false;
      fill(prod_numbers.begin(), prod_numbers.end(), new_value);
      //copy(prod_numbers.begin(), prod_numbers.end(), ostream_iterator<bool>(cout, ", "));
      //cout << endl;
    }
    ++test;
  }
  cout << "==================================" << endl;
  //copy(prod_numbers.begin(), prod_numbers.end(), ostream_iterator<map<long, Helper>::iterator >(cout, "\n"));
  //  /*
  map<long, Helper>::iterator it = products.begin();
  map<long, Helper>::iterator it_end = products.end();
  long result = 0;
  while (it != it_end) {
    cout << *it << " - " << result << endl;
    if (result > result + it->first) {
      cout << "OVERFLOW!!!" << endl;
      return 0;
    }
    result = result + it->first;
    ++it;
  }
  //*/
  cout << endl << "==================================" << endl;
  cout << result << endl;
  return 0;
}

bool is_candidate(long test, vector<bool> &numbers)
{
  vector<bool> vtmp(numbers);
  bool retValue = true;
  if (numbers.size() < 10) {
    return false;
  }
  if (test > MAX_CANDIDATE) {
    return false;
  }
  while (test > 9) {
    long tmp = test % 10;
    if (0 == tmp) {
      retValue = false;
      break;
    }
    if (vtmp[tmp]) {
      retValue = false;
      break;
    }
    vtmp[tmp] = true;
    test /= 10;
  }
  if (retValue) {
    if (vtmp[test]) {
      return false;
    }
    vtmp[test] = true;
    numbers = vtmp;
    //cout << "is_candidate" << endl;
    //copy(numbers.begin(), numbers.end(), ostream_iterator<bool>(cout, ", "));
    //cout << endl << "#######" << endl;
  }
  return retValue;
}

