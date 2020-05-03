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
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2)
    // 考虑两个数不等长的情况！！

    {
        ListNode *l3 = new ListNode();

        int carry=0, temp_value=0;

        ListNode *i=l1, *j=l2, *k=l3;



        while(i || j)
        {
            k->next = new ListNode();
            k=k->next;

            if(i&&j)
            {
                temp_value = (i->value + j->value + carry)%10 ;
                carry = (i->value + j->value + carry)/10;
                i=i->next;
                j=j->next;
            }

            else if(!i)
            // 这里应该是 else if，不是if，仔细体会！！

            {
                temp_value = (j->value + carry)%10 ;
                carry = (j->value + carry)/10;
                j=j->next;

            }

            else if(!j)
            {
                temp_value = (i->value + carry)%10 ;
                carry = (i->value +  carry)/10;
                i=i->next;

            }

            k->value = temp_value;

        }


        l3=l3->next;

        return l3;
    }

//////////////////// Leetcode passed  //////////////////////////////////
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry=0;
        ListNode *dummy = new ListNode(0), *q=dummy;

        for(ListNode* p1=l1, *p2=l2; p1 || p2;
            p1 = p1? p1->next : nullptr,
            p2 = p2? p2->next : nullptr){

            int a1 = p1? p1->val : 0;
            int a2 = p2? p2->val : 0;
            int curval = a1 + a2 + carry;
            carry=curval/10;
            curval%=10;
            q->next = new ListNode(curval);
            q=q->next;
        }

        if(carry) q->next = new ListNode(carry);

        return dummy->next;
    }

};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(5, new ListNode(6, new ListNode(8, new ListNode(5, new ListNode(9)))));

    for(auto i=a;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.addTwoNumbers(a, b);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
