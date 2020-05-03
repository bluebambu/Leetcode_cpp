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

/**
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

// 本质是inorder traversal， 不存入所有的节点，只存入左边的节点。
**/
//////////leetcode passed//////////
class BSTIterator {
    vector<TreeNode*> stack;

    void pushAll(TreeNode* node){
        for(;node; node=node->left)
            stack.push_back(node);
    }
public:
    BSTIterator(TreeNode *root) {
        pushAll(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return stack.size();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* tmp=stack.back();
        int ret = stack.back()->val;
        stack.pop_back();
        pushAll(tmp->right);
        return ret;
    }

};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

//////////////leetcode passed //////////
class BSTIterator2 {
public:
    BSTIterator2(TreeNode *root) {
        TreeNode* cur=root;
        while(cur){
            st.push(cur);
            cur=cur->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !st.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* node = st.top();
        int result;
        if( !node->right || node->right==prev){
            st.pop();
            result=node->val;
            prev=node;
        }else{
            TreeNode* cur=node->right;
            while(cur){
                st.push(cur);
                cur=cur->left;
            }
            result=next();
        }

        return result;
    }
private:
    stack<TreeNode*> st;
    TreeNode* prev=nullptr;
};

/// Morris inorder traversal
/// https://maskray.me/blog/2014-06-29-leetcode-solutions

class BSTIterator3 {
public:
  TreeNode *x;

  BSTIterator3(TreeNode *t) : x(t) {}

  /** @return whether we have a next smallest number */
  bool hasNext() {
    return x != NULL;
  }

  /** @return the next smallest number */
  int next() {
    int r;
    for(;;) {
      TreeNode *y = x->left;
      if (y) {
        while (y->right && y->right != x)
          y = y->right;
        if (y->right)
          y->right = NULL;
        else {
          y->right = x;
          x = x->left;
          continue; /// key
        }
      }
      r = x->val;
      x = x->right;
      break;  /// key
    }
    return r;
  }
};

///////////// leetcode passed ////////////////////
class BSTIterator {
public:
    TreeNode* cur=nullptr;

    BSTIterator(TreeNode *root):cur(root) {

    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return cur;
    }

    /** @return the next smallest number */
    int next() {
        int result;
        while(cur){
            if(!cur->left){
                result=cur->val;
                cur=cur->right;
                break;
            }
            else{
                TreeNode* node=cur->left;
                while(node->right && node->right!=cur)
                    node=node->right;
                if(node->right==nullptr){
                    node->right=cur;
                    cur=cur->left;
                    continue;
                }else{
                    result=cur->val;
                    node->right=nullptr;
                    cur=cur->right;
                    break;
                }
            }
        }
        return result;
    }
};




int main()
{


//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */
    BSTIterator2 a(tree);

    while(a.hasNext())
        cout<<a.next();




}
