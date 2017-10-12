#include <iostream>
#include <stack>
// Algorithm:
// The way to iterate through a btree is to take the leftmost nodes of each layer.
//
// During next(), we need to check:
//
// If the node has no children: 
//  1. pop() and use the previous node
// If the node has a right child: 
//  1. we're done with this node, so pop it off.
//  2. push right child, its left child, its left left child...
// If the node has a left child: 
//  that's not possible because we chose the leftest of all nodes.

struct TreeNode;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

typedef TreeNode tnode;
using std::stack;

class btree_iterator{
public:
    btree_iterator(tnode* n) {
        while(n){
            lvs.push(n);
            n = n->left;
        }
    }

    bool hasNext(){
        return lvs.size() != 0;  
    }

    int next(){
        tnode* cur = lvs.top();
        int v = cur->val;
        // Case 1: If the current node does not have a right
        if(!cur->right)
            lvs.pop();
        // Case 2: If the current node does have a right
        else{
            tnode* node = cur->right;
            lvs.pop();
            while(node){
                lvs.push(node);
                node = node->left;
            }
        }
        return v;
    }
private:
    stack<tnode*> lvs;
};

int main(){
    tnode a(3), b(1), c(2), d(4), e(5);
    a.left = &b;
    b.right = &c;
    a.right = &d; 
    d.right = &e;
    btree_iterator it(&a);
    while(it.hasNext()){
        std::cout << it.next() << std::endl;
    } 
}
