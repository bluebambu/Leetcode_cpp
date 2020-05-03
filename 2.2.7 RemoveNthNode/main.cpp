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
    ListNode* RemoveNthNode(ListNode* head, int n)
    {
        ListNode *i, *j=nullptr;
        int idx=0;

        for(i=head; i->next!=nullptr;i=i->next)
        {
            ++idx;
            if(idx==n+1) j=head;
            // 这里n+1 和 continue是否同时用，需要仔细考虑！！
            if(j!=nullptr) j=j->next;

        }

        ListNode* tmp = j->next;
        j->next = j->next->next;

        delete tmp;

        return head;


    }

};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(2, new ListNode(5, new ListNode(2, new ListNode(6, new ListNode(78))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.RemoveNthNode(b, 4);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
