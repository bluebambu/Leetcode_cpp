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
    ListNode* CyclePoint(ListNode* head)
    {
        ListNode *fast=head, *slow=head;

        while(fast->next)
        {
            fast=fast->next->next;
            slow=slow->next;

            if(fast==slow)
            {
                ListNode* slow2=head;
                while(1)
                {
                    slow2=slow2->next;
                    slow=slow->next;

                    if(slow==slow2) return slow2;
                }
            }
        }

        return nullptr;
    }
//////////////////////Leetcode passed ///////////////////////////////
    ListNode *detectCycle(ListNode *head) {
        if(!head) return NULL;
        if((head->next==NULL)) return NULL;

        ListNode *fast=head->next->next, *slow=head->next; // 不能从head 开始，否则的话，如果cycle从head开始，那下一个循环就直接break了！！！ 特殊情况！！！

        for(;fast && fast->next; fast=fast->next->next, slow=slow->next){
            if( fast==slow) break;
        }

        if(!fast || !fast->next) return NULL;

        slow=head;

        for(;slow!=fast; slow=slow->next, fast=fast->next);

        return slow;
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


    ListNode* c = s.CyclePoint(b);

//    for(auto i=c;i!=nullptr;i=i->next)
        cout<<c->value<<",";

}
