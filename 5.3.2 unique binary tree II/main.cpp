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
    vector<TreeNode*> generateTrees(int n) {
        if(n<1) return vector<TreeNode*>();
        return generate(1, n);
    }

    vector<TreeNode*> generate(int start, int end){
        vector<TreeNode*> subtree;
        if(start>end){
            subtree.push_back(nullptr);
            return subtree;
        }

        for(int k=start; k<=end; ++k){
            vector<TreeNode*> leftsubs = generate(start, k-1);
            vector<TreeNode*> rightsubs = generate(k+1, end);
            for(auto i : leftsubs){
                for(auto j : rightsubs){
                    TreeNode* node = new TreeNode(k);
                    node->left = i;
                    node->right = j;
                    subtree.push_back(node);
                }
            }

        }
        return subtree;
    }
//////////////////////////////////////////////////////////////////////////////////
private:
    TreeNode * clone(TreeNode * root){
        if(NULL == root) return NULL;
        TreeNode * newRoot = new TreeNode(root->val);
        newRoot->left = clone(root->left);
        newRoot->right = clone(root->right);
        return newRoot;
    }
    void addToLeft(TreeNode * oldRoot, TreeNode * newRoot, vector<TreeNode *> & results){
        TreeNode * cloneRoot = clone(oldRoot);
        newRoot->left = cloneRoot;
        results.push_back(newRoot);
    }
    void addRight(TreeNode * oldRoot, TreeNode * cur, TreeNode * newNode, vector<TreeNode *> & results){
        TreeNode *cloneRoot = clone(oldRoot);
        TreeNode *newCur = cloneRoot;
        while(NULL != newCur){
            if(newCur->val == cur->val) break;
            else newCur = newCur->right;
        }
        assert(NULL != newCur);
        TreeNode * temp = newCur->right;
        newCur->right = newNode;
        newNode->left = temp;
        results.push_back(cloneRoot);
    }

public:
    vector<TreeNode *> generateTrees(int n) {
        // DP:
        // for n-1 to n , for each n -1
        // 1) left to n
        // 2) for each right child down
        //    n replace right and right will be n left
        vector<TreeNode *> results;
        vector<TreeNode *> preResults(1, NULL);
        for(int i = 1; i <=n; i ++){
            for(int j = 0; j < preResults.size(); j++){
                // add n-1 left to n
                TreeNode * oldRoot = preResults[j];
                TreeNode * newRoot = new TreeNode(i);
                addToLeft(oldRoot, newRoot, results);
                TreeNode * cur = oldRoot;
                while(NULL != cur){
                    TreeNode *newNode = new TreeNode(i);
                    addRight(oldRoot, cur, newNode, results);
                    cur = cur->right;
                }
            }
            swap(results, preResults);
            results.clear();
        }
        return preResults;
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

    a.flatten(tree);


}
