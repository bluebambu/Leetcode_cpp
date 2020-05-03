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
    ListNode* RotateRight(ListNode* head, int k)
    // 先遍历一遍，得出链表长度 l en，注意 k 可能大于 l en，
    // 因此令 k% = l en。将尾节点 next 指针指向首节点，形成
    // 一个环，接着往后跑 l en − k 步，从这里断开，就是要求的
    // 结果了。

    {
        int len=0;
        ListNode* i=head;

        for(;i->next!=nullptr;i=i->next)
            ++len;
        ++len;

        i->next = head;

        k %= len;

        for(int j=0; j<len-k;++j)
        {
            i=i->next;
        }

        ListNode* tmp = i->next;

        i->next = nullptr;

        return tmp;

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

    ListNode* c = s.RotateRight(b, 14);

    for(auto i=c;i!=nullptr;i=i->next)
        cout<<i->value<<",";

}
