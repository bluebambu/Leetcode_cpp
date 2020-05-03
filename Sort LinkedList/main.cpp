#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


struct ListNode
{

    ListNode(int a, ListNode* b):val(a),next(b) {}
    ListNode(int a): val(a), next(nullptr) {}
    ListNode():val(0),next(nullptr) {}

    int val;
    ListNode* next;
};

class Solution
{
public:
    ListNode* insertionSortList(ListNode* head) {
        // insertion
        if(!head) return nullptr;
        ListNode* dummy = new ListNode(INT_MIN);
        dummy->next=head;

        for(ListNode* iter=head; iter->next;){
            ListNode* cur=iter->next;
            ListNode* iter2=dummy;
            for(; iter2->next->val<cur->val; iter2=iter2->next);

            if(iter2==iter){
                iter=iter->next;
                continue;
            }else{
                ListNode* tmp=cur->next;
                cur->next=iter2->next;
                iter2->next=cur;
                iter->next=tmp;
            }
        }
        return dummy->next;
    }

        ListNode* selectionSortList(ListNode* head) {
        // selection
        for(ListNode* iter=head; iter; iter=iter->next){
            long minval = LONG_MAX;
            ListNode* minnode=nullptr;
            for(ListNode* iter2=iter; iter2; iter2=iter2->next){
                if(minval>iter2->val){
                    minval=iter2->val;
                    minnode=iter2;
                }
            }

            if(minnode!=iter) swap(minnode->val, iter->val);
        }
        return head;
    }
/////////////////////////////  Quick Sort  ， 常规， 用最后一个做pivot 太麻烦////////////////////////
    ListNode* quickSortList(ListNode* head) {
        // quicksort
        if(!head) return nullptr;
        int len=0;
        ListNode* cur=head;
        while(cur->next){
            len++;
            cur=cur->next;
        }

        quick(head, 0, len);
        return head;
    }

    void quick(ListNode* head, int start, int end){
        if(start>=end) return;

        int pivot=idx(head, end)->val;
        ListNode* curnode=idx(head, start);
        int partition=end;

        for(int i=start; i<end; ++i){
            int curval=curnode->val;
            if(curval>pivot){
                ListNode* jnode=curnode->next;

                for(int j=i+1; j<end; ++j){
                    int jval=jnode->val;
                    if(jval < pivot){
                        swap(curnode->val, jnode->val);
                        break;
                    }
                    jnode=jnode->next;
                }

                if(jnode==idx(head, end)){
                    swap(curnode->val, idx(head, end)->val);
                    partition=i;
                    break;
                }
            }
            curnode=curnode->next;
        }

        quick(head, start, partition-1);
        quick(head, partition+1, end);
    }

    ListNode* idx(ListNode* head, int n){
        int idx=n;
        while(idx>0){
            head=head->next;
            idx--;
        }

        return head;
    }

//////////////////// better quicksort for linkedlist 用第一个做pivot ， time nlogn, space O(1) /////////////////////////////
////////////////////// Leetcode passed  ///////////////////////////////////////////////////
    ListNode* quickSortList2(ListNode* head) {
        // quicksort 2 , open end condition
        quick(head, NULL);
        return head;
    }

    void quick(ListNode* start, ListNode* end){
        if( start==end || start->next==end) return;
        ListNode* loc=start;
        int pivot=start->val;

        for(ListNode* iter=start->next; iter!=end; iter=iter->next){
            if(iter->val < pivot){
                loc=loc->next;
                swap(iter->val, loc->val);
            }
        }

        swap(start->val, loc->val);
        quick(start, loc);
        while(loc->next && loc->next->val == loc->val) loc=loc->next; /// skip duplicates
        quick(loc->next, end);
    }

///////////////// merge sort  //////////////////
    ListNode* mergeSortList(ListNode* head) {
        if(!head || !head->next) return head;
        // mergesort
        ListNode* fast=head, *slow=head;

        // 要先写fast->next, 再写 fast->next->next， 不然报错！！！！
        //  而且不能写成 fast && fast->next. fast 理应达不到 end
        for(;fast->next && fast->next->next; fast=fast->next->next, slow=slow->next);

        // 要断开
        ListNode* head2=slow->next;
        slow->next=NULL;

        fast=mergeSortList(head);
        slow=mergeSortList(head2);
        return merge(fast, slow);
    }

    ListNode* merge(ListNode* l1, ListNode* l2){
        ListNode* p1=l1, *p2=l2;
        ListNode* dummy=new ListNode(0), *p3=dummy;

        while(p1 && p2){
            if(p1->val < p2->val){
                p3->next=p1;
                p3=p3->next;
                p1=p1->next;
            }else{
                p3->next=p2;
                p3=p3->next;
                p2=p2->next;
            }
        }

        if(p1)
            p3->next=p1;
        else
            p3->next=p2;

        return dummy->next;
    }
////////////// merge sort 2, leetcode passed /////////////
    ListNode* sortList(ListNode* head) {
        // quicksort 2 , open end condition
        head=merge(head, nullptr);
        return head;
    }

    ListNode* merge(ListNode* start, ListNode* end){
        if(!start) return nullptr;
        if(start->next==end) return start;

        ListNode *fast=start, *slow=start;
        //  而且不能写成 fast && fast->next. fast 理应达不到 end
        for(;fast->next!=end && fast->next->next!=end; fast=fast->next->next, slow=slow->next);

        // 要断开
        ListNode* head2=slow->next;
        slow->next=nullptr;

        fast=merge(start, slow->next);
        slow=merge(head2, end);

        ListNode* dummy=new ListNode(0);
        ListNode* p=dummy;

        while(fast && slow){
            switch(fast->val < slow->val){
                case 1: p->next=fast; fast=fast->next;break;
                case 0: p->next=slow; slow=slow->next;break;
            }
            p=p->next;
        }

        p->next = !fast ? slow : fast;
        return dummy->next;
    }
};

int main()
{
    Solution s;

    ListNode* a = new ListNode(3, new ListNode(2, new ListNode(4)));

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(2, new ListNode(5, new ListNode(3, new ListNode(6, new ListNode(78))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=a;i!=nullptr;i=i->next)
        cout<<i->val<<",";
    cout<<endl;

    ListNode* c = s.mergeSortList(a);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->val<<",";
    cout<<endl;


}
