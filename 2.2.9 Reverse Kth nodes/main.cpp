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
    ListNode* ReverseKthNodes(ListNode* head, int gap)
    {

        ListNode* dummy = new ListNode(-999, head);

        ListNode *i=dummy, *j=i->next;

        for(int idx=0;j!=nullptr;)
        {
            ++idx;
            if(idx%gap==0)
            {
                ListNode *tmphead = i->next;
                ListNode *tmppost = j->next;

                ReverseEntire(tmphead, j);

                i->next = j;
                tmphead->next = tmppost;
                i=tmphead;
                j=tmppost; // j 要移动到 原来的 j->next 上去；
                continue;
            }

            j=j->next;


        }

        return dummy->next;

    }

    void ReverseEntire(ListNode* head, ListNode* tail)
    {
        ListNode  *i, *j, *k;

        for(i=head, j=i->next, k=j->next; i!=tail;)
        {


            j->next = i;
            i=j;
            j=k;
            if(k) k=k->next;
        }

        head->next = nullptr;
    }



};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(2, new ListNode(5, new ListNode(9, new ListNode(6, new ListNode(78))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c =s.ReverseKthNodes(b, 2);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
