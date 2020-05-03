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
public:
    ////////// leetcode passed /////////////
    typedef unordered_map<int, int>::iterator UI;

    struct comp{
        bool operator() (UI& a, UI& b){
            return a->second > b->second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result;
        if(nums.empty()) return result;

        unordered_map<int, int> map;
        for(int i=0; i<nums.size(); ++i){
            ++map[nums[i]];
        }

        priority_queue<UI, vector<UI>, comp> pq;

        for(auto iter=map.begin(); iter!=map.end(); ++iter){
            if(pq.size()<k)  /// 注意逻辑！
                pq.push(iter);
            else if(pq.top()->second < iter->second){
                pq.pop();
                pq.push(iter);
            }
        }

        while(!pq.empty()){
            result.push_back(pq.top()->first);
            pq.pop();
        }

        return result;
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
