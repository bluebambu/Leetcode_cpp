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

class Solution2 {
public:
    //// passed
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        int i, j;

        while(lists.size()>1){
            i=0, j=lists.size()-1;

            for(; i<j;++i,--j){
                lists[i] = merge(lists[i], lists[j]);
                lists.pop_back();
            }
        }
        return lists[0];
    }

    ListNode* merge(ListNode* a, ListNode* b){
        if(!a || !b) return a ? a : b;
        ListNode *dummy = new ListNode(0), *p=dummy;

        while(a && b){
            if(a->val < b->val){
                p->next=a;
                a=a->next;
            }else{
                p->next=b;
                b=b->next;
            }
            p=p->next;
        }

        p->next = a? a:b;
        return dummy->next;
    }
};


class Solution
{


public:
    ////////////////////Leetcode passed  ///////////////////////
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return NULL;
        int n=lists.size();

        struct comparator{
            bool operator()(ListNode* a, ListNode* b){
                return a->val > b->val;
            }
        };
        // priority queue can only use functor typename, not functor obj.
        priority_queue<ListNode*, vector<ListNode*>, comparator> pque;

        for(int i=0; i<n ; ++i){
            if(lists[i]) pque.push(lists[i]);
        }

        ListNode* dummy = new ListNode(0);
        ListNode* p=dummy;

        while(pque.size()){
            ListNode* tmp=pque.top();
            pque.pop();
            if(tmp->next)
                pque.push(tmp->next);

            p->next=tmp;
            p=p->next;

        }
        return dummy->next;
    }


    ////////////////////////////////////////////////////////////
    /////////////////// Using priority queue ///////////////
    struct compare {
        bool operator()(const ListNode* l, const ListNode* r) {
            return l->val > r->val;
        }
    };

    ListNode *mergeKLists1(vector<ListNode *> &lists) {
        priority_queue<ListNode *, vector<ListNode *>, compare> q;
        for (auto l : lists) {
            if (l) {
                q.push(l);
            }
        }

        if (q.empty()) {
            return NULL;
        }

        ListNode* result = q.top();
        q.pop();
        if (result->next) {
            q.push(result->next);
        }

        ListNode* tail = result;
        while (!q.empty()) {
            tail->next = q.top();
            q.pop();
            tail = tail->next;
            if (tail->next) {
                q.push(tail->next);
            }
        }

        return result;
    }

//////////////// Leetcode passed, nlogn, merge 1st and last ////////////
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;

        while(lists.size()>1){
            int n=lists.size();
            int i=0, j=n-1;
            for(;i<j;++i, --j){
                lists[i] = merge2(lists[i], lists[j]);
                lists.pop_back();
            }
        }

        return lists[0];
    }

    ListNode* merge2(ListNode* l1, ListNode* l2){
        ListNode* dummy=new ListNode(0);
        ListNode* p=dummy, *p1=l1, *p2=l2;

        for(;p && p1 && p2;p=p->next){ /// need to check p1 & p2 !!
            if(p1->val < p2->val){
                p->next=p1;
                p1=p1->next;
            }else{
                p->next=p2;
                p2=p2->next;
            }
        }

        p->next = p1 ? p1 : p2;  /// necessary step!

        return dummy->next;
    }

//////////////////// Use merge 2 sorted list to achieve ///  过不了大数据集合 ！！  ////////////////////
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if(lists.empty()){
            return nullptr;
        }
        while(lists.size() > 1){
            lists.push_back(mergeTwoLists(lists[0], lists[1]));
            lists.erase(lists.begin());
            lists.erase(lists.begin());
        }
        return lists.front();
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if(l1 == nullptr){
            return l2;
        }
        if(l2 == nullptr){
            return l1;
        }
        if(l1->val <= l2->val){
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else{
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

//////////////////////// 暴力法， 过不了大数据集合 /////////////////////////
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;

        ListNode* p = lists[0];

        for(int i=1; i<lists.size(); ++i)
            p=merge(p, lists[i]);

        return p;
    }

    ListNode* merge(ListNode* p1, ListNode* p2){
        if(!p1 && !p2) return nullptr;
        if(!p1 || !p2) return p1? p1 : p2;

        ListNode* dummy = new ListNode(0);
        ListNode* q = dummy;

        while(p1 && p2){
            if(p1->val < p2->val){
                q->next=p1;
                p1=p1->next;
                q=q->next;
            }else{
                q->next=p2;
                p2=p2->next;
                q=q->next;
            }
        }

        q->next = p1 ? p1 : p2;

        return dummy->next;
    }
};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    a.mergeKLists1();


}
