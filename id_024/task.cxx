#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
////////////////////////////////////////////////////////
// Idea is:
// Number of permutations is n! for "n" symbols
// So, if we need Nth permutation then:
// we do sum (n-1)! + (n-1)!+... up to this sum is less
// then N. Let's assume we did sum K times (n-1)!
// Obviously, K is less then "n" since we have everything
// is equal n! = (n-1)! + (n-1)!+..+(n-1)!
//                |         |         |
//                ---------------------
//                          |
//                       n times
// If we have an array with dimension "n" which
// contains those symbols in lexicographic order
// then the first symbol to output is Kth item
////////////////////////////////////////////////////////
using namespace std;

void init_symbols(deque<int> &symbs, deque<int> &factorials, int &permIndex);

int main(int argc, char *argv[])
{
  deque<int> factorials;
  deque<int> symbs;
  deque<int> result;
  int permIndex;

  init_symbols(symbs, factorials, permIndex);

  cout << "Input:" << endl;
  cout << "Symbs: ";
  copy(symbs.begin(),
       symbs.end(), ostream_iterator<int>(cout, ", "));
  cout << endl;
  cout << "factorials: ";
  copy(factorials.begin(),
       factorials.end(), ostream_iterator<int>(cout, ", "));
  cout << endl;
  cout << "Required permutation index is :" << permIndex << endl;

  deque<int>::iterator symb_it;
  for (size_t i = 0; i < factorials.size()-1; ++i) {
    //Just in case...
    if (permIndex > factorials[i]) {
      cout << "Wow!, Bug, Bug..." << endl;
      return 0;
    }
    if (factorials[i] == permIndex) {
      //Well, it is last permutation that we need
      while (symbs.size() > 0) {
        result.push_back(symbs[symbs.size() - 1]);
        symbs.pop_back();
      }
      //We do not need anything more
      break;
    }
    symb_it = symbs.begin();
    while (permIndex > factorials[i+1]) {
      permIndex -= factorials[i+1];
      ++symb_it;
    }
    //Just in case
    if (symb_it == symbs.end()) {
      //This shouldn't happen since this is
      //the case when factorials[i] == permIndex
      //and we checked it before
      cout << "Wow!, Iterator Bug, Bug..." << endl;
      return 0;
    }
    result.push_back(*symb_it);
    symbs.erase(symb_it);
  }

  cout << "Result: ";
  copy(result.begin(),
       result.end(), ostream_iterator<int>(cout, ""));
  cout << endl;
  return 0;
}

void init_symbols(deque<int> &symbs, deque<int> &factorials, int &permIndex)
{
  int fact = 1;
  for (int i = 0; i < 10; ++i) {
    symbs.push_back(i);
    fact *= (i+1);
    factorials.push_front(fact);
  }
  permIndex = 1000000;
}
