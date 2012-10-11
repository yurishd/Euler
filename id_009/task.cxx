#include <iostream>

using namespace std;

bool IsOk(int a);

int main(int argc, char *argv[])
{
  int result = 0;
  for (int a = 1; a < 999; ++a) {
    if (IsOk(a)) {
      return 0;
      //cout << a << " * " << b < " * " << c << " = " << a*b*c << endl;
    }
  }
  cout << "NOT FOUND!!!" << endl;
  return 0;
}

bool IsOk(int a)
{
  int lastb = (1000 - a);
  if (lastb & 0x1) {
    lastb = lastb/2 + 1;
  } else {
    lastb = lastb/2;
  }
  int sqa = a*a;
  int c;
  for (int b = a + 1; b < lastb; ++b) {
    c = 1000 - a - b;
    if (sqa + b*b == c*c) {
      cout << a << " * " << b << " * " << c << " = " << a*b*c << endl;
      return true;
    }
  }
  return false;
}

