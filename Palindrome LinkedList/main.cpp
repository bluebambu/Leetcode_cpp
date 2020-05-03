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


 // Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
      ListNode(int x, ListNode* y) : val(x), next(y) {}
 };

class Solution
{
public:
    /////////// 从头到尾生成一个反序的list， 效率太低！！ ////////////////////////
    bool isPalindrome(ListNode* head) {
        if(head==NULL || head->next==NULL) return true;

        ListNode* i=head, *j=new ListNode(head->val);

        while(i->next!=NULL){
            ListNode* tmp=new ListNode(i->next->val);
            tmp->next=j;
            j=tmp;
            i=i->next;
        }

        i=head;

        while(i->next){
            if(i->val != j->val)
                return false;
            i=i->next;
            j=j->next;
        }

        return true;
    }

///////////////// Leetcode passed , 中间折断，然后后半部分反序， 前后再对比 ！ /////////////////////////
    bool isPalindrome(ListNode* head) {
        if(!head) return true;

        ListNode *fast=head, *slow=head;

        for(; fast->next && fast->next->next; slow=slow->next, fast=fast->next->next);

        fast=slow->next;
        slow->next=nullptr;
        slow=head;
        fast = reverse(fast);


        while(slow && fast){
            if(slow->val != fast->val)
                return false;
            slow=slow->next;
            fast=fast->next;
        }
        return true;
    }

    ListNode* reverse(ListNode*& head){
        if(!head) return nullptr;
        ListNode *pre=NULL, *cur=head, *next;

        while(head){
            next=head->next;
            head->next=pre;
            pre=head;
            head=next;
        }
        return pre;
    }
};


int main()
{
    Solution a;

    ListNode* b = new ListNode(1, new ListNode(4, new ListNode(7, new ListNode(2, new ListNode(2, new ListNode(7, new ListNode(4, new ListNode(1))))))));

//    for(auto i=a;i!=nullptr;i=i->next)
//        cout<<i->value<<",";
//    cout<<endl;

    for(auto i=b;i!=nullptr;i=i->next)
        cout<<i->val<<",";
    cout<<endl;

    auto c =a.isPalindrome(b);

//    for(auto i=c;i!=nullptr;i=i->next)
        cout<<c<<",";
}
