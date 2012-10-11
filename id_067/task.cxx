#include <iostream>
#include <deque>
#include <vector>
#include <fstream>

using namespace std;

template <typename T>
struct Node_t
{
  Node_t(Node_t<T> *pParent);
  ~Node_t();

  T get_node_value() const;

  void SetLeftNode(Node_t<T> *pNode);
  void SetRightNode(Node_t<T> *pNode);
private:
  Node_t *m_pParent;
  Node_t *m_pLeft;
  Node_t *m_pRight;
protected:
  T     m_data;
};

struct NodeData_t
{
  int m_Weight;
  int m_PathWeight;

  NodeData_t();
};

struct IntTreeNode_t : public Node_t<NodeData_t>
{
  IntTreeNode_t(IntTreeNode_t *pParent, int weight);

  void SetPathWeight(int pathWeight);
  bool UpdatePathWeightIfBetter(int pathWeight);
  int getFullWeight() const;

  IntTreeNode_t* CreateLeftNode(int weight);
  IntTreeNode_t* CreateRightNode(int weight);
};

int main(int argc, char *argv[])
{
  if (argc < 2) {
    cout << "Give input file name" << endl;
    return 0;
  }

  ifstream is(argv[1]);
  if (!is.good()) {
    cout << "BAD input file name" << endl;
    return 0;
  }


  vector<int> vinp;

  int itmp;
  while (!is.eof()) {
    is >> itmp;
    if (!is && !is.eof()) {
      cout << "BAD input file STRUCTURE" << endl;
      return 0;
    }
    vinp.push_back(itmp);
  }


  int inp_size = (int)vinp.size();

  cout << inp_size << endl;

  IntTreeNode_t root(NULL, vinp[0]);
  int result = root.getFullWeight();

  deque<IntTreeNode_t *> treeq;
  treeq.push_back(&root);

  deque<IntTreeNode_t *> tmpq;
  int jsize = 1;
  int i = 1;
  IntTreeNode_t *pRroot;
  IntTreeNode_t *pTmpNode;

  while(jsize < inp_size) {
    ++i;
    for (int jobi = 0; jobi < i; ++jobi) {
      pRroot = treeq[0];
      treeq.pop_front();
      //Build or init left
      if (tmpq.size() > 0) {//actually it should be == 1
        pTmpNode = tmpq[0];
        tmpq.pop_front();
        if (pTmpNode->UpdatePathWeightIfBetter(pRroot->getFullWeight())) {
          cout << "(" << pTmpNode->getFullWeight() << ") |";
        } else {
          cout << "!" << pTmpNode->getFullWeight() << "! |";
        }
      } else {
        pTmpNode = pRroot->CreateLeftNode(vinp[jsize]);
        ++jsize;
        ++jobi;
        cout << " " << pTmpNode->getFullWeight() << " |";
        treeq.push_back(pTmpNode);
      }
      if (result < pTmpNode->getFullWeight()) {
        result = pTmpNode->getFullWeight();
        //cout << "new result (L)" << result << endl;
      }

      //Build right
      pTmpNode = pRroot->CreateRightNode(vinp[jsize]);
      treeq.push_back(pTmpNode);
      ++jsize;
      if (result < pTmpNode->getFullWeight()) {
        result = pTmpNode->getFullWeight();
        //cout << "new result (R)" << result << endl;
      }
      tmpq.push_back(pTmpNode);
    }
    tmpq.clear();
    cout << " jsize = " << jsize << endl;
  }

  cout << "RESULT: " << result << endl;
  return 0;
}

template <typename T>
Node_t<T>::Node_t(Node_t<T> *pParent)
  : m_pParent(pParent), m_pLeft(0), m_pRight(0)
{}

template <typename T>
Node_t<T>::~Node_t()
{ delete m_pLeft; delete m_pRight; }

template <typename T>
T Node_t<T>::get_node_value() const
{ return m_data; }
 
template <typename T>
void Node_t<T>::SetLeftNode(Node_t<T> *pNode)
{ m_pLeft = pNode; }

template <typename T>
void Node_t<T>::SetRightNode(Node_t<T> *pNode)
{ m_pRight = pNode; }


NodeData_t::NodeData_t()
  : m_Weight(0), m_PathWeight(0)
{}

IntTreeNode_t::IntTreeNode_t(IntTreeNode_t *pParent, int weight)
  :  Node_t<NodeData_t>(pParent)
{ this->m_data.m_Weight = weight; }

void IntTreeNode_t::SetPathWeight(int pathWeight)
{ this->m_data.m_PathWeight = pathWeight; }

int IntTreeNode_t::getFullWeight() const
{ return this->m_data.m_Weight + this->m_data.m_PathWeight; }

IntTreeNode_t* IntTreeNode_t::CreateLeftNode(int weight)
{
  IntTreeNode_t *pNode = new IntTreeNode_t(this, weight);
  pNode->SetPathWeight(this->getFullWeight());
  Node_t<NodeData_t>::SetLeftNode(pNode);
}

IntTreeNode_t* IntTreeNode_t::CreateRightNode(int weight)
{
  IntTreeNode_t *pNode = new IntTreeNode_t(this, weight);
  pNode->SetPathWeight(this->getFullWeight());
  Node_t<NodeData_t>::SetRightNode(pNode);
}

bool IntTreeNode_t::UpdatePathWeightIfBetter(int pathWeight)
{
  if (this->m_data.m_PathWeight < pathWeight) {
    this->m_data.m_PathWeight = pathWeight;
    return true;
  }
  return false;
}
