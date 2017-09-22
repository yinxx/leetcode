#include <iostream>
#include <vector>
#include <cassert>

/* Algorithm:
 * We can recursively apply a divide and conquer method:
 *
 * Suppose we have list a and list b, with size la, and lb.
 * ma = a[la/2]
 * mb = b[lb/2]
 *
 * Lemma: We want to divide the smaller list by half every time for searching.
 * We can at most remove min(la, lb) elements at a time, or else we overjump.
 * 
 * What do we do with the larger matrix? We also remove smaller_list_size/2 elements
 * from it. 
 *
 * This way, we always remove equal amounts of elements from both sides of the median.
 */

/* Pseudocode:
 *
 * as, ae, bs, be = 0, len(a), 0, len(b)
 * if len(a) > len(b)
 *     a, b = b, a
 *     ae, be = be, ae
 *     as, bs = bs, as
 *
 * la, lb = ae-as, be-bs
 * ma, mb = median(a), median(b)
 *
 * to_remove = la/2 # safely remove half of smaller matrix
 * if ma < mb:
 *     a = a[as + to_remove, ...]
 *     b = b[..., be - to_remove]
 * else:
 *     a = a[..., ae - to_remove]
 *     b = b[bs + to_remove, ...] */

double median_sorted(std::vector<int>& a, std::vector<int>& b){
    auto median = [](std::vector<int>& v, int s, int e) -> double {
        assert( s <= e );
        return (v[s+(e-s)/2] + v[s+(e-s+1)/2]) / 2.0;
    };
    using std::swap; 
    int as = 0, ae = a.size()-1, bs = 0, be = b.size()-1; 
    while(true){
        if (a.size() > b.size()) {
            swap(a,b);
            swap(as, bs);
            swap(ae, be);
        }
        
        // base case
        if(ae-as == 0 && be-bs == 0)
            return double(median(a, as, ae) + median(b, bs, be))/2.0;
        else if(ae-as <= 0)
           return median(b, 
                   bs + 1 * (a.size() && a[ae] > median(b, bs, be)), 
                   be - 1 * (a.size() && a[ae] <= median(b, bs, be)));

        int la = ae-as;
        int ma = median(a, as, ae), mb = median(b, bs, be);

        int to_remove = (la+1)/2;
        if(ma < mb){
            as += to_remove;
            be -= to_remove;
        }
        else{
            ae -= to_remove;
            bs += to_remove;
        }
    }
}

int main(){
    // 1 2 3 4 4 5 6 8 9 10
    // median is: 4.5
    std::vector<int> a {};
    std::vector<int> b { 2,3,4,5 };
    std::cout << "ANSWER : " << median_sorted(a, b) << std::endl;
    return 0;
}
