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

struct TreeNode;
void print();

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}



class Solution
{
    struct LL{
        int val;
        LL* next;
        LL(int x):val(x), next(nullptr) {}
    };
public:
    LL* merge(LL* a, LL* b){
        LL* dummy = new LL(0);
        LL *p=a, *q=b, *r=dummy;

        while(p!=nullptr && q!=nullptr){
            if(p->val < q->val){
                r->next = p;
                p=p->next;
                r=r->next;
            }else{
                r->next = q;
                q=q->next;
                r=r->next;
            }
        }

        r->next = q? q : p ;
        return dummy->next;
    }

    void sortBottomUp(LL* a){

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


}
