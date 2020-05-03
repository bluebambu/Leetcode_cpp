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


struct RandomListNode {
     int label;
     RandomListNode *next, *random;
     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
     RandomListNode(int x, RandomListNode* y, RandomListNode* z): label(x), next(y), random(z) {}
};


class Solution
{
public:
    //////// leetcode passed, hashmap ///////////////////////////
    ///  but it is a bit tedious
    RandomListNode *copyRandomList1(RandomListNode *head) {
        if(!head) return nullptr;

        unordered_map<RandomListNode *, RandomListNode *> hashmap;

        RandomListNode * newhead=new RandomListNode(head->label);
        newhead->random = head->random;
        RandomListNode *p=head, *q=newhead;

        while(p){
            hashmap[p]=q;
            if(p->next){
                q->next = new RandomListNode(p->next->label);
                q=q->next;
                q->random = p->next->random;
            }
                p=p->next;
        }

        RandomListNode *t=newhead;

        while(t){
            t->random = hashmap[t->random];
            t=t->next;
        }

        return newhead;
    }

    ///////// cleaner version   ///////////////////
     RandomListNode *copyRandomList2(RandomListNode *head)
     {
         if(head == NULL)
             return NULL;

         unordered_map<RandomListNode *, RandomListNode *> m;
         m[head] = new RandomListNode(head -> label);
         for(RandomListNode *p = head; p -> next != NULL; p = p -> next)
         {
             ///// this logic is concise
             m[p -> next] = new RandomListNode(p -> next -> label);
             m[p] -> next = m[p -> next];
         }

         for(RandomListNode *p = head; p != NULL; p = p -> next)
            /// concise logic
             m[p] -> random = m[p -> random];

         return m[head];
     }

/////////////////// O 1 space solution, leetcode passed/////////
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return nullptr;

        RandomListNode * p=head;

        for(; p; p=p->next->next){  // for 循环比 while 好用， while 需要加上一些判断条件
            RandomListNode *tmp=p->next;
            p->next = new RandomListNode(p->label);
            p->next->next=tmp;
        }

        for(p=head; p; p=p->next->next){
            if(p->random) p->next->random = p->random -> next;
        }

        RandomListNode *newhead = head->next;
        RandomListNode *q;

        for(p=head; p;p=p->next, q=q->next){ // 要把原来的list 还原
            q=p->next;
            p->next=q->next;
            if(q->next) q->next=q->next->next; // 判断条件一定要加上！！
        }

        return newhead;
    }
};

int main()
{
    Solution s;

    RandomListNode* a = new RandomListNode(-1, new RandomListNode(2), nullptr);
    a->random=a->next;
    a->next->random = a;


    //RandomListNode* b = new RandomListNode(1, new RandomListNode(4, new RandomListNode(7, new RandomListNode(2, new RandomListNode(5, new RandomListNode(2, new RandomListNode(6, new RandomListNode(78))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=a;i!=nullptr;i=i->next)
        cout<<i->label<<",";
    cout<<endl;

    RandomListNode* c = s.copyRandomList3(a);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->label<<",";

}
