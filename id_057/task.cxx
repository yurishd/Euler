#include <iostream>
#include <vector>

int const MAX_NUMBER = 1000;

using namespace std;

struct square_t
{
  vector<int> m_numerator;
  vector<int> m_denominator;

  square_t();
  void nex_iter();

  bool isNumDigMoreThenDen();
};

int main(int argc, char *argv[])
{
  int sum = 0;
  square_t sq;
  for (int i = 1; i < MAX_NUMBER; ++i) {
    sq.nex_iter();
    if (sq.isNumDigMoreThenDen()) ++sum;
  }
  cout << sum << endl;
  return 0;
}

square_t::square_t()
{
  m_numerator.push_back(1);
  m_denominator.push_back(2);
}

void square_t::nex_iter()
{
  vector<int> atmp;
  int moveOver = 0;
  int tmp;

  size_t isz;
  for (isz = 0; isz < m_denominator.size(); ++isz) {
    tmp = m_denominator[isz]*2 + moveOver;
    if (isz < m_numerator.size()) {
      tmp += m_numerator[isz];
    }
    atmp.push_back(tmp % 10);
    moveOver = tmp / 10;
  }
  if (isz < m_numerator.size()) {
    moveOver += m_numerator[isz];
  }
  if (moveOver > 0) {
    atmp.push_back(moveOver);
  }
  m_numerator = m_denominator;
  m_denominator = atmp;
}

bool square_t::isNumDigMoreThenDen()
{
  int moveOver = 0;
  int itmp;
  size_t sz_max = m_numerator.size();
  if (m_denominator.size() > sz_max) {
    sz_max = m_denominator.size();
  }
  for (size_t isz = 0; isz < sz_max; ++isz) {
    itmp = moveOver;
    if (isz < m_numerator.size()) {
      itmp += m_numerator[isz];
    }
    if (isz < m_denominator.size()) {
      itmp += m_denominator[isz];
    }
    moveOver = itmp / 10;
  }
  if (moveOver > 0) return true;
  return false;
}
