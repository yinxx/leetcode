#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

auto print_list = [](ListNode* n){
    while(n){
        std::cout << n->val << " ";
        n = n->next;
    }
    std::cout << std::endl;
};

// Restrictions: 
// - Cannot alter value in nodes
// - Constant memory

// Helper function:
// If head is nullptr, then return <nullptr, nullptr>
// If k cannot go to 0, then return <head, early_tail>
std::pair<ListNode*, ListNode*> reverse(ListNode* head, int k){
    // stupid specs make no sense
    auto list_len = [](ListNode* n, int k) -> std::pair<int, ListNode*>{
        int count = 0;
        ListNode dummy(0);
        dummy.next = n;
        ListNode* follower = &dummy;
        while(n && ++count < k) {
            n = n->next;
            follower = follower->next;
        }
        return {count, follower};
    };
    auto p = list_len(head, k);
    if(p.first < k){
        return {head, p.second};
    }

    if(!head)
        return {nullptr, nullptr};
    ListNode* node = head;
    ListNode* prev = nullptr;
    ListNode* next = head->next; 
    for(int i = 0; i < k && node; i++){
        next = node->next;
        node->next = prev;
        prev = node;
        node = next;
    }
    head->next = next;
    if(!prev)
        prev = head;
    // node will always be at the last node or the k-th node
    return {prev, head};
}

ListNode* reverse_k_group(ListNode* head, int k){
    ListNode dummy(0);
    dummy.next = head;
    ListNode* node = &dummy;
    while(node->next){
        auto p = reverse(node->next, k);
        node->next = p.first;
        node = p.second;    
    }
    return dummy.next;
}

typedef ListNode ln;
int main(){
    ln a(1), b(2), c(3), d(4), e(5); 
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    // auto p = reverse(&a, 0);
    auto p = reverse_k_group(&a, 5);
    print_list(p); 
    return 0;
}
