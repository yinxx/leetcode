#include <iostream>
#include <stack>
#include <unordered_map>

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _v) : val(_v), left(nullptr), right(nullptr) {}
};

typedef std::string str;
typedef TreeNode node;
using std::to_string;
using std::stack;
using std::unordered_map;
// Iterative algorithm using a stack.
// Is the same algorithm, but instead of implicit stack, we use an actual stack.
// This way, we don't experience stack overflow.
str serialize(node* root){
    stack<node*> stk;
    str s;
    stk.push(root);
    while(!stk.empty()){
        // populate the stack with the nodes and perform pre-order construction as well.
        node* n = stk.top();
        stk.pop();
        s += n ? to_string(n->val) : "x"; 
        s += ',';
        if(n) { 
            stk.push(n->right);
            stk.push(n->left);
        }
    }
    return s;
}

node* deserialize(str s){
    auto intlen = [](str& s, int start) -> int{
        int len = 0;
        while(s[start+len] != ',') len++;
        return len;
    };
    auto consume = [&intlen](str& s, int& offset) -> node* {
        if(s[offset] == 'x'){
            offset += 2;
            return nullptr;
        }
        int len = intlen(s, offset);
        node* n = new node(atoi(s.data()+offset));
        offset += len+1;
        return n;
    };
    if(s.empty())
        return nullptr;
    stack<node*> stk;
    unordered_map<node*, int> map;

    int offset = 0;
    
    node* root = consume(s, offset);
    stk.push(root);

    while(!stk.empty()){
        node* n = stk.top();
        if(!n || map[n] == 2){
            stk.pop();
            continue;
        }
        map[n]++;
        node* next = consume(s, offset);
        if(map[n] == 1)
            n->left = next;
        else if(map[n] == 2)
            n->right = next;
        stk.push(next);
    }

    return root;
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
