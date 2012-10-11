#include <iostream>
#include <deque>

using namespace std;

int inp[] = {
  75,
  95, 64,
  17, 47, 82,
  18, 35, 87, 10,
  20,  4, 82, 47, 65,
  19,  1, 23, 75,  3, 34,
  88,  2, 77, 73,  7, 63, 67,
  99, 65,  4, 28,  6, 16, 70, 92,
  41, 41, 26, 56, 83, 40, 80, 70, 33,
  41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
  53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
  70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
  91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
  63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
   4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23
};



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
  int inp_size = sizeof(inp)/sizeof(int);

  cout << inp_size << endl;

  IntTreeNode_t root(NULL, 75);
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
        pTmpNode = pRroot->CreateLeftNode(inp[jsize]);
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
      pTmpNode = pRroot->CreateRightNode(inp[jsize]);
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
