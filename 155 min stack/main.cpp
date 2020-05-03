#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

/**
 Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    getMin() -- Retrieve the minimum element in the stack.

**/


////// leetcode passed, one stack //////
class MinStack {
    vector<pair<int, int>> stack;
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        if(stack.empty()) stack.push_back(make_pair(x, x));
        else{
            int tmp=stack.back().second;
            stack.push_back(make_pair(x, tmp<x ? tmp : x));
        }
    }

    void pop() {
        stack.pop_back();
    }

    int top() {
        return stack.back().first;
    }

    int getMin() {
        return stack.back().second;
    }
};

/////////// leetcode passed, two stack /////////
class MinStack {
    vector<int> stack;
    vector<int> min;
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        stack.push_back(x);
        if(stack.size()==1) min.push_back(x);
        else min.push_back(x<min.back()? x: min.back());
    }

    void pop() {
        stack.pop_back();
        min.pop_back();
    }

    int top() {
        return stack.back();
    }

    int getMin() {
        return min.back();
    }
};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    a.flatten(tree);


}
