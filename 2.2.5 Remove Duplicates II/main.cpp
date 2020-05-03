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
    ListNode* RemoveDuplicaII(ListNode* head)
    {
        ListNode *dummy = new ListNode(-999, head);

        ListNode *i, *j, *k;

        for( i = dummy ; i->next!=nullptr;)
        {
            j=i->next;
            k=j->next;

            if(j==nullptr || k == nullptr) break;
            // 这个判断还是很重要的，nullptr -> value, nullptr -> next 都会报错的

            if(j->value == k->value)
            {
                ListNode* tmp;

                for(;(k->value)==(j->value);k=tmp)
                {
                    tmp = k->next;
                    delete k;
                }

                delete j;
                i->next = k;
            }

            else
            {
                i=i->next;
            }
        }

        return dummy->next;

    }

};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(3, new ListNode(5, new ListNode(6, new ListNode(6, new ListNode(78))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.RemoveDuplicaII(b);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
