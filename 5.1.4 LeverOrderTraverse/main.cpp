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


struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};


class Solution
{
public:
    vector<vector<int>> LevelOrder(TreeNode* root)
    {
        vector<vector<int>> val_output;
        vector<queue<TreeNode*>> node_queue;

        int i=0;
        TreeNode* tmp=root;
        node_queue.push_back(queue<TreeNode*>());
        node_queue[0].push(tmp);
        val_output.push_back(vector<int>());

        while(!(node_queue[i].empty() && i==node_queue.size()-1))
        {
            if(node_queue[i].empty()) ++i;

            tmp = node_queue[i].front();
            node_queue[i].pop();

            if(i>val_output.size()-1)
                    val_output.push_back(vector<int>());

            val_output[i].push_back(tmp->val);

            if((tmp->left || tmp->right) && i==node_queue.size()-1)
            {
                node_queue.push_back(queue<TreeNode*>());
            }

            if(tmp->left) node_queue[i+1].push(tmp->left);
            if(tmp->right) node_queue[i+1].push(tmp->right);

        }

        return val_output;
    }

    vector<vector<int>> LevelOrder2(TreeNode* root)
    {
        vector<vector<int>> result;
        LvlTraverse(root, 1, result);
        return result;
    }

    void LvlTraverse(TreeNode* root, int level, vector<vector<int>>& result)
    {
        if(!root) return;

        if(level > result.size()) result.push_back(vector<int>());

        result[level-1].push_back(root->val);
        LvlTraverse(root->left, level+1, result);
        LvlTraverse(root->right, level+1, result);
    }


    vector<vector<int>> LevelOrder3(TreeNode* root)
    {
        vector<vector<TreeNode*>> vecnode;
        vecnode.push_back(vector<TreeNode*>());
        vecnode[0].push_back(root);

        int i=0;

        while(1)
        {
            vecnode.push_back(vector<TreeNode*>());

            for(auto p : vecnode[i])
            {
                if(p->left) vecnode[i+1].push_back(p->left);
                if(p->right) vecnode[i+1].push_back(p->right);
            }

            ++i;

            if(!vecnode[i].size()) break;
        }

        vector<vector<int>> result(vecnode.size());

        for(int i=0; i<result.size(); ++i)
        {
            for(auto j : vecnode[i])
                result[i].push_back(j->val);
        }

        return result;
    }


    vector<vector<int>> LevelOrder4(TreeNode* root)
    {
        vector<vector<int>> result;
        int lvl=0;

        LevelOrderbyLevel(root, lvl, result);

        return result;
    }

    void LevelOrderbyLevel(TreeNode* node, int level, vector<vector<int>> & result)
    {
        if(!node) return;

        if(result.empty() || level > result.size()-1) result.push_back(vector<int>());
        // 如果 result 为空，result.size() 也会 throw error ！！！

        result.at(level).push_back(node->val);

        if(node->left) LevelOrderbyLevel(node->left, level+1, result);
        if(node->right) LevelOrderbyLevel(node->right, level+1, result);
    }

    vector<vector<int>> LevelOrder5(TreeNode* root)
    {
        vector<vector<TreeNode*>> nodevec;
        vector<vector<int>> result;

        nodevec.push_back(vector<TreeNode*>{root});

//        nodevec[0].push_back(root);

        int i=0;

        while(1)
        {
            nodevec.push_back(vector<TreeNode*>());

            for( auto node : nodevec[i] )
            {
                if(node->left) nodevec[i+1].push_back(node->left);
                if(node->right) nodevec[i+1].push_back(node->right);
            }


            ++i;

            if(!nodevec[i].size()) break;

        }

        for(int m=0; m<nodevec.size(); ++m)
            for(int n=0; n<nodevec[m].size(); ++n)
        {
            if(result.size()< m+1) result.push_back(vector<int>());

            result[m].push_back(nodevec[m][n]->val);
        }

        return result;
    }

    /// recursion solution  ////////
    vector<vector<int>> LevelOrder6(TreeNode* root)
    {
        vector<vector<int>> result;
        int Level=0;

        LevelOrderbyLevel2(root, Level, result);
        return result;
    }

    void LevelOrderbyLevel2(TreeNode* node, int Level, vector<vector<int>> & result)
    {
        if(node==nullptr) return;

        if(result.size() < Level+1) result.push_back(vector<int>());

        result[Level].push_back(node->val);

        LevelOrderbyLevel2(node->left, Level+1, result);
        LevelOrderbyLevel2(node->right, Level+1, result);
    }

//////////// leetcode passed, only use 1 queue  //////////
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(!root) return result;
        queue<TreeNode*> q;
        q.push(root);


        while(q.size()){
            int n=q.size();
            vector<int> tmp;

            for(int i=0; i<n; ++i){
                tmp.push_back(q.front()->val);
                if(q.front()->left) q.push(q.front()->left);
                if(q.front()->right) q.push(q.front()->right);
                q.pop();
            }

            result.push_back(tmp);
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
