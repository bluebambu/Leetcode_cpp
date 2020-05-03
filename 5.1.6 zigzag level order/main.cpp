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


class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;

        zz(root, 1, result);
        return result;
    }

    void zz(TreeNode* root, int lvl, vector<vector<int>>& result){
        if(!root) return ;
        if(lvl > result.size())
            result.push_back(vector<int>());
        if(lvl%2!=0)
            result[lvl-1].push_back(root->val);
        else
            result[lvl-1].insert(result[lvl-1].begin(), root->val);

        zz(root->left, lvl+1, result);
        zz(root->right, lvl+1, result);

    }
/////////////////////////////////////////
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        vector<vector<int>> result;
        vector<int> layer;
        if(!root) return result;

        queue<TreeNode*> cur, next;
        cur.push(root);

        int idx=1;

        while(cur.size()){
            layer.clear();

            while(cur.size()){
                if(idx%2!=0)
                    layer.push_back(cur.front()->val);
                else
                    layer.insert(layer.begin(), cur.front()->val);
                if(cur.front()->left) next.push(cur.front()->left);
                if(cur.front()->right) next.push(cur.front()->right);

                cur.pop();
            }

            result.push_back(layer);
            swap(cur, next);
            idx++;
            cout<<idx;
        }

        return result;
    }
////////////////////////////////////////////////////////
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(!root) return result;

        vector<TreeNode*> cur, next;
        cur.push_back(root);

        int idx=0;

        while(1){
            result.push_back(vector<int>());

            for(int i=0; i<cur.size(); ++i){
                if(idx%2==0)
                    result.back().push_back(cur[i]->val);
                else
                    result.back().insert(result.back().begin(), cur[i]->val);

                if(cur[i]->left) next.push_back(cur[i]->left);
                if(cur[i]->right) next.push_back(cur[i]->right);
            }

            if(next.size()){
                swap(cur, next);
                next.clear();
                ++idx;
            }else
                break;
        }
        return result;
    }
};



int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(3,new TreeNode(6, new TreeNode(9), new TreeNode(1)),new TreeNode(4, new TreeNode(3), new TreeNode(4)));
    /*      3
        6       4
     9    1   3    4

    */

    auto b = a.LevelOrder6(tree);

    for(auto i:b)
        {for(auto j:i)
            cout<<j<<" ";
         cout<<endl;
        }
}
