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

struct ListNode
{

    ListNode(int a, ListNode* b):value(a),next(b) {}
    ListNode(int a): value(a), next(nullptr) {}
    ListNode():value(0),next(nullptr) {}

    int value;
    ListNode* next;
};


class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode* head = new ListNode();
        ListNode* p = head;

        while(l1 || l2)
        {
            if(!l1)
                {p->next = l2; break;}
            else if(!l2)
                {p->next = l1;break;}
            else if(l1->value < l2->value)
            {
                p->next = l1;
                l1=l1->next;
            }
            else if(l1->value >= l2->value)
            {
                p->next=l2;
                l2=l2->next;
            }

            p=p->next;
        }

        return head->next;
    }

//////////////better! /////////////////////////
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy=new ListNode(0);
        ListNode* p=dummy;

        while(l1 && l2){
            if(l1->val < l2->val){
                p->next=l1;
                l1=l1->next;
                p=p->next;
            }else{
                p->next=l2;
                l2=l2->next;
                p=p->next;
            }
        }

        if(!l1){
            p->next=l2;
        }else
            p->next=l1;

        return dummy->next;
    }
//////////////// Recursive  //////////////////////
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;

        if(l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l2->next, l1);
            return l2;
        }
    }
};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(3, new ListNode(4)));

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(12, new ListNode(15, new ListNode(22, new ListNode(26, new ListNode(78))))))));

    for(auto i=a;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.mergeTwoLists(a, b);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
