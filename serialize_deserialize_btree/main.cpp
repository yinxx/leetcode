#include <iostream>

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _v) : val(_v), left(nullptr), right(nullptr) {}
};

typedef std::string str;
typedef TreeNode node;
using std::to_string;

// To serialize this binary tree, we should try DFS.
// Algorithm:
// 
// serialize(s&, n):
//     s += n ? "x" : n.val;
//     dfs(s&, n.left)
//     dfs(s&, n.right)
// 
// deserialize(s&, offset&):
//     if s is "x":
//         return nullptr
//     new_n = node( int(s) )
//     new_n.left = deserialize( s, offset )
//     new_n.right = deserialize( s, offset )

void _serialize(str& s, node* n){
    if(!n) {
        s += 'x';
        s += ',';
    }
    else {
        s += to_string(n->val);
        s += ',';
        _serialize(s, n->left);
        _serialize(s, n->right);
    }
}

str serialize(node* root){
    str s("");
    _serialize(s, root);
    return s;
}

node* _deserialize(const str& s, int& offset){
    if(s[offset] == 'x') {
        offset += 2; // skips comma
        return nullptr;
    }
    int start = offset, len = 0;
    while(s[start+len] != ',') len++;
    int num = atoi(s.data()+start);
    node* n = new node(num);
    offset += len + 1; // skips comma
    n->left = _deserialize(s, offset); 
    n->right = _deserialize(s, offset);
    return n;
}

node* deserialize(str s_){
    str s = s_; // copy
    int offset = 0;
    return _deserialize(s, offset);
}

int main(){
    node a(1), b(255), c(-3), d(400000);
    a.left = &b;
    b.right = &c;
    a.right = &d;
    str serialized = serialize(&a);
    std::cout << serialized << std::endl;
    node* deserialized = deserialize(serialized);
    str reserialized = serialize(deserialized);
    std::cout << reserialized << std::endl;
    return 0;
}
