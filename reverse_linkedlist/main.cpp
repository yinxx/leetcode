#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverse(ListNode* head){
    if(!head)
        return nullptr;
    if(!head->next)
        return head;
  
    auto next = head->next; 
    head->next = nullptr; 
    auto to_return = reverse(next);
    next->next = head;
    return to_return; 
}

int main(){
    ListNode a(1),b(2),c(3);
    a.next = &b;
    b.next = &c;
    ListNode* head = reverse(&a);
    while(head){
        std::cout << head->val << std::endl;
        head = head->next;
    }
    return 0;
}
