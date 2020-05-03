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
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    /// leetcode passed ///
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> stack;

        for(ListNode* p=headA; p; p=p->next){
            stack.insert(p);
        }

        for(ListNode* q=headB; q; q=q->next)
            if(stack.find(q)!=stack.end()) return q;

        return nullptr;
    }
    /// leetcode passed , two pointers///
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pa = headA, *pb=headB;

        for(;pa && pb; pa=pa->next, pb=pb->next);

        if(!pa){
            for(pa=headB; pb; pb=pb->next, pa=pa->next);
            pb=headA; /// here exchange the pointers
        }else{
            for(pb=headA; pa; pa=pa->next, pb=pb->next);
            pa=headB;
        }

        for(;pa!=pb && pa && pb;pa=pa->next, pb=pb->next);

        return pa==pb? pa : nullptr; /// especially for no intersection condition
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
