#include <iostream>
#include <vector>
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Algorithm:
//
// The way to generate these trees is to go from the root and call the following functions:
// 
// for k in 0:n :
//     root -> left(n - k)
//          -> right(k)
//     
// we will generate all possible left branches with all possible right branches and do a
// cartesian product to generate new trees.

TreeNode* clone(TreeNode* root){
    if(!root)
        return nullptr;
    TreeNode* croot = new TreeNode(root->val);
    croot->left = clone(root->left);
    croot->right = clone(root->right);
    return croot;
}

vector<TreeNode*> generate_trees(int n, int offset){
    if(n == 0)
        return {nullptr};
    if(n == 1)
        return {new TreeNode(1 + offset)};
    vector<TreeNode*> v;
    for(int i = 1; i <= n; i++){
        // We want the root to be of value i.
        vector<TreeNode*> rv = generate_trees(n-i, i+offset);
        vector<TreeNode*> lv = generate_trees(i-1, offset);
        for(TreeNode* r : rv){
            for(TreeNode* l : lv){
                TreeNode* root = new TreeNode(i+offset);
                root->left = clone(l);
                root->right = clone(r);
                v.push_back(root);
            }
        }
    }
    return v;
}

int main(){
    vector<TreeNode*> trees = generate_trees(3, 0);
    std::cout << trees.size() << std::endl;
    return 0;
}
