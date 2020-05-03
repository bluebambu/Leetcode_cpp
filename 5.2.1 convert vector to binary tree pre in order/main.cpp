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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return f(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }

    TreeNode* f(vector<int>& preorder, int pi, int pj, vector<int>& inorder, int ii, int ij){
        if(pi>=pj || ii>=ij)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[pi]);
        int in_idx=ii;
        while(in_idx<ij  &&  inorder[in_idx]!=preorder[pi]) ++in_idx;

        int distance = in_idx  - ii; /// 相对distance 是关键， 而不是绝对位置

        root->left = f(preorder, pi+1, pi+distance+1, inorder, ii, in_idx);
        root->right = f(preorder, pi+distance+1, pj, inorder, in_idx+1, ij);
        return root;
    }
///////////////////////////////////////////////////////////////////////////////
//    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//
//    int preStart = 0;
//
//    public TreeNode buildTree(int[] preorder, int[] inorder) {
//        if(preorder.length == 0 || inorder.length == 0) return null;
//        return helper(0,inorder.length - 1,preorder,inorder);
//    }
//
//    private TreeNode helper(int inStart, int inEnd, int[] preorder, int[] inorder){
//        // Base情况
//        if(preStart > preorder.length || inStart > inEnd){
//            return null;
//        }
//        TreeNode root = new TreeNode(preorder[preStart]);
//        int inMid = 0;
//        // 找到根在中序序列中的位置，从而知道先序中的分割点
//        for(int i = inStart ; i <= inEnd; i++){
//            if(inorder[i] == preorder[preStart]){
//                inMid = i;
//            }
//        }
//        preStart++;
//        // 例如先序序列 1(234)(567) 中2是左子树的根
//        root.left = helper(inStart, inMid - 1, preorder, inorder);
//        // 先序序列 1(234)(567) 中5是右子树的根
//        root.right = helper(inMid + 1, inEnd, preorder, inorder);
//        return root;
//    }
//    }

//////////////////////////////////////////////////////////////////////////////
    TreeNode* buildTreeUtil(vector<int>& preorder, int preS, int preE,
                        vector<int>& inorder, int inS, int inE,
                        unordered_map<int, int>& hmap) {

        if(preS > preE || inS > inE) return nullptr;
        TreeNode* root;
        if(preS == preE) {
            root = new TreeNode(preorder[preS]);
            return root;
        }
        int idx = hmap[preorder[preS]];

        root = new TreeNode(preorder[preS]);

        int len=idx-inS;

        root->left = buildTreeUtil(preorder, preS+1, preS+len, inorder, inS, idx-1, hmap);
        root->right = buildTreeUtil(preorder, preS+len+1, preE, inorder, idx+1, inE, hmap);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() != inorder.size())
            return nullptr;

        unordered_map<int, int> hmap;

        for(int i=0; i<inorder.size(); i++)
            hmap[inorder[i]] = i;

        return buildTreeUtil(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1, hmap);
    }

////////////////// iterative , 太难  //////////////////////////////////////////////
////The idea is as follows:
////
////1) Keep pushing the nodes from the preorder into a stack (and keep making the tree by adding nodes to the left of the previous node) until the top of the stack matches the inorder.
////
////2) At this point, pop the top of the stack until the top does not equal inorder (keep a flag to note that you have made a pop).
////
////3) Repeat 1 and 2 until preorder is empty. The key point is that whenever the flag is set, insert a node to the right and reset the flag.
////
////我的理解： 如果stack.top)()== inorder.at(pin), 则stack.top()一定是一个左下角的元素，左子树为nullptr。 这样的话，它在preorder里面的下一个元素必是它的右子树！！ 见line 138， p->right = new TreeNode(preorder.at(ppre));

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (preorder.size() == 0) return NULL;
        int ppre = 0, pin = 0;
        TreeNode *root = new TreeNode(preorder.at(ppre++));
        TreeNode *p = NULL;
        stack<TreeNode *> roots;
        roots.push(root);

        while (true) {
            if (inorder.at(pin) == roots.top()->val) {
                p = roots.top();
                roots.pop();
                pin++;
                if (pin == inorder.size()) break;
                if (roots.size() && inorder.at(pin) == roots.top()->val) continue;
                p->right = new TreeNode(preorder.at(ppre));
                ppre++;
                roots.push(p->right);
            }
            else {
                p = new TreeNode(preorder.at(ppre));
                ppre++;
                roots.top()->left = p;
                roots.push(p);
            }
        }

        return root;
    }
};

int main()
{
    Solution a;
    vector<int> b = { 1, 2, 3 };
    vector<int> c = { 2, 1, 3 };

    a.buildTree(b, c);


}
