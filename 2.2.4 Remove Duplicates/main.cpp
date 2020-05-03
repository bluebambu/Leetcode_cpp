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
    ListNode* RemoveDuplica(ListNode* head)
    {

        ListNode *i, *j;

        for( i=head ; i->next!=nullptr ;)
        {
            j=i->next;

            if(j==nullptr) break;

            if(j->value == i->value)
            {
                i->next = j->next;
                delete j;
            }

            else
                i=i->next;
        }

        return head;
    }

    ListNode* RemoveDuplica2(ListNode* LL)
    {
        ListNode* head=new ListNode(-9999, LL);

        ListNode* p, *q, *r;

        for(p=head; p; )
        {
            if(p->next && p->next->value == p->value)
            {
                r=p->next;
                q=p->next->next;
                p->next=q;
                delete r;
            }
            else
                p=p->next;
        }

        return head->next;
    }

};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(1, new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(4, new ListNode(4))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.RemoveDuplica2(b);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
