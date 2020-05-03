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
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int value;
 *     ListNode *next;
 *     ListNode(int x) : value(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(-999);
        dummy->next = head;

        ListNode* p=dummy;
        ListNode* q=p->next;

        while(q){
            if(q->value == q->next->value){
                while(q->value == q->next->value){
                    q=q->next;
                    if(!q->next) break;
                }

                p->next=q->next;
                q=q->next;
            }
            else{
                p=p->next;
                q=q->next;
            }
        }

        return dummy->next;

    }
};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(2, new ListNode(5, new ListNode(2, new ListNode(6, new ListNode(78))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->valueue<<",";
//    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.deleteDuplicates(b);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
