#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct summator_t
{
  size_t m_sum;
  size_t m_index;
  summator_t() : m_sum(0), m_index(0) {}
  void operator ()(std::pair<string, size_t> const& it)
  {
    ++m_index;
    switch (m_index) {
    case 937:
    case 938:
    case 939:
      cout << m_index << ": " << it.first << ":" << it.second << endl;
    }
    size_t sum = m_sum + it.second * m_index;
    if(m_sum > sum) {
      cout << "OVERFLOW!?!?!";
      exit(0);
    }
    m_sum = sum;
  }
};

int main(int argc, char *argv[])
{
  ifstream is("./names.txt");
  if (!is) {
    cout << "Failed to open file" << endl;
  }

  string names;
  is >> names;
  cout << names << endl;

  size_t value;
  size_t isz;
  map<string, size_t> snames;
  size_t comma_pos_prev = 0;
  size_t comma_pos = names.find(',', comma_pos_prev+1);
  string name = names.substr(comma_pos_prev+1, comma_pos - comma_pos_prev - 2);
  cout
    << comma_pos_prev << ":" << comma_pos
    << "[" << name << "] "
    << endl;
  while (string::npos != comma_pos) {

    value = 0;
    for (isz = 0; isz < name.length(); ++isz) {
      value += (name[isz] - 'A') + 1;
    }
    if (snames.find(name) != snames.end()) {
      cout << "SCREAMSCREAMSCREAMSCREAMSCREAM" << endl;
    }
    snames[name] = value;

    comma_pos_prev = comma_pos;
    comma_pos = names.find(',', comma_pos_prev+1);
    if (string::npos == comma_pos) {
      cout << "END" << endl;
      break;
    }
    name = names.substr(comma_pos_prev+2, comma_pos - comma_pos_prev - 3);
    cout
      << comma_pos_prev << ":" << comma_pos
      << "[" << name << "]"
      << endl;
  }
  cout << "LAST" << endl;
  name = names.substr(comma_pos_prev+2, names.length() - comma_pos_prev - 3);
  cout
    << comma_pos_prev << ":" << comma_pos
    << "[" << name << "]"
    << endl;

  value = 0;
  for (isz = 0; isz < name.length(); ++isz) {
    value += (name[isz] - 'A') + 1;
  }
  if (snames.find(name) != snames.end()) {
    cout << "SCREAMSCREAMSCREAMSCREAMSCREAM" << endl;
  }
  snames[name] = value;

  cout << for_each(snames.begin(), snames.end(), summator_t()).m_sum << endl;
  return 0;
}
