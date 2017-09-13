#include <iostream>
#include <vector>
using std::cout;
using std::endl;

struct node {
    node(int _val, 
            node* _l = nullptr, 
            node* _r = nullptr, 
            node* _n = nullptr) : 
        val(_val), l(_l), r(_r), n(_n) {};
    int val;
    node *l, *r, *n;
};

auto leftest = [](node* n) -> node* {
    if(!n)
        return nullptr;
    return n->l ? n->l : n->r; 
};
// links all nodes of left's children.
void layer_link(node* left){
    if(!left)
        return;
    node* to_next = nullptr;
    if(left->l) {
        to_next = left->l;
        if(left->r)
            left->l->n = left->r;
    }
    if(left->r)
        to_next = left->r;
    
    if(to_next)
        to_next->n = leftest(left->n);

    layer_link(left->n);
}

void link(node* root){
    if(!root)
        return;
    layer_link(root);
    while(root && leftest(root) == nullptr)
        root = root->n;
    link(leftest(root));
}

int main(){
    node h(8),i(9);
    node f(6),g(7, &h, &i);
    node d(4),e(5, &f, &g);
    node b(2, &d),c(3, nullptr, &e);
    node a(1, &b, &c);
    link(&a);
    cout << h.n->val << endl;
    cout << f.n->val << endl;
    cout << d.n->val << endl;
    cout << b.n->val << endl;
};
