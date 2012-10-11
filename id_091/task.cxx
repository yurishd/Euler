#include <iostream>
#include <map>
#include <set>

using namespace std;

int const MAX_COORD = 50;

struct point_t
{
  int m_x;
  int m_y;

  point_t(int x, int y) :m_x(x), m_y(y) {}
  point_t() : m_x(0), m_y(0) {}

  point_t& operator++()
  {
    ++m_y;
    if (m_y > MAX_COORD) {
      m_y = 0;
      ++m_x;
      if (m_x > MAX_COORD) {
        m_x = 0;
      }
    }
    return *this;
  }

  bool isNotOrigin() const
  { return ((m_x != 0) || (m_y != 0)); }

  bool operator==(point_t const& other) const
  { return ((m_x == other.m_x) && (m_y == other.m_y)); }
};

ostream& operator<<(ostream &os, point_t const &pt)
{
  os << "x: " << pt.m_x << ", y: " << pt.m_y;
  return os;
}
bool operator<(point_t const &ptl, point_t const &ptr)
{
  if (ptl.m_x < ptr.m_x) return true;
  if (ptl.m_x > ptr.m_x) return false;
  return (ptl.m_y < ptr.m_y);
}

struct DoublePoint_t
{
  point_t m_points[2];

  DoublePoint_t(point_t const &pt1, point_t const &pt2)
  {
    if (pt1 < pt2) {
      m_points[0] = pt2;
      m_points[1] = pt1;
    } else {
      m_points[0] = pt1;
      m_points[1] = pt2;
    }
  }
};

bool operator<(DoublePoint_t const &ptl, DoublePoint_t const &ptr)
{
  if (ptl.m_points[0] < ptr.m_points[0]) return true;
  if (ptl.m_points[0] == ptr.m_points[0]) {
    return (ptl.m_points[1] < ptr.m_points[1]);
  }
   return false;
}

int IsRightAngle(map<point_t, int> &diags, set<DoublePoint_t> &used_points,
                  point_t const &ptd, point_t const &pts);

int main(int argc, char *argv[])
{
  int sum = 0;

  map<point_t, int> diags;
  set<DoublePoint_t> used_points;

  for (int i = 0; i <= MAX_COORD; ++i) {
    int sqi = i*i;
    for (int j = 0; j <= MAX_COORD; ++j) {
      diags.insert(map<point_t, int>::value_type(point_t(i,j), sqi +j*j));
    }
  }
  cout << "INIT DONE" << endl;
  point_t ptd(0,0);
  ++ptd;
  while (ptd.isNotOrigin()) {
    point_t pts(0,0);
    ++pts;
    while (pts.isNotOrigin()) {
      sum += IsRightAngle(diags, used_points, ptd, pts);

      //if (IsRightAngle(diags, ptd, pts)) {
      //  ++sum;
        //if (ptd.m_x && ptd.m_y && (ptd.m_x != ptd.m_y)
        //    &&((ptd.m_x == pts.m_x) || (ptd.m_y == pts.m_y))) ++sum;
      //}
      ++pts;
    }
    ++ptd;
  }

  cout << sum << endl;
  return 0;
}

int IsRightAngle(map<point_t, int> &diags, set<DoublePoint_t> &used_points,
                  point_t const &ptd, point_t const &pts)
{
  //cout << ptd << " | " << pts << " = ";
  if (ptd == pts) {
    //cout << "0" << endl; 
    return 0;
  }
  if (!used_points.insert(DoublePoint_t(ptd,pts)).second) {
    //cout << "0" << endl; 
    return 0;
  }
  map<point_t, int>::const_iterator itd = diags.find(ptd);
  map<point_t, int>::const_iterator its = diags.find(pts);
  point_t tmp;
  tmp.m_x = pts.m_x - ptd.m_x;
  if (tmp.m_x < 0) tmp.m_x *= (-1);
  tmp.m_y = pts.m_y - ptd.m_y;
  if (tmp.m_y < 0) tmp.m_y *= (-1);
  map<point_t, int>::const_iterator itt = diags.find(tmp);
  int retValue = 0;
  int test = ((*its).second + (*itt).second);
  if (test == (*itd).second) {
    ++retValue;
    //cout << ptd << " -||- " << pts << " : " << tmp << "=>> ";
    //cout << (*itd).second << (((*itd).second == retValue)?"==":"!=")
    //     << (*its).second << "+"
    //     << (*itt).second;
    //    if (ptd.m_x && ptd.m_y && (ptd.m_x != ptd.m_y)
    //        && ((ptd.m_x == pts.m_x) || (ptd.m_y == pts.m_y))) {
    //      cout << " x 2";
    //    }
    //cout << endl;
  }
  if ((*itd).second + (*its).second == (*itt).second) {
    ++retValue;
  }
  if ((*itd).second + (*itt).second == (*its).second) {
    ++retValue;
  }
  //cout << retValue << endl; 
  return retValue;
}
