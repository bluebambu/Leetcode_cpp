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

struct TreeNode;
void print();

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

void print(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);

    while(q.size()){
        auto tmp = q.front();
        cout<<tmp->val<<" ";
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
        q.pop();
    }
}



class Solution
{
public:
    // LC passed
    ListNode* sortList(ListNode* head) {
        return sort(head, nullptr);
    }

    ListNode* sort(ListNode* start, ListNode* end){
        if(!start || start->next == end) return start;

        ListNode *fast=start, *slow=start;

        /// 不能写成 fast！=end， 因为fast理应无法到达end    [start, end)
        for(; fast->next!=end && fast->next->next!=end; fast=fast->next->next, slow=slow->next);

        fast=slow->next;
        slow->next=nullptr; ///  要断开， 因为合并2个list时， 最后的2个nullptr是必不可少的。
        slow=start;

        slow = sort(start, nullptr);
        fast = sort(fast, nullptr);

        ListNode* dummy = new ListNode(0),*p=dummy;

        while(slow && fast){
            if(slow->val < fast->val){
                p->next = slow;
                slow=slow->next;
            }else{
                p->next = fast;
                fast=fast->next;
            }
            p=p->next;
        }

        p->next = slow ? slow : fast;
        return dummy->next;
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


}
