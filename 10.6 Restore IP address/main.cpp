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
////////////// leetcode passedd           ////////////////////////////
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        if(s.size()<4 || s.size()>12) return result;
        string path;
        dfs(s, 0, 0, path, result);
        return result;
    }

    void dfs(string& s, int cur, int idx, string& path, vector<string>& result){
        if(idx==4 && cur==s.size()){ /// conditions are necessary !
            result.push_back(path);
            return;
        }else if(idx<4 && cur<s.size()){

            for(int i=1; i<=3; ++i){
                string temp=s.substr(cur, i);
                string t_path=path;
                if(str2int(temp)<=255){
                    path+=temp;
                    if(idx<3) path+=".";
                    dfs(s, cur+i, idx+1, path, result);
                    path=t_path;
                }
            }

        }
    }

    int str2int(string str){
        if(str[0]=='0' && str.size()>1)
            return 256; /// very necessary, "012" is not valid!!!
        int n=str.size();
        int result=0;
        for(int i=0; i<n; ++i){
            result = result*10 + str[i]-'0';
        }
        return result;
    }


    ////////////// leetcode code, cool solution  /////////////
    // c++  code
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        string ans;

        for (int a=1; a<=3; a++)
        for (int b=1; b<=3; b++)
        for (int c=1; c<=3; c++)
        for (int d=1; d<=3; d++)
            if (a+b+c+d == s.length()) {
                int A = stoi(s.substr(0, a));
                int B = stoi(s.substr(a, b));
                int C = stoi(s.substr(a+b, c));
                int D = stoi(s.substr(a+b+c, d));
                if (A<=255 && B<=255 && C<=255 && D<=255)
                    /// test to make sure no "012" turns to "12"
                    if ( (ans=to_string(A)+"."+to_string(B)+"."+to_string(C)+"."+to_string(D)).length() == s.length()+3)
                        ret.push_back(ans);
            }

        return ret;
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
