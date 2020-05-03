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
    //////// passed, 20ms /////////////////////
    int lengthOfLongestSubstring(string s) {
        if(s.empty()) return 0;

        int i=0, j=0, result=0;
        vector<bool> map(256, 0);  /// 256 x char!!!

        for(; j<s.size(); ++j){
            if(map[s[j]]==0){
                map[s[j]]=1;
            }else{
                while(s[i]!=s[j]){
                    map[s[i]]=0;
                    ++i;
                }
                ++i;
            }
            result = max(result, j-i+1);
        }
        return result;
    }


////////////////// 128ms  特别慢！ /////////////////////
    int lengthOfLongestSubstring(string s) {
        int longest=0;
        int len=0;
        vector<int> ch(256, -1);

        for(int i=0; i<s.size(); ++i){
            if(ch[s[i]]<0){
                ch[s[i]]=i;
                len++;
                longest=max(longest, len);
            }else{
                longest=max(longest, len);
                i=ch[s[i]];
                ch=vector<int>(256, -1);
                len=0;
            }
        }
        return longest;
    }

//////////////////// best answer ///////////////
int lengthOfLongestSubstring(char *s) {
    int m[129] = {0};
    int i, j;
    int cnt = 0, pre = 0;
    int max = 0;
    int c;

    for (i = 0; c = s[i]; i++) {
        if (pre < m[c]) {
            if (max < cnt)
                max = cnt;

            cnt = i-m[c];
            pre = m[c];
        }

        cnt++;
        // 数组储存的是字母在s的位置
        m[c] = i+1;
    }
    return max > cnt ? max : cnt;
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
