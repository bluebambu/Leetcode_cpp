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


struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};


class Solution
{
public:
    ///// leetcode passed, recursion ///////
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        if(!head->next)
            return head;

        ListNode* newhead=reverseList(head->next);
        head->next->next=head;
        head->next=nullptr;

        return newhead;
    }

    //////// leetcode passed, iterative /////////
    ListNode* reverseList2(ListNode*& head){
        if(!head) return nullptr;
        ListNode *pre=NULL, *cur=head, *next;

        while(head){
            next=head->next;
            head->next=pre;
            pre=head;
            head=next;
        }
        return pre;
    }

};

int main()
{
    Solution a;




}
