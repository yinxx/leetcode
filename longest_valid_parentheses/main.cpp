#include <iostream>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::string;
using std::stack;
using std::vector;

// A valid parentheses substring is one where all the parentheses
// are matched correctly. A stack or some sort could be used to solve
// the most basic, which is to check whether the substring is correct
// or not.
//
// The most basic DP solution is O(N^3):
// OPT(i,j) = OPT(i+1, j-1) + 1(s[i] == '(' and s[j] == ')') 
// ONLY if {i+1,...,j-1} makes a valid parentheses substring.
// The caveat is that {i+1...k-1}, {k...j-1} could be 2 subproblems,
// hence O(N^3).
//
// 

int longest_valid_parentheses(string str){
    stack<char> sc;
    stack<int> sv;
    // Algorithm:
    // if c is (:
    // Add onto the sc. Add a 0 onto the sv.
    //
    // if c is ):
    // If the character directly below is a (, then pop off (.
    //      For sv, we must do something more complicated:
    //          while sv.top != 0:
    //              sv.pop, add to a temp
    //          sv.pop the 0 that's left. Put the temp + 2 onto the sv.
    //
    // If the character directly below is not a (, then keep ) there, and its corresponding 0.
    //      This 0 will serve as a roadblock for future "pop-til-0" algs.
    
    for(char c : str){
        if(c == '('){
           sc.push('(');
           sv.push(0);
        } 
        else if(c == ')'){
            if(!sc.empty() && sc.top() == '('){
                sc.pop();
                int temp = 0;
                int zero_count = 0;
                while(!sv.empty() && zero_count < 2){
                    zero_count += (sv.top() == 0);
                    if(zero_count >= 2)
                        break;
                    temp += sv.top();
                    sv.pop(); 
                }
                sv.push(temp + 2); // replace with a temp + 2
            }
            else{
                sc.push(')');
                sv.push(0);
            }
        }
    }

    int max_parenths = 0;
    while(!sv.empty()){
        max_parenths = std::max(max_parenths, sv.top());
        sv.pop();
    }
    return max_parenths;
}

int main(){
    cout << "ANSWER : " << longest_valid_parentheses(")()())()()(") << endl;
    return 0;
}
