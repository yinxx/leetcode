#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

typedef ListNode node;

node* plus_helper(node* n){
    // Base case:
    if(!n->next){
        n->val = n->val + 1;
        return n;
    }
    node* nxt = plus_helper(n->next);
    if(nxt->val == 10){
        nxt->val = 0;
        n->val = n->val + 1;
    }
    return n;
}

node* plus_one(node* n){
    n = plus_helper(n);
    if(n->val != 10) return n;
    // added a whole digit.
    n->val = 0;
    node* head = new node(1);
    head->next = n;
    return head;
}

int main(){
    auto print_list = [](node* n){
        while(n){
            std::cout << n->val << " ";
            n = n->next;
        }
    };
    ListNode a(9);
    ListNode b(9);
    ListNode c(9);
    ListNode d(9);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    print_list(plus_one(&a));
    return 0;
}
