#include <iostream>

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int val) {
        this->val = val;
        this->next = nullptr;
    }
};

auto print_list = [](ListNode* n){
    while(n){
        std::cout << n->val << " ";
        n = n->next;
    }
    std::cout << std::endl;
};

// The algorithm is some variant of merge sort:
//
// Sort every 2 nodes, then every 4 nodes, etc.
// At every merge we perform the following:
// ListNode *lh, *rh = left & right halvesA
// move_and_return = (lh > rh) ? rh : lh, whichever node was less, move ->next. Check nulls as well.
// head = move_and_return()
// while lh not null and rh not null:
//     head->next = move_and_return()
// return head and tail

std::pair<ListNode*, ListNode*> merge(ListNode* lh, ListNode* rh){
    // returns the correct next node.
    auto move = [&lh, &rh](){
        ListNode* ret = nullptr; 
        if(!lh){
            ret = rh;
            if(rh)
                rh = rh->next;
        }
        else if(!rh){
            ret = lh;
            if(lh)
                lh = lh->next;
        }
        else if(lh->val < rh->val){
            ret = lh;
            lh = lh->next;
        }
        else{
            ret = rh;
            rh = rh->next;
        }
        return ret;
    };
    
    ListNode* head = move();
    ListNode* tail = head;
    while(lh || rh){
        tail->next = move(); 
        tail = tail->next; 
    }

    return {head, tail};
}

// We need to start off by sorting every 2 elements.
// (pair) (pair) (pair) ... (pair) (residue)
//
// Then, every 4.
// (4s) (4s) (4s) ... (4s) (residue)
ListNode* sort(ListNode* head){
    auto get_len = [](ListNode* n) -> int {
        int count = 0;
        while(n && ++count) 
            n = n->next;
        return count;
    };
    // Walks n steps or until nullptr
    auto walk = [](ListNode* n, int walk) -> ListNode* {
        while(n && walk--)
           n = n->next; 
        return n;
    };
    int len = get_len(head);
    
    ListNode* prev_seq = nullptr;
    // O(logN) iterations
    for(int num_sorted = 1; num_sorted < len; num_sorted *= 2){
        // O(N) iterations 
        bool flag = true;
        ListNode* node = head;
        while(node){
            // Find the first node, and then walk num_sorted to the second.
            ListNode* lhs = node;
            ListNode* rhs = walk(node, num_sorted);
            // Disconnect lhs and rhs
            ListNode* mid_node = walk(lhs, num_sorted-1);
            if(mid_node){
                mid_node->next = nullptr; 
            }
            ListNode* last_node = walk(rhs, num_sorted-1);
            ListNode* next_seq = nullptr;
            if(last_node){
                next_seq = last_node->next;
                last_node->next = nullptr;
            }
            // Merge
            auto p = merge(lhs, rhs);
            if(flag){
                head = p.first;
                flag = false;
            }
            else
                prev_seq->next = p.first;
            p.second->next = next_seq;
            node = next_seq;
            prev_seq = p.second;
        }
    }
    return head; 
}

int main(){
/*     ListNode a(3), b(4), c(4);
 *     ListNode w(1), x(2), y(5), z(7);
 *     a.next = &b;
 *     b.next = &c;
 *
 *     w.next = &x;
 *     x.next = &y;
 *     y.next = &z;
 *
 *     ListNode* head = merge(&a, &w).first;
 *
 *     print_list(head); */


    ListNode a(21), b(25), c(25), d(31), e(4);
    // should be:
    // 3,4,1,5,2,6,3
    // 1,3,4,5,2,3,6
    // 1,2,3,3,4,5,6
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    // e.next = &f;
    // f.next = &g;

    ListNode* head = sort(&a);

    print_list(head);
    return 0;
}
