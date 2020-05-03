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
    TreeNode(int a):val(a), left(nullptr), right(nullptr), next(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y),  next(nullptr) {}
    TreeNode():val(0), left(nullptr), right(nullptr), next(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *next;

};


class Solution
{
public:
    void connect(TreeNode* root) {
    // 不正确的答案
    // 无法处理 root->child 与 root->next->next->child 的链接
        if(!root) return;
        if(root->left)
            root->left->next = root->right;

        if(root->next && (root->left || root->right)){
            if(root->right                          && root->next->left)
                root->right->next = root->next->left;
            else if(!root->right && root->left      && root->next->left)
                root->left->next = root->next->left;
            else if(root->right                     && !root->next->left && root->next->right)
                root->right->next = root->next->right;
            else if(!root->right && root->left      && !root->next->left && root->next->right)
                root->left->next = root->next->right;
        }

        connect(root->left);
        connect(root->right);
        }
/////////////////////////////////////////////////////////////
        void connect(TreeLinkNode *root) {
            if (root == nullptr) return;

            TreeLinkNode dummy(-1);

            for (TreeLinkNode *curr = root, *prev = &dummy; curr; curr = curr->next) {
                if (curr->left != nullptr){
                    prev->next = curr->left;
                    prev = prev->next;
                }
                if (curr->right != nullptr){
                    prev->next = curr->right;
                    prev = prev->next;
                }
            }
            connect(dummy.next);
        }
/////////////////////////////////////////////////////////////
        void connect2(TreeLinkNode *root) {
                TreeLinkNode* cur=root;

                while(cur){
                    TreeLinkNode *head=nullptr, *nextlvlprev=new TreeLinkNode(-1);

                    while(cur){
                        if(head==nullptr && (cur->left || cur->right))
                            head=cur->left ? cur->left : cur->right;

                        if(cur->left){
                            nextlvlprev->next=cur->left;
                            nextlvlprev=nextlvlprev->next;
                        }
                        if(cur->right){
                            nextlvlprev->next=cur->right;
                            nextlvlprev=nextlvlprev->next;
                        }

                        cur=cur->next;
                    }
                    cur=head;
                }
        }
////////////////////////////////////////////////////////////
    void connect(TreeLinkNode *root) {
        TreeLinkNode *cur;
        TreeLinkNode *curhead=root, *nexthead=new TreeLinkNode(0);


        while(1){
            TreeLinkNode *nextiter=nexthead;
            for(cur=curhead; cur; cur=cur->next){
                if(cur->left){
                    nextiter->next=cur->left;
                    nextiter=nextiter->next;
                }
                if(cur->right){
                    nextiter->next=cur->right;
                    nextiter=nextiter->next;
                }
            }

            if(nexthead->next==nullptr)
                break;

            curhead=nexthead->next;
            nexthead->next=nullptr;
        }
    }
};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, nullptr,
                                                    nullptr),
                                    new TreeNode(8, new TreeNode(-3, nullptr,
                                                                     new TreeNode(9, nullptr,
                                                                                     new TreeNode(-5))),
                                                    new TreeNode(6)));
    /*      6
        3       8
     1    4   7    9

    */

    a.connect(tree);
}
