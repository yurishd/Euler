#include <iostream>

using namespace std;

long g_result = 0;
long LAST_NUMBER = 101;

int main(int argc, char *argv[])
{
  long helper = 3;
  long result = 4;
  for (long i = 3; i < LAST_NUMBER; ++i) {
    result += 2 * i * helper;
    helper += i;
  }
  cout << result << endl;;
  return 0;
}
