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

    ListNode* ReversePartList(ListNode *head, int m, int n)
    {
        if(m<1) return nullptr;
        if(m==n) return head;

        int num=0;
        ListNode *node_m, *node_n, *node_m_prev, *node_n_post;

        ListNode* dummy= new ListNode(-999, head);
        // 加一个头结点会方便很多，不用特殊考虑 m == 1的情况；

        for(ListNode* i=dummy;i!=nullptr;i=i->next)
        {
            if(num== m-1) {node_m_prev = i; node_m = i->next;}
            if(num== n) {node_n = i; node_n_post = i->next;}
            ++num;
        }

        ReverseEntireList(node_m, node_n);

        node_m_prev->next=node_n;
        node_m->next=node_n_post;

        return dummy->next;

    }

    void ReverseEntireList(ListNode* head, ListNode* tail)
    {
        ListNode *i, *j, *k;

        for(i=head,j=i->next;i!=tail;)
        {
            k=j->next;

            j->next=i;

            i=j;
            j=k;
        }
    }

    ListNode* ReversePartList2(ListNode *LL, int m, int n)
    {
        if(m>n) return ReversePartList2(LL, n, m);

        ListNode* head = new ListNode(-999, LL);
        ListNode* l_node_l=nullptr, *l_node_r=nullptr, *r_node=nullptr;
        ListNode* p=head;
        int i=0;

        while(i!=m-1)
        {
            p=p->next;
            ++i;
        }

        l_node_l=p;
        l_node_r=p->next;

        p=p->next;
        ++i;
        ListNode* q=p->next;
        ListNode* r=q->next;

        while(i!=n-1)
        {
            q->next=p;
            p=q;
            q=r;
            r=r->next;

            ++i;
        }

        q->next=p;

        l_node_l->next=q;
        l_node_r->next=r;

        return head->next;

    }

    ListNode* ReversePartList3(ListNode *LL, int m, int n)
    {
        if(m>n) return ReversePartList3(LL, n, m);

        ListNode* head1 = new ListNode(0, LL);
        ListNode* p = head1;

        for(int i=0; i<m && p; ++i)
        {
            p=p->next;
        }

        ListNode* lnode = p;
        ListNode* q=lnode->next;
        ListNode* r=q->next;

        for(int i=0; i<n-m; ++i) // q 一直都指着第m个元素，改变的是 q->next 和 r
        {
            q->next = r->next;
            r->next = lnode->next;
            lnode->next = r;
            r = q->next;
        }

        return head1->next;

    }

    ListNode* ReversePartList4(ListNode *LL, int m, int n){
        if(m>n) return ReversePartList4(LL, n, m);

        ListNode* head = new ListNode(-999, LL),
                  *head2 = head;

        int i=0, j=0;

        while(i< m-1 && head2){
        // 此处为 m-1
            head2=head2->next;
            ++i;
        }
        if(!head2) return nullptr;

        ListNode* p=head2->next, *q = p->next;

        while(1){
            p->next = q->next;
            q->next = head2->next;
            head2->next = q;
            ++j;

            if(j==n-1) // 此处是 n-1
                break;

            q=p->next;


        }

        return head->next;
    }
////////////////////// Leetcode passed //////////////////////////////
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(!head) return head;

        ListNode* dummy=new ListNode(9);
        dummy->next=head;

        ListNode *t=dummy;

        for(int i=1;i<m ; ++i)
            t=t->next;


        ListNode *p=t->next, *q=p->next;

        for(int i=m+1; i<=n ; ++i){
            p->next=q->next;
            q->next=t->next;
            t->next=q;
            q=p->next;
        }

        return dummy->next;
    }
};

int main()
{
    Solution s;

    ListNode* a = new ListNode(2, new ListNode(4, new ListNode(3)));

    ListNode* b = new ListNode(5, new ListNode(6, new ListNode(8, new ListNode(5, new ListNode(9, new ListNode(11, new ListNode(2)))))));

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->value<<",";
    cout<<endl;

    ListNode* c = s.ReversePartList4(b, 2, 5);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
