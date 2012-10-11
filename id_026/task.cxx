#include <iostream>
//#include <map>

using namespace std;

int const MAX_NUMBER = 1000;
int main(int argc, char *argv[])
{
  int aRecurr[MAX_NUMBER];
  int maxRecurringsV = 0;
  int maxRecurringsN = 0;
  //map<int, int> recurrings;
  for (int i = 1; i < MAX_NUMBER; ++i) {
    memset(aRecurr, 0, sizeof(int)*MAX_NUMBER);
    int numerator = 1;
    int recurr_i = 0;
    while (numerator) {
      ++recurr_i;
      if (numerator >= i) {
        numerator = numerator % i;
        if (aRecurr[numerator]) {
          int tmp = recurr_i - aRecurr[numerator];
          if (tmp > maxRecurringsN) {
            maxRecurringsN = tmp;
            maxRecurringsV = i;
          }
          break;
        } else {
          aRecurr[numerator] = recurr_i;
        }
      }
      numerator *= 10;
    }
  }


  cout << "Value " << maxRecurringsV << ", N " << maxRecurringsN << endl;
  return 0;
}
