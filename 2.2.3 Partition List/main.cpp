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
    ListNode* PartitionList(ListNode* head, int x)
    {
        ListNode* temp = new ListNode();

        ListNode* dummy = new ListNode(-999, head);

        ListNode *i, *j, *temp_cur=temp;

        for(i=dummy;i->next!=nullptr;)
        {
            j=i->next;

            if(j->value >= x)
            {
                temp_cur->next = j;
                i->next = j->next;
                temp_cur = temp_cur->next;
                temp_cur->next = nullptr;
                // 最后需要将末尾归零，因为temp的前面
                // 几个元素都不受影响，但是最后一个还是会
                // 保留原来的 next。
            }


            else
                i=i->next;
        }

        i->next=temp->next;

        return dummy->next;




    }

    ListNode* PartitionList2(ListNode* LL, int x)
    {
        ListNode* head_1 = new ListNode(-999, LL);
        ListNode* head_2 = new ListNode(-999, nullptr); // 头结点应该是个obj
        ListNode* q = head_2;

        for(ListNode* p=head_1; p ;)
        {
            if(p->next && p->next->value < x)
            {
                q->next=p->next;
                p->next=p->next->next;

                q=q->next;
            }
            else
                p=p->next;
        }

        q->next=head_1->next;

        return head_2->next;
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

    ListNode* c = s.PartitionList(b, 4);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
