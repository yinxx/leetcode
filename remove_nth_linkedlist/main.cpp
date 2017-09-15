#include <iostream>

using std::cout;
using std::endl;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void traverse(ListNode* head){
    while(head){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Removing n-th from end means something like:
// Given list [1,2,3,4,5], and n=2, we will remove 4
//             5 4 3 2 1
// and get [1,2,3,5].
//
// f(h, n): h->next = f(h->next, n-1)

// This helper function to get the node. 
// It will return back a value int that is representative of how far from
// the end it is. The node reference will give us the node we need.
int helper(ListNode* &target, ListNode* head, int n){  
    if(!head)
        // "1" distance away from the end.
        // It's actually 0, but we need to return the node right before it.
        return 0; 

    int dist = helper(target, head->next, n);
    
    if(dist == n)
        target = head;
    return dist + 1;
}

ListNode* remove_nth_from_end(ListNode* head, int n){
    // Target is 1 node before the node to delete.
    ListNode* target = nullptr;
    
    helper(target, head, n);

    if(!target)
        // means this list is empty, it's the head, or we can't find the target
        // within the specified range which would violate the assumption
        return (head) ? head->next : nullptr;

    // skips over the current.
    target->next = (target->next) ? target->next->next : nullptr;
    
    // returns the head.
    return head;
}

int main(){ 
    ListNode a(1), b(2), c(3), d(4), e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    
    ListNode* head = &a;

    traverse(head);

    head = remove_nth_from_end(head, 2);
    traverse(head);

    head = remove_nth_from_end(head, 4);
    traverse(head);

    head = remove_nth_from_end(head, 1);
    traverse(head);

    head = remove_nth_from_end(head, 1);
    traverse(head);
    return 0;
}
