#include <iostream>
#include <set>
#include <deque>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;
int const START_I = 3;
int const END_I = 1000;

bool build_integral_solution(int prmtr, int a, int *pb, int *pc);

int main(int argc, char* argv[])
{
  int prmtrMax = 0;
  int solMax = 0;
  for (int prmtr = START_I; prmtr < END_I; ++prmtr) {
    int b,c;
    int tmpSol = 0;
    for (int a = 1; a < prmtr - 2; ++a) {
      if (build_integral_solution(prmtr, a, &b, &c)) {
        cout << prmtr << "=" << a << "+"<< b << "+" << c
             << "  |  " << a*a << "+" << b*b << "=" << c*c << endl;
        ++tmpSol;
      }
    }
    if (tmpSol > solMax) {
      solMax = tmpSol; 
      prmtrMax = prmtr;
    }
  }
  cout << prmtrMax << ":" << solMax << endl;
  return 0;
}

bool build_integral_solution(int prmtr, int a, int *pb, int *pc)
{
  int tmp1 = prmtr * (prmtr - 2*a);
  int tmp2 = 2 * (prmtr - a);

  if (0 == tmp1 % tmp2) {
    *pb = tmp1 / tmp2;
    *pc = prmtr - a - *pb;
    if ((*pb > 0) && (*pc > 0)) {
      return true;
    }
  }
  return false;
}
