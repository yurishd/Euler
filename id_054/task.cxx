#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;

typedef enum {
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE
} CardValue_t;

typedef enum {
  H,
  D,
  S,
  C
} CardColor_t;

struct Card_t
{
  CardValue_t m_cardValue;
  CardColor_t m_cardColor;

  bool m_valid;
  Card_t(): m_cardValue(TWO), m_cardColor(H), m_valid(false){}

  bool operator>(Card_t const &other) const
  {
    return (m_cardValue > other.m_cardValue);
  }
  bool operator<(Card_t const &other) const
  {
    return (other.m_cardValue > m_cardValue);
  }
  bool operator==(Card_t const &other) const
  {
    return (m_cardValue == other.m_cardValue);
  }
};

enum {
  HIGH_CARD = 0,
  ONE_PAIR,
  TWO_PAIRS,
  THREE_KIND,
  STRAIGHT,
  FLUSH,
  FULL_HOUSE,
  FOUR_KIND,
  STRAIGHT_FLUSH,
  ROYAL_FLUSH
};

struct Hand_t
{
  vector<Card_t> m_cards;

  bool is_valid() const;

  Hand_t() : m_cards(5) { }

  bool operator>(Hand_t const &);

  int get_rank(vector<int> &add_info) const;

  bool is_straight() const;
  bool is_flush() const;

  int kind(vector<int> &add_info) const;
};

istream& operator>>(istream &is, Card_t &card);
istream& operator>>(istream &is, Hand_t &hand);

ostream& operator<<(ostream &os, Card_t const &card);
ostream& operator<<(ostream &os, Hand_t const &hand);

int main(int argc, char *argv[])
{
  Hand_t Player1, Player2;
  int p1win_count = 0;

  ifstream is("./poker.txt");
  int i;
  string strtmp;
  int count = 0;
  while (is) {
    getline(is, strtmp);
    if (is.eof()) {
      break;
    }
    istringstream iss(strtmp);
    iss >> Player1;
    if (!Player1.is_valid()) {
      cout << "1 FAILED READ" << endl;
      return 0;
    }
    iss >> Player2;
    if (!Player2.is_valid()) {
      cout << "1 FAILED READ" << endl;
      return 0;
    }
    if (Player1 > Player2) {
      ++p1win_count;
      cout << setw(3) << count << ")+ " << Player1 << " | " << Player2 << endl;
    } else {
      cout << setw(3) << count << ")- " << Player1 << " | " << Player2 << endl;
    }
    ++count;
    //cout << Player1 << " " << Player2 << endl;
  }

  cout << endl << "DONE: " << p1win_count << endl;
  return 0;
}

istream& operator>>(istream &is, Card_t &card)
{
  string str;
  is >> str;
  //cout << "INPUT: " << str << endl;
  bool bGood = true;
  char ch = '-';
  if (str.length() == 2) {
    switch(str[0]){
    default:
      cout << "NOT GOOD <" << str[0] << ">" << endl;
      bGood = false;
      break;
    case '2':
      card.m_cardValue = TWO;
      break;
    case '3':
      card.m_cardValue = THREE;
      break;
    case '4':
      card.m_cardValue = FOUR;
      break;
    case '5':
      card.m_cardValue = FIVE;
      break;
    case '6':
      card.m_cardValue = SIX;
       break;
   case '7':
      card.m_cardValue = SEVEN;
      break;
    case '8':
      card.m_cardValue = EIGHT;
      break;
    case '9':
      card.m_cardValue = NINE;
      break;
    case 'T':
      card.m_cardValue = TEN;
      break;
    case 'J':
      card.m_cardValue = JACK;
      break;
    case 'Q':
      card.m_cardValue = QUEEN;
      break;
    case 'K':
      card.m_cardValue = KING;
      break;
    case 'A':
      card.m_cardValue = ACE;
      break;
    }
   if (bGood) {
     ch = str[1];
   }
  }
  if (bGood) {
    switch (ch) {
    default:
      bGood = false;
      break;
    case 'H':
      card.m_cardColor = H;
      break;
    case 'D':
      card.m_cardColor = D;
      break;
    case 'S':
      card.m_cardColor = S;
      break;
    case 'C':
      card.m_cardColor = C;
      break;
    }
  };
  if (!bGood) {
    cout << "NOT GOOD " << ch << endl;
  }
  card.m_valid = bGood;
  return is;
}

ostream& operator<<(ostream &os, Card_t const &card)
{
  if (!card.m_valid) {
    os << "NA";
  } else {
    switch(card.m_cardValue) {
    case TWO:
      os << "2";
      break;
    case THREE:
      os << "3";
      break;
    case FOUR:
      os << "4";
      break;
    case FIVE:
      os << "5";
      break;
    case SIX:
      os << "6";
      break;
    case SEVEN:
      os << "7";
      break;
    case EIGHT:
      os << "8";
      break;
    case NINE:
      os << "9";
      break;
    case TEN:
      os << "T";
      break;
    case JACK:
      os << "J";
      break;
    case QUEEN:
      os << "Q";
      break;
    case KING:
      os << "K";
      break;
    case ACE:
      os << "A";
      break;
    }
    switch(card.m_cardColor) {
    case H:
      os << "H";
      break;
    case D:
      os << "D";
      break;
    case S:
      os << "S";
      break;
    case C:
      os << "C";
      break;
    }
  }
  return os;
}

