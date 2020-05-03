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
    ListNode* CheckCycle(ListNode* head)
    {
        ListNode *i=head, *j=head;

        while(i!=nullptr)
        {
            i=i->next->next;
            j=j->next;

            if(i==j) return i;
        }

        return nullptr;


    }


};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(2, new ListNode(5, new ListNode(2, new ListNode(6)))))));

    ListNode* endlist;

    for(auto i=b;i!=nullptr;i=i->next)
        if(i->next == nullptr) endlist=i;

    endlist->next = b->next->next;
//
//    for(auto i=b;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    ListNode* c = s.CheckCycle(b);

    cout<<c->value<<",";s

}
