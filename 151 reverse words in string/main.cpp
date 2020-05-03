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



class Solution {
public:
    ///////// leetcode passed ///////////
    // First, reverse the whole string, then reverse each word.
    void reverseWords(string &s) {
        reverse(s.begin(), s.end());
        int newidx=0;

        for(int i=0; i<s.size(); ++i){
            if(s[i]!=' '){
                if(newidx!=0) s[newidx++]=' ';
                int j=i;
                while(j<s.size() && s[j]!=' ') {
                    s[newidx++] = s[j];
                    ++j;
                }
                reverse(s.begin()+newidx-(j-i), s.begin()+newidx);
                i=j;
            }
        }
        s.erase(s.begin()+newidx, s.end());
    }

    /////////////  c++ solution///
    void reverseWords(string &s) {
        istringstream is(s);
        string tmp;
        s.clear();
        is >> s;
        while(is >> tmp) s = tmp + " " + s;
        if(s[0] == ' ') s = "";
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
