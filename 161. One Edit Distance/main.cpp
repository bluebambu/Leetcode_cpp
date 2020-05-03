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


class Solution {
public:
    // passed leetcode
    bool isOneEditDistance(string s, string t) {
        if(s.size() == t.size()){ // when 2 strings have same size
            int fault=0;
            for(int i=0; i<s.size(); ++i){
                if(s[i]==t[i])
                    continue;
                fault++;
            }
            return fault==1; // only one mismatch is allowed
        }else if(s.size() < t.size()){
            return isOneEditDistance(t,s);
        }else if(s.size() == t.size() + 1){ // when 2 strings have different size, only 1 size diff is allowed
            int fault=0;
            for(int i=0; i<s.size(); ++i){
                if(i-fault>=t.size()) // in case the additional char is at the end
                    fault++;
                else if(s[i]==t[i-fault]) // consider the position offset
                    continue;
                else
                    fault++;
            }
            return fault==1; // only one position offset is allowed
        }else
            return false;
    }

    // much more concise solution
    bool isOneEditDistance(string s1, string t1) {
        char *s=&s1[0], *t=&t1[0];
        while (*s == *t && *s)
            ++s, ++t;
        int a = strlen(s),
            b = strlen(t);
        return *s != *t && !strcmp(s+(a>=b), t+(b>=a));
        /// strcmp return 0 when two strings are same
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
