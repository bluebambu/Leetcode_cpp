#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>

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
    ListNode* SwapNodes(ListNode* head)
    {
        ListNode* dummy = new ListNode(-999, head);

        ListNode *i, *j, *k;

        for(i=dummy ; i!=nullptr;)
        {
            j=i->next;
            if(!j) break;

            k=j->next;
            if(!k) break;

            // j 和 k 要一步一步确认不为0，不然会报错！

            i->next = k;
            j->next = k->next;
            k->next = j;

            i=j;
        }

        return dummy->next;

    }

    ListNode* SwapNodes2(ListNode* LL)
    {
        ListNode* head = new ListNode(-999, LL);
        ListNode* p=head, *q;

        while(p->next && p->next->next)
        {
            q=p->next->next->next;

            p->next->next->next=p->next;
            p->next=p->next->next;
            p->next->next->next=q;

            p=p->next->next;
        }

        return head->next;
    }

};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(2, new ListNode(5, new ListNode(2, new ListNode(6, new ListNode(78, new ListNode(90)))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.SwapNodes2(b);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
