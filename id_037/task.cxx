#include <iostream>
#include <set>
#include <deque>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char* argv[])
{
  set<long> primes;
  ifstream is("../primes_1mil.txt");
  long tmplong;
  is >> tmplong;
  while (is) {
    primes.insert(tmplong);
    is >> tmplong;
  }
  primes.insert(tmplong);

  long count = 0;
  long sum = 0;
  set<long>::iterator it = primes.begin();
  set<long>::iterator it_end = primes.end();
  deque<long> tmpdeque;
  for (; it != it_end; ++it) {
    long tmp = *it;
    if (tmp < 10) continue;
    //cout << tmp;
    tmpdeque.clear();
    while(tmp > 9) {
      if (primes.find(tmp/10) == it_end) {
        //cout << " ? " << tmp/10;
        break;
      }
      //cout << " ! " << tmp/10 << "-" << tmp % 10;
      tmpdeque.push_front(tmp % 10);
      tmp /= 10;
    }
    if (tmp > 9) {
      //cout << " Failed first round" << endl;
      continue;
    }
    tmpdeque.push_front(tmp);
    //cout << endl;

    long count_tenth = 10;
    long prev = tmpdeque[tmpdeque.size() - 1];
    if (primes.find(prev) == it_end) continue;
    tmpdeque.pop_back();
    while (tmpdeque.size()) {
      prev = prev + tmpdeque[tmpdeque.size() - 1]*count_tenth;
      if (primes.find(prev) == it_end) break;
      count_tenth *= 10;
      tmpdeque.pop_back();
    }
    if (0 == tmpdeque.size()) {
      ++count;
      sum+=*it;
      cout << count << ") " << *it << ":" << sum << endl;
      //} else {
      //  cout << " Failed second round" << endl;
    }
  } 
  cout << count << ":" << sum << endl;
  return 0;
}
