#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <fstream>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
  set<int> tnumbers;
  int tmp;
  for (size_t isz = 1; isz < 1000; ++isz) {
    if (isz & 0x1) {
      tmp = (isz + 1) / 2 * isz;
    } else {
      tmp = isz / 2 * (isz + 1);
    }
    tnumbers.insert(tmp);
  }
  //copy(tnumbers.begin(), tnumbers.end(), ostream_iterator<int>(cout,", "));
  //cout << endl;
  //return 0;
  ifstream is("./words.txt");
  if (!is) {
    cout << "Failed to open file" << endl;
  }

  string words;
  is >> words;
  cout << words << endl;

  int value;
  size_t isz;
  size_t comma_pos_prev = 0;
  size_t comma_pos = words.find(',', comma_pos_prev+1);
  string word = words.substr(comma_pos_prev+1, comma_pos - comma_pos_prev - 2);
  cout
    << comma_pos_prev << ":" << comma_pos
    << "[" << word << "] "
    << endl;

  int result = 0;
  while (string::npos != comma_pos) {

    value = 0;
    for (isz = 0; isz < word.length(); ++isz) {
      value += (word[isz] - 'A') + 1;
    }
    if (tnumbers.find(value) != tnumbers.end()) {
      ++result;
    }

    comma_pos_prev = comma_pos;
    comma_pos = words.find(',', comma_pos_prev+1);
    if (string::npos == comma_pos) {
      cout << "END" << endl;
      break;
    }
    word = words.substr(comma_pos_prev+2, comma_pos - comma_pos_prev - 3);
    cout
      << comma_pos_prev << ":" << comma_pos
      << "[" << word << "]"
      << endl;
  }
  cout << "LAST" << endl;
  word = words.substr(comma_pos_prev+2, words.length() - comma_pos_prev - 3);
  cout
    << comma_pos_prev << ":" << comma_pos
    << "[" << word << "]"
    << endl;

  value = 0;
  for (isz = 0; isz < word.length(); ++isz) {
    value += (word[isz] - 'A') + 1;
  }
  if (tnumbers.find(value) != tnumbers.end()) {
    ++result;
  }
  cout << "RESULT = " << result << endl;
  return 0;
}
