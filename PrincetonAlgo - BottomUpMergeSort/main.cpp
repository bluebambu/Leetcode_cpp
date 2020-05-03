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

struct TreeNode
{
	TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
	TreeNode():val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);

    while(q.size()){
        auto tmp = q.front();
        cout<<tmp->val<<" ";
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
        q.pop();
    }
}



class Solution
{
    vector<int> aux;
public:
    void sort(vector<int>& a, int low, int high){
        if(low+1>=high) /// 必须是 low+1 >= high， 否则参考 【0，1） 区间, [0,1)
            return;
        int mid = low+(high-low)/2;
        sort(a, low, mid);
        sort(a, mid, high);
        merge(a, low, mid, high);
    }

    /// merge of [i, j)
    /// 该函数同样可以merge low-mid 和 mid-high 长度不一样的情况！！！！
    void merge(vector<int>& a, int low, int mid, int high){
        aux=a;

        int i=low, j=mid;
        for(int k=low; k<high; ++k){
            if(i>=mid)
                a[k]=aux[j++];
            else if(j>=high)
                a[k]=aux[i++];
            else if(aux[i]<aux[j])
                a[k]=aux[i++];
            else
                a[k]=aux[j++];
        }
    }


    /// bottomUp merge!!!!
    void sort2(vector<int>& a, int low, int high){
        for(int sz=1; sz<a.size(); sz*=2){
            for(int j=0; j+sz<a.size(); j+=2*sz){
                /// 必须是 j+sz<a.size(), 不能是 j+2*sz<a.size()
                merge(a, j, j+sz, min(j+2*sz, a.size()));
            }
        }
    }



};


int main()
{
	Solution aa;
	vector<int> bb={3,2,1};
	aa.sort2(bb, 0, bb.size());

	for(auto i:bb)
        cout<<i<<" ";


}
