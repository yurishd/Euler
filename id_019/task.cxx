#include <iostream>

using namespace std;

char const *month[] = {
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "Jun",
  "Jul",
  "Aug",
  "Sep",
  "Oct",
  "Nov",
  "Dec"
};
enum {
  JAN = 0,
  FEB,
  MAR,
  APR,
  MAY,
  JUN,
  JUL,
  AUG,
  SEP,
  OCT,
  NOV,
  DEC
};

int const monthd[] = {
  31,
  28,
  31,
  30,
  31,
  30,
  31,
  31,
  30,
  31,
  30,
  31
};

char const * WDay[] = {
  "Sun",
  "Mon",
  "Tue",
  "Wed",
  "Thu",
  "Fri",
  "Sat"
};

enum {
  SUN = 0,
  MON,
  TUE,
  WED,
  THU,
  FRI,
  SAT
};

bool is_leap_year(int the_year);

int main(int argc, char *argv[])
{
  int result;

  int nextFirstWDay = MON;
  int curYear = 1899;
  int curMonth = DEC;

  //  int endYear = 1901;
  //int endYear = 2011;
  //int endMonth = JAN;
  int endYear = 2000;
  int endMonth = DEC;

  int dInMonths;
  bool leapYear = false;
  int shift;
  cout << ((DEC == curMonth)? month[0]: month[curMonth+1]) << " 1sh, "
       << ((DEC == curMonth)? curYear+1: curYear)
       << (leapYear?" l":"")
       <<" is " << WDay[nextFirstWDay] << endl;
  while (
         (curYear < endYear) ||
         (curYear == endYear) && (curMonth < endMonth)
         ) {
    if (DEC == curMonth) {
      curMonth = 0;
      ++curYear;
      leapYear = is_leap_year(curYear);
    } else {
      ++curMonth;
    }
    dInMonths = monthd[curMonth];
    if (leapYear && (FEB == curMonth)) {
      ++dInMonths;
    }
    shift = dInMonths % 7;
    nextFirstWDay = (nextFirstWDay + shift) % 7;
    if (SUN == nextFirstWDay) {
      if (
          (1901 <= curYear) ||
          (1900 == curYear) && (DEC == curMonth)
          ){
      ++result;
      }
    }
    cout << ((DEC == curMonth)? month[0]: month[curMonth+1]) << " 1sh, "
         << ((DEC == curMonth)? curYear+1: curYear)
         << (leapYear?" l":"")
         <<" is " << WDay[nextFirstWDay] << endl;
  }

  cout << result << endl;
  return 0;
}

bool is_leap_year(int the_year)
{
  if (0 == the_year % 400) {
    return true;
  }
  if (0 == the_year % 100) {
    return false;
  }
  if (0 == the_year % 4) {
    return true;
  }
  return false;
}
