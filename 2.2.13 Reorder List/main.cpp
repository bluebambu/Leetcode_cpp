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
    ListNode* ReOrderList(ListNode* head)
    {
        int length=0;

        for(ListNode* i=head; i!=nullptr;i=i->next)
            ++length;

        int mid = length/2;

        ListNode *tmp=head;

        for(int j=1;j<mid;++j )
        {
            tmp=tmp->next;
        }
        // tmp = mid_iter

        ListNode* head2 = tmp->next;

        tmp->next = nullptr;


        ListNode *i=head2->next, *j=i->next;

        head2->next=nullptr;

        for(;i!=nullptr;)
        {

            i->next = head2;
            head2 = i;
            i = j;
            if(j) j = j->next;
        }

        // now combine head & head2
        ListNode * ii, *jj;

        for(ListNode *i=head, *j=head2;i!=nullptr;)
        {
            ii=i->next;
            jj=j->next;

            i->next=j;
            if(ii) j->next=ii;

            i=ii;
            j=jj;
        }


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

    for(auto i=a;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.ReOrderList(a);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
