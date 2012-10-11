#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

class BigNumber_t
{
public:
  BigNumber_t();
  BigNumber_t(BigNumber_t const &);
  BigNumber_t(int);

  BigNumber_t& operator=(BigNumber_t const &);
  BigNumber_t& operator=(int);

  BigNumber_t& operator+=(BigNumber_t const &);

  void print_out(ostream& ) const;

  size_t get_num_of_digits() const;

  void reverse_digits();
  bool is_palindromic() const;

  //int get_sum_of_numbers() const;
private:
  deque<int> m_number;
};

ostream& operator<<(ostream &os, BigNumber_t const &bn);

int main(int argc, char *argv[])
{
  BigNumber_t BN1;
  BigNumber_t BN2;
  //BigNumber_t tmpBN;

  int count = 0;
  int othercount = 0;
  int i = 0;
  bool isLychrel;
  while (i < 10000) {
    BN1 = i;
    BN2 = BN1;
    BN2.reverse_digits();
    //cout << BN1 << ":" << BN2 << endl << "========" << endl;
    isLychrel = true;
    for (int ii = 0; ii < 50; ++ii) {
      BN1 += BN2;
      //cout << BN1 << endl;
      if (BN1.is_palindromic()) {
        isLychrel = false;
        //cout << BN1 << " !!FAILED" << endl;
        break;
      }
      BN2 = BN1;
      BN2.reverse_digits();
      //cout << BN1 << ":" << BN2 << endl;
    }
    if (isLychrel) {
      ++count;
      cout << i << endl;
    } else {
      ++othercount;
    }
    ++i;
  }
  cout << count << ":" << othercount << ":" << othercount + count << endl;
  return 0;
}

ostream& operator<<(ostream &os, BigNumber_t const &bn)
{
  bn.print_out(os);
  return os;
}

BigNumber_t::BigNumber_t()
{
  m_number.push_back(0);
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

BigNumber_t& BigNumber_t::operator = (BigNumber_t const & from)
{
  m_number = from.m_number;
  return *this;
}

BigNumber_t& BigNumber_t::operator=(int i)
{
  m_number.clear();
  while(i > 9) {
    m_number.push_front(i % 10);
    i /= 10;
  }
  m_number.push_front(i);
  return *this;
}

BigNumber_t& BigNumber_t::operator+=(BigNumber_t const & from)
{
  while (from.m_number.size() > m_number.size()) {
    m_number.push_front(0);
  }
  size_t my_isz = m_number.size();
  bool moveOver = false;
  //cout << *this << " += " << from << " => ";
  
  for (size_t isz = from.m_number.size(); isz > 0; ) {
    --isz;
    --my_isz;
    m_number[my_isz] += from.m_number[isz];
    if (moveOver) {
      ++m_number[my_isz];
      moveOver = false;
    }
    if (m_number[my_isz] > 9) {
      m_number[my_isz] -= 10;
      moveOver = true;
    }
  }
  if (moveOver) {
    while (my_isz) {
      ++m_number[--my_isz];
      if (m_number[my_isz] < 10) {
        moveOver = false;
        break;
      }
      m_number[my_isz] -= 10;
      if (0 == my_isz) {
        cout << "SCREAMSCREAMSCREAMSCREAM" << endl;
        exit(0);
      }
    }
    if (moveOver) {
      m_number.push_front(1);
    }
  }
  //cout << *this << endl;
  return *this;
}

size_t BigNumber_t::get_num_of_digits() const
{
  return m_number.size();
}

void BigNumber_t::reverse_digits()
{
  size_t sz = m_number.size();
  int tmp;
  for (size_t ssz = 0, fsz = sz - 1; ssz < sz / 2; ++ssz, --fsz) {
    tmp = m_number[ssz];
    m_number[ssz] = m_number[fsz];
    m_number[fsz] = tmp;
  }
}

bool BigNumber_t::is_palindromic() const
{
  size_t sz = m_number.size();
  for (size_t ssz = 0, fsz = sz - 1; ssz < sz / 2; ++ssz, --fsz) {
    if (m_number[ssz] != m_number[fsz]) {
      return false;
    }
  }
  return true;
}

//int BigNumber_t::get_sum_of_numbers() const
//{
//  int retValue = 0;
//  for (size_t isz = 0; isz < m_number.size(); ++isz) {
//    retValue += m_number[isz];
//  }
//  return retValue;
//}

