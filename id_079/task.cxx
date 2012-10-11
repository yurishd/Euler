#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;


struct Location_t
{
  set<int> m_beforeMe;
  set<int> m_afterMe;
  bool m_active;

  Location_t() : m_active(false) {}
};

ostream& operator<<(ostream &os, Location_t const &lc);

int find_no_before(deque<Location_t> const &supp);
void remove_number(deque<Location_t>  &supp, int theNumber);

int main(int argc, char *argv[])
{
  long tmp;
  vector<long> passcode_d;

  ifstream is("./keylog.txt");
  is >> tmp;
  while (is) {
    passcode_d.push_back(tmp);
    is >> tmp;
  }
  passcode_d.push_back(tmp);

  copy(passcode_d.begin(), passcode_d.end(), ostream_iterator<long>(cout,", "));
  cout << endl;

  deque<Location_t> supp(10);
  vector<int> atmp(3);

  size_t sz = passcode_d.size();

  for (size_t isz = 0; isz < sz; ++isz) {
    tmp = passcode_d[isz];
    atmp[2] = tmp % 10;
    tmp /= 10;
    atmp[1] = tmp % 10;
    tmp /= 10;
    atmp[0] = tmp % 10;
    
    supp[atmp[0]].m_active = true;
    supp[atmp[0]].m_afterMe.insert(atmp[1]);
    supp[atmp[0]].m_afterMe.insert(atmp[2]);
    supp[atmp[2]].m_active = true;
    supp[atmp[2]].m_beforeMe.insert(atmp[0]);
    supp[atmp[2]].m_beforeMe.insert(atmp[1]);
    supp[atmp[1]].m_active = true;
    supp[atmp[1]].m_afterMe.insert(atmp[2]);
    supp[atmp[1]].m_beforeMe.insert(atmp[0]);
  }

  deque<int> result;

  for (int i = 0; i < 10; ++i) {
    cout << i << ": " << supp[i] << endl;
  }
  
  int itmp = find_no_before(supp);

  while (itmp >= 0) {
    result.push_back(itmp);
    remove_number(supp, itmp);
    itmp = find_no_before(supp);
  }
  cout << "=================" << endl;
  for (int i = 0; i < 10; ++i) {
    cout << i << ": " << supp[i] << endl;
  }
  cout << "=================" << endl;
  copy(result.begin(), result.end(), ostream_iterator<long>(cout,""));
  cout << endl << "DONE:" << endl;
  return 0;
}

ostream& operator<<(ostream &os, Location_t const &lc)
{
  if (lc.m_active) {
    os << "bf <";
    copy(lc.m_beforeMe.begin(), lc.m_beforeMe.end(), ostream_iterator<int>(cout, ", "));
    os << ">, af <";
    copy(lc.m_afterMe.begin(), lc.m_afterMe.end(), ostream_iterator<int>(cout, ", "));
    os << ">";
  } else {
    cout << "---";
  }
 return os;
}

int find_no_before(deque<Location_t> const &supp)
{
  for (int i = 0; i < 10; ++i) {
    if (supp[i].m_active && (supp[i].m_beforeMe.size() == 0)) {
      return i;
    }
  }
  return -1;
}

void remove_number(deque<Location_t> &supp, int theNumber)
{
  supp[theNumber].m_active = false;
  for (int i = 0; i < 10; ++i) {
    if (supp[i].m_active) {
      set<int>::iterator it = supp[i].m_beforeMe.find(theNumber);
      if (it != supp[i].m_beforeMe.end()) {
        supp[i].m_beforeMe.erase(it);
      }
      it = supp[i].m_afterMe.find(theNumber);
      if (it != supp[i].m_afterMe.end()) {
        supp[i].m_afterMe.erase(it);
      }
    }
  }
}
