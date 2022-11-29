#ifndef _IOSTREAM_H
#include <iostream>
#include <climits>
#define _IOSTREAM_H
#endif

using namespace std;

enum Boolean { FALSE, TRUE};

class Tree;

class TreeNode {
friend class Tree;
friend int equal(TreeNode*, TreeNode*);
private:
    TreeNode *LeftChild;
    int data;
    TreeNode *RightChild;
    TreeNode() {LeftChild = RightChild = 0;};
    TreeNode(char ch, TreeNode *Lefty, TreeNode *Righty)
    {
	data = ch;
	LeftChild = Lefty;
	RightChild = Righty;
    }
};

class Tree {
friend int operator==(const Tree&, const Tree&);
private:
    TreeNode *root;
    void inorder(TreeNode *);
    void inorder(TreeNode *, int *);
    void inorder_sum(TreeNode *, int *);
    void inorder_min(TreeNode *, int *);
    void inorder_max(TreeNode *, int *);
    void inorder_height(TreeNode *, int *, int *);
    void inorder_degree(TreeNode *, int *);
    void preorder(TreeNode *);
    void postorder(TreeNode *);
    TreeNode* copy(TreeNode *);
public:
    void setup();
    void inorder();
    void preorder();
    void postorder();
    int size();
    int sum();
    int max();
    int min();
    int height();
    int degree();
    Tree(const Tree&);
    Tree() {root = 0;};
};

int Tree::size()
{
    int count = 0;
    this->inorder(root, &count);
    return count;
}

int Tree::degree()
{
    int max_degree = 0;
    this->inorder_degree(root, &max_degree);
    return max_degree;
}

int Tree::height()
{
    int height = 0, buf = -1;
    this->inorder_height(root, &height, &buf);
    return height;
}

int Tree::sum()
{
    int sum = 0;
    this->inorder_sum(root, &sum);
    return sum;
}

int Tree::min()
{
    int min = INT_MAX;
    this->inorder_min(root, &min);
    return min;
}

int Tree::max()
{
    int max = INT_MIN;
    this->inorder_max(root, &max);
    return max;
}

void Tree::setup()
{
    root = new TreeNode(1,0,0);
    root->LeftChild = new TreeNode(2,0,0);
    root->LeftChild->LeftChild = new TreeNode(3, 0, 0);
    root->LeftChild->RightChild = new TreeNode(4, 0, 0);
    root->LeftChild->LeftChild->LeftChild = new TreeNode(5, 0, 0);
    root->LeftChild->LeftChild->LeftChild->LeftChild = new TreeNode(5, 0, 0);
}

void Tree::inorder()
{
   inorder(root);
}

void Tree::preorder()
{
   preorder(root);
}

void Tree::postorder()
{
   postorder(root);
}

void Tree::inorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 inorder(CurrentNode->LeftChild);
	 cout << CurrentNode->data;
	 inorder(CurrentNode->RightChild);
     }
}

void Tree::inorder(TreeNode *CurrentNode, int *count)
{
     if (CurrentNode) {
	 inorder(CurrentNode->LeftChild, count);
     (*count) += 1;
	 inorder(CurrentNode->RightChild, count);
     }
}

void Tree::inorder_sum(TreeNode *CurrentNode, int *sum)
{
     if (CurrentNode) {
	 inorder_sum(CurrentNode->LeftChild, sum);
     (*sum) += CurrentNode->data;
	 inorder_sum(CurrentNode->RightChild, sum);
     }
}

void Tree::inorder_min(TreeNode *CurrentNode, int *min)
{
     if (CurrentNode) {
	 inorder_min(CurrentNode->LeftChild, min);
     if(CurrentNode->data < (*min))
        (*min) = CurrentNode->data;
	 inorder_min(CurrentNode->RightChild, min);
     }
}

void Tree::inorder_max(TreeNode *CurrentNode, int *max)
{
     if (CurrentNode) {
	 inorder_max(CurrentNode->LeftChild, max);
     if(CurrentNode->data > (*max))
        (*max) = CurrentNode->data;
	 inorder_max(CurrentNode->RightChild, max);
     }
}

void Tree::inorder_height(TreeNode *CurrentNode, int *height, int *buf)
{
     if (CurrentNode)
     {
        (*buf) += 1;
	    inorder_height(CurrentNode->LeftChild, height, buf);
        if((*buf) > (*height))
        {
            (*height) = (*buf);
        }

	    inorder_height(CurrentNode->RightChild, height, buf);
        (*buf) -= 1;
     }
}

void Tree::inorder_degree(TreeNode *CurrentNode, int *max_degree)
{
     if (CurrentNode)
     {
        int node_degree = 0;
        if(CurrentNode->LeftChild)
            node_degree++;
        if(CurrentNode->RightChild)
            node_degree++;
        if(node_degree > (*max_degree))
            *max_degree = node_degree;

	    inorder_degree(CurrentNode->LeftChild, max_degree);
	    inorder_degree(CurrentNode->RightChild, max_degree);
     }
}

void Tree::preorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 cout << CurrentNode->data;
	 preorder(CurrentNode->LeftChild);
	 preorder(CurrentNode->RightChild);
     }
}

void Tree::postorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 postorder(CurrentNode->LeftChild);
	 postorder(CurrentNode->RightChild);
	 cout << CurrentNode->data;
     }
}

Tree::Tree(const Tree& s)
{
  root = copy(s.root);
}

TreeNode* Tree::copy(TreeNode *orignode)
{
  if (orignode) {
      TreeNode *temp = new TreeNode;
      temp->data = orignode->data;
      temp->LeftChild = copy(orignode->LeftChild);
      temp->RightChild = copy(orignode->RightChild);
      return temp;
  }
  else return 0;
}

// Driver
int operator==(const Tree& s, const Tree& t)
{
   return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode *a, TreeNode *b)
/* This function returns 0 if the subtrees at @a@ and @b@ are not
   equivalent. Otherwise, it will return 1 */
{
 if ((!a) && (!b)) return 1;  // both @a@ and @b@ are 0
 if (a && b &&                // both @a@ and @b@ are non-0
    (a->data == b->data)      // @data@ is the same
    && equal(a->LeftChild, b->LeftChild) // left subtrees are the same
    && equal(a->RightChild, b->RightChild) ) // right subtrees are the same
       return 1;
 return 0;
}

int main()
{
Tree t;
t.setup();
Tree s = t;
s.inorder();
cout << endl;
if (s == t) cout << 1; else cout << 0;
cout << endl;


cout << "Size:\n";
cout << t.size() << endl;
cout << "Sum:\n";
cout << t.sum() << endl;
cout << "Min\n";
cout << t.min() << endl;
cout << "Max\n";
cout << t.max() << endl;
cout << "Height\n";
cout << t.height() << endl;
cout << "Degree\n";
cout << t.degree() << endl;
}

