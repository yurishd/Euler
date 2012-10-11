#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void set_n_as_vect(int n, vector<int> &out);
void multiply_equal(vector<int> &inout, int n);
void plus_equal(vector<int> &inout, vector<int> const &in);

int const MAX_NUMBER = 1000;
int main(int argc, char *argv[])
{
  vector<int> aresult(10, 0);
  vector<int> atmp(10, 0);

  for (int i = 1; i < MAX_NUMBER+1; ++i) {
    //cout << i << endl << "=====================" << endl;
    //fill(atmp.begin(), atmp.end(), 0);
    set_n_as_vect(i, atmp);
    //copy(atmp.begin(), atmp.end(), ostream_iterator<int>(cout, ""));
    //cout << endl;
    for (int j = 1; j < i; ++j) {
      multiply_equal(atmp, i);
    }
    //copy(atmp.begin(), atmp.end(), ostream_iterator<int>(cout, ""));
    //cout << endl;
    plus_equal(aresult, atmp);
    //copy(aresult.begin(), aresult.end(), ostream_iterator<int>(cout, ""));
    //cout << endl;
  }
  copy(aresult.begin(), aresult.end(), ostream_iterator<int>(cout, ""));
  cout << endl;
  return 0;
}

void set_n_as_vect(int n, vector<int> &out)
{
  size_t index = out.size()-1;
  while (n > 0) {
    out[index] = n % 10;
    if (0 == index) return;
    n /= 10;
    --index;
  }
  do {
    out[index] = 0;
    if (!index) return;
    --index;
  } while(1);
}

void multiply_equal(vector<int> &inout, int n)
{
  size_t sz = inout.size();
  vector<int> atmp(sz, 0);
  size_t dist = 0;
  int multiplier = n % 10;
  n /= 10;
  //cout << "n = " << n << ", mt = " << multiplier
  //     << ", dist = " << dist << endl;
  while (dist < sz) {
    for (size_t jsz = sz - dist; jsz > 0; --jsz) {
      atmp[jsz-1] = multiplier * inout[jsz-1+dist] + atmp[jsz-1];
      if (atmp[jsz-1] > 9) {
        int moveOver = atmp[jsz-1]/10;
        atmp[jsz-1] = atmp[jsz-1] % 10;
        if (jsz > 1) {
          atmp[jsz-2] += moveOver;
        }
      }
    }
    //cout  << "--- " << dist << " --- " << multiplier << endl;
    //copy(atmp.begin(), atmp.end(), ostream_iterator<int>(cout, ""));
    //cout << endl;
    if (0 == n) break;
    multiplier = n % 10;
    n /= 10;
    ++dist;
  }
  inout = atmp;
}

void plus_equal(vector<int> &inout, vector<int> const &in)
{
  size_t sz = inout.size();
  //cout  << "####################" << endl;
  //copy(inout.begin(), inout.end(), ostream_iterator<int>(cout, ""));
  //cout << " + " << endl;
  //copy(in.begin(), in.end(), ostream_iterator<int>(cout, ""));
  //cout << endl;
  for (size_t isz = sz; isz > 0; --isz) {
    inout[isz - 1] = inout[isz - 1] + in[isz - 1];
    //cout << inout[isz - 1] << ",";
    if (inout[isz - 1] > 9) {
      inout[isz - 1] = inout[isz - 1] % 10;
      if (isz > 1) {
        ++inout[isz - 2];
      }
    }
  }
  //cout << endl;
  //copy(inout.begin(), inout.end(), ostream_iterator<int>(cout, ""));
  //cout << endl;
  //cout  << "####################" << endl;
}