istream& operator>>(istream &is, Hand_t &hand)
{
  int i;
  for (i = 0; i < 5; ++i) {
    is >> hand.m_cards[i];
    if (!hand.m_cards[i].m_valid) {
      cout << "FAILED READ " << i << " card" << endl;
      return is;
    }
  }
  for (i = 0; i < 4; ++i) {
    for (int j = i+1; j < 5; ++j) {
      if (hand.m_cards[i] < hand.m_cards[j]) {
        Card_t card = hand.m_cards[i];
        hand.m_cards[i] = hand.m_cards[j];
        hand.m_cards[j] = card;
      }
    }
  }
  return is;
}

ostream& operator<<(ostream &os, Hand_t const &hand)
{
  os << hand.m_cards[0];
  for (int i = 1; i < 5; ++i) {
    os << " " << hand.m_cards[i];
  }
  return os;
}

bool Hand_t::is_valid() const
{
  for (int i = 0; i < 5; ++i) {
    if (!m_cards[i].m_valid) {
      return false;
    }
  }
  return true;
}

bool Hand_t::operator>(Hand_t const &other)
{
  vector<int> myinfo(5);
  vector<int> otherinfo(5);
  int otherRank = other.get_rank(otherinfo);
  int myRank = get_rank(myinfo);

  if (otherRank == myRank) {
    int i = 0;
    for(; i < 5; ++i) {
      if (myinfo[i] > otherinfo[i]) {
        cout << myRank << ":" << myRank << " =? ";
        return true;
      }
      if (myinfo[i] < otherinfo[i]) {
        cout << myRank << ":" << myRank << " =? ";
        return false;
      }
    }
    
    for (i = 0; i < 5; ++i) {
      if (!(m_cards[i] == other.m_cards[i])) {
        break;
      }
    }
    if (i > 4) {
      cout << "SCREAMSCREAMSCREAMSCREAM" << endl;
      return false;
    }
    cout << myRank << ":" << myRank << " =" << i << " ";
    return (m_cards[i] > other.m_cards[i]);
  }
  cout << myRank << ":" << otherRank << " !! ";
  return (myRank > otherRank);
}

int Hand_t::get_rank(vector<int> &add_info) const
{
  for (int i = 0; i < 5; ++i) {
    add_info[i] = -1;
  }
  if (is_straight()) {
    if (is_flush()) {
      if (ACE == m_cards[0].m_cardValue){
        return ROYAL_FLUSH;
      }
      return STRAIGHT_FLUSH;
    }
    return STRAIGHT;
  }
  if (is_flush()) {
    return FLUSH;
  }
  return kind(add_info);
}

int Hand_t::kind(vector<int> &add_info) const
{
  map<int, int> kinds;
  kinds.insert(map<int, int>::value_type(m_cards[0].m_cardValue, 1));
  pair<map<int, int>::iterator, bool> it;
  for (int i = 1; i < 5; ++i) {
    it = kinds.insert(map<int, int>::value_type(m_cards[i].m_cardValue, 1));
    if (!it.second) {
      ++it.first->second;
    }
  }
  switch(kinds.size()) {
  case 4:
    {
      map<int, int>::iterator it = kinds.begin();
      while (it != kinds.end()) {
        if (2 == it->second) {
          add_info[0] = it->first;
        }
        ++it;
      }
    }
    return ONE_PAIR;
  case 3:
    {
      map<int, int>::iterator itn1 = kinds.begin();
      map<int, int>::iterator itn = itn1++;
      switch (itn->second) {
      case 1:
        if ((1 == itn1->second) || (3 == itn1->second)) {
          if (1 == itn1->second) {
            ++itn1;
          }
          add_info[0] = itn1->first;
          return THREE_KIND;
        }
        itn = itn1++;
        if (itn->first > itn1->first) {
          add_info[0] = itn->first;
          add_info[1] = itn1->first;
        } else {
          add_info[0] = itn1->first;
          add_info[1] = itn->first;
        }
        return TWO_PAIRS;
      case 2:
        if (1 == itn1->second) {
          ++itn1;
        }
        if (itn->first > itn1->first) {
          add_info[0] = itn->first;
          add_info[1] = itn1->first;
        } else {
          add_info[0] = itn1->first;
          add_info[1] = itn->first;
        }
        return TWO_PAIRS;
      }
      //case 3:
      //default:
      add_info[0] = itn->first;
      return THREE_KIND;
    }
  case 2:
    {
      map<int, int>::iterator itn = kinds.begin();
      switch (itn->second) {
      case 1:
        ++itn;
      case 4:
        add_info[0] = itn->first;
        return FOUR_KIND;
      case 2:
        add_info[1] = itn->first;
        ++itn;
        add_info[0] = itn->first;
        break;
      case 3:
        add_info[0] = itn->first;
        ++itn;
        add_info[1] = itn->first;
        break;
      }
      return FULL_HOUSE;
    }
  }
  return HIGH_CARD;
}

bool Hand_t::is_straight() const
{
  return (
          (1 == m_cards[0].m_cardValue - m_cards[1].m_cardValue) &&
          (1 == m_cards[1].m_cardValue - m_cards[2].m_cardValue) &&
          (1 == m_cards[2].m_cardValue - m_cards[3].m_cardValue) &&
          (1 == m_cards[3].m_cardValue - m_cards[4].m_cardValue)
          );
}

bool Hand_t::is_flush() const
{
  for (int i = 0; i < 4; ++i) {
    if (m_cards[i].m_cardColor != m_cards[i+1].m_cardColor) {
      return false;
    }
  }
  return true;
}
