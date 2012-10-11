#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <ctype.h>

using namespace std;

int main(int argc, char *argv[])
{
  int sum = 0;
  ifstream is("cipher1.txt");
  vector<int> message;
  int itmp;
  char ctmp;
  is >> itmp;
  while (is) {
    message.push_back((char)itmp);
    is >> ctmp;
    if (',' != ctmp) {
      cout << "!" << (int) ctmp << "!" << itmp << endl;
      break;
    }
    if (!is) {
      cout << "NNN" << endl;
      break;
    }
    is >> itmp;
  }

  ctmp = 'A';
  char ctmp1 = ctmp^0xFF;
  //cout << hex << (int)ctmp << "|" << hex << (int) (ctmp^ctmp1) << endl;

  vector<int> key;
  key.push_back((int)'g');
  key.push_back((int)'o');
  key.push_back((int)'d');

  size_t sz = message.size()/3*3;
  bool bTry;
  int ich;
  /*
  vector<int> key1, key2, key3;
  for (ich = 1; ich < 256; ++ich) {
    bTry = true;
    for (size_t jsz = 0; jsz < sz; jsz += 3) {
      if (!isprint((message[jsz]^ich))) {
        bTry = false;
        break;
      }
    }
    if (bTry) {
      key1.push_back(ich);
      if (isprint(ich)) {
        cout << (char)ich;
      } else {
        cout << dec << ich;
      }
      cout << "->" << (char)(message[0]^ich) << endl;
    }
  }
  cout << "================" << endl;
  for (ich = 1; ich < 256; ++ich) {
    bTry = true;
    for (size_t jsz = 0; jsz < sz; jsz += 3) {
      if (!isprint((message[jsz+1]^ich))) {
        bTry = false;
        break;
      }
    }
    if (bTry) {
      key2.push_back(ich);
      if (isprint(ich)) {
        cout << (char)ich;
      } else {
        cout << dec << ich;
      }
      cout << "->" << (char)(message[1]^ich) << endl;
    }
  }
  cout << "================" << endl;
  for (ich = 1; ich < 256; ++ich) {
    bTry = true;
    for (size_t jsz = 0; jsz < sz; jsz += 3) {
      if (!isprint((message[jsz+2]^ich))) {
        bTry = false;
        break;
      }
    }
    if (bTry) {
      key3.push_back(ich);
      if (isprint(ich)) {
        cout << (char)ich;
      } else {
        cout << dec << ich;
      }
      cout << "->" << (char)(message[2]^ich) << endl;
    }
  }
  cout << "================" << endl;
  for(size_t ksz1 = 0; ksz1 < key1.size(); ++ksz1) {
    for(size_t ksz2 = 0; ksz2 < key2.size(); ++ksz2) {
      for(size_t ksz3 = 0; ksz3 < key3.size(); ++ksz3) {
        cout << (char)key1[ksz1] << "|"
             << (char)key2[ksz2] << "|"
             << (char)key3[ksz3] <<endl;
        for (size_t msz = 0; msz < 54; msz +=3) {
          cout << (char)(message[msz]^key1[ksz1]);
          cout << (char)(message[msz+1]^key2[ksz2]);
          cout << (char)(message[msz+2]^key3[ksz3]);
        }
        cout << endl << "++++++++++++++++++++++++++++++++++" << endl;
      }
    }
  }

  return 0;
  */

  size_t isz;
  sz = message.size()/3*3;
  cout << sz << ":" << message.size() << endl;
  for (isz = 0; isz < sz; isz +=3) {
    sum += (char)(message[isz] ^ key[0]);
    cout << (char)(message[isz] ^ key[0]);
    sum += (char)(message[isz+1] ^ key[1]);
    cout << (char)(message[isz+1] ^ key[1]);
    sum += (char)(message[isz+2] ^ key[2]);
    cout << (char)(message[isz+2] ^ key[2]);
  }
  if (isz < message.size()) {
    sum += (char)(message[isz] ^ key[0]);
    cout << (char)(message[isz] ^ key[0]);
    ++isz;
    if (isz < message.size()) {
      sum += (char)(message[isz] ^ key[1]);
      cout << (char)(message[isz] ^ key[1]);
    }
  }
  //message.push_back((char)itmp);

  //copy(message.begin(), message.end(), ostream_iterator<int>(cout, ", "));


  cout << dec << sum << endl;
  return 0;
}
