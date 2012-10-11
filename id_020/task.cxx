#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <unistd.h> //exit

using namespace std;

class BigNumber_t
{
public:
  BigNumber_t();
  BigNumber_t(BigNumber_t const &);
  BigNumber_t(int);

  BigNumber_t& operator=(BigNumber_t const &);
  //BigNumber_t& operator=(int);
  BigNumber_t& operator*=(int);

  void print_out(ostream& ) const;
  int get_sum_of_numbers() const;
private:
  deque<int> m_number;
};

ostream& operator<<(ostream&, BigNumber_t const&);
int const FACTN = 100;

int main(int argc, char *argv[])
{
  BigNumber_t bnumber = 1;
  //  cout << bnumber << endl;
  //  BigNumber_t bnumber = 39916800;
  //  bnumber *= 343;
  //  cout << bnumber << endl;
  //  return 0;

  for (int i = 2; i <= FACTN; ++i) {
    bnumber *= i;
    //cout << bnumber << endl;
  }
  cout << bnumber.get_sum_of_numbers() << endl;
  return 0;
}

ostream& operator<<(ostream &os, BigNumber_t const &bn)
{
  bn.print_out(os);
  return os;
}

BigNumber_t::BigNumber_t(int n)
{
  if (n < 0) {
    cout << "MUST BE POSITIVE OR NULL!!!!" << endl;
    exit(0);
  }
  if (0 == n) {
    m_number.push_back(0);
    return;
  }

  while (n > 10) {
    m_number.push_front(n % 10);
    n /= 10;
  }
  if (0 != n) {
    m_number.push_front(n);
  }
}

void BigNumber_t::print_out(ostream &os) const
{
  copy(m_number.begin(), m_number.end(), ostream_iterator<int>(os, ""));
}

int BigNumber_t::get_sum_of_numbers() const
{
  int retValue = 0;
  for (size_t isz = 0; isz < m_number.size(); ++isz) {
    retValue += m_number[isz];
  }
  return retValue;
}

BigNumber_t& BigNumber_t::operator *= (int n)
{
  if (n < 0) {
    cout << "MUST BE POSITIVE OR NULL!!!!" << endl;
    exit(0);
  }
  if (1 == n) {
    return *this;
  }
  if (0 == n) {
    m_number.clear();
    m_number.push_back(0);
    return *this;
  }
  while ((n > 0) && (0 == n % 10)) {
    m_number.push_back(0);
    n /= 10;
  }
  int tmp;
  int tmpResult;
  int moveOver = 0;
  
  size_t nsz = m_number.size();
  deque<int> result;
  //result.push_back(0);
  //size_t rsz = 1;
  size_t rsz = 0;
  size_t irsz;

  int nN = 0;
  //cout << "START " << *this << " *= " << n << endl;
  while (n > 0) {
    //cout << "=============================" << endl << "ITER " << nN << ", " << n << endl;
    tmp = n % 10;
    for (size_t isz = nsz; isz > 0; --isz) {
      tmpResult = tmp * m_number[isz-1];
      //cout << "----------------------"
      //     << endl << tmpResult << " = " << tmp << " * " << m_number[isz-1] << " (" << isz << ")" << endl;
      if (nsz - isz + nN + 1 > rsz) {
        ++rsz;
        result.push_front(0);
        //cout << "Increase result: ";
        //copy(result.begin(), result.end(), ostream_iterator<int>(cout, ""));
        //cout << endl;
      }
      irsz = rsz + isz - nN - nsz - 1;
      //cout << "rsz = " << rsz << ", irsz = " << irsz;
      tmpResult += moveOver;
      moveOver = 0;
      //cout << ",  tmpResult = " << tmpResult << ", mo = " << moveOver << endl;
      result[irsz] += tmpResult;
      if (result[irsz] >= 10) {
        moveOver = result[irsz]/10;
        result[irsz] = result[irsz] % 10;
      }
      //copy(result.begin(), result.end(), ostream_iterator<int>(cout, ""));
      //cout << endl;
    }
    if (moveOver > 0) {
      ++rsz;
      result.push_front(moveOver);
      moveOver = 0;
      //copy(result.begin(), result.end(), ostream_iterator<int>(cout, ""));
      //cout << endl;
    }
    ++nN;
    n /= 10;
  }
  m_number = result;
  return *this;
}
