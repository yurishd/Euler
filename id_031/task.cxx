#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct WaysCounter_t
{
  WaysCounter_t()
  {
    m_coins.push_back(200);
    m_coins.push_back(100);
    m_coins.push_back(50);
    m_coins.push_back(20);
    m_coins.push_back(10);
    m_coins.push_back(5);
    m_coins.push_back(2);
    m_coins.push_back(1);
  }

  long count_ways(long sum);
  long count_ways(long sum, size_t index);
  typedef map<int, long> CoinToWays_t;
  typedef map<int, CoinToWays_t> SumToCoinToWays_t;

  SumToCoinToWays_t    m_scways;
  vector<int>                m_coins;
};

int main(int argc, char* argv[])
{
  WaysCounter_t wcounter;
  cout << wcounter.count_ways(200) << endl;
  return 0;
}

long WaysCounter_t::count_ways(long sum)
{
  return count_ways(sum, 0);
}

long WaysCounter_t::count_ways(long sum, size_t index)
{
  if (index + 1 == m_coins.size()) {
    if (sum % m_coins[index] == 0) {
      cout << "Last for " << sum << " and "
           << m_coins[index] << " = 1" << endl;
      return 1;
    }
    cout << "Last for " << sum << " and " << m_coins[index] << " = 0" << endl;
    return 0;
  }
  SumToCoinToWays_t::iterator it = m_scways.find(sum);
  if (it != m_scways.end()) {
    CoinToWays_t::iterator it_start = it->second.find(m_coins[index]);
    if (it_start != it->second.end()) {
      cout << "FOUND for" << sum << " and " << m_coins[index] << " = "
           << it_start->second << endl;
      return it_start->second;
    }
  }
  long times = sum / m_coins[index];
  long rest = sum % m_coins[index];
  long retValue = 0;
  while (times > 0) {
    if (rest > 0) {
      retValue += count_ways(rest, index + 1);
    } else {
      cout << "Calced(M) for " << sum << " and " << m_coins[index+1]
           << " = 1" << endl;
                     ++retValue;
    }
    rest += m_coins[index];
    --times;
  }
  long tmp =  count_ways(sum, index + 1);
  cout << "Calced for " << sum << " and " << m_coins[index+1]
       << " = " << tmp << endl;
  cout << "       and " << sum << " and " << m_coins[index]
       << " = " << tmp + retValue << endl;
  retValue += tmp;
  if (it == m_scways.end()) {
    it = m_scways.insert(
           SumToCoinToWays_t::value_type(sum, CoinToWays_t())).first;
  }
  it->second.insert(CoinToWays_t::value_type(m_coins[index], retValue));
  return retValue;
}
