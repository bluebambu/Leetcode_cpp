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
//////////////Leetcode passed , fastest //////////////////

    ListNode* insertionSortList(ListNode* head) {
        if(!head) return nullptr;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode* i=head;

        while(i->next){
            ListNode *front = i->next;

            if(front->val < i->val){ /// this condition is very important to save run time
                ListNode *p=dummy;
                for(;p->next->val < front->val; p=p->next);

                i->next=front->next;
                front->next=p->next;
                p->next=front;
            }else
                i=i->next;
        }

        return dummy->next;
    }
//////////////Leetcode passed //////////////////

    ListNode* insertionSortList(ListNode* head) {
        if(!head) return nullptr;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode* i=head;

        while(i->next){
            ListNode *front = i->next;

            ListNode* p=dummy;
            for(;p->next!=front && p->next->val < front->val; p=p->next);

            if(p->next==front){
                i=i->next;
            }else{
                i->next=front->next;
                front->next = p->next;
                p->next=front;
            }
        }

        return dummy->next;
    }
/////////////////////////////////////////////
    ListNode* InsertSortLists(ListNode* l1)
    {
        ListNode* head = new ListNode(-999, l1);
        ListNode* p=head, *q, *r;

        while(p->next)
        {
            q=p->next;

            if(p->value <= q->value)
                // 这里应该有等号，与下面的 while 判断条件一致
                p=q;
            else
            {
                p->next = q->next;

                r=head;
                while(r->next->value <= q->value)
                    r=r->next;

                q->next=r->next;
                r->next=q;
            }
        }

        return head->next;
    }
////////////////////////////////////////////////////////////////////
    ListNode* insertionSortList(ListNode* head) {
        if(!head) return nullptr;

        ListNode* dummy = new ListNode(INT_MIN);
        dummy->next = head;

        ListNode* cur=dummy->next, *tmp, *idx=dummy;

        while(cur->next){
            int curval = cur->next->val;
            idx=dummy;
            while(idx->next->val < curval && idx!=cur)
                idx=idx->next;

            if(idx==cur){
                cur=cur->next;
            }else{
                tmp=cur->next->next;
                cur->next->next=idx->next;
                idx->next=cur->next;
                cur->next=tmp;
            }
        }

        return dummy->next;
    }

};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(3, new ListNode(4)));

    ListNode* b = new ListNode(7, new ListNode(1, new ListNode(7, new ListNode(12, new ListNode(-9, new ListNode(13, new ListNode(4, new ListNode(7))))))));

    for(auto i=a;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.InsertSortLists(b);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
