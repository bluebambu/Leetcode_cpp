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
    /// other's answer


    /// not passed, can not handle "/..." case

    /// 将path看作这样： / /sd /ds /.. /...   , 然后第二个 /sd 最后拼接的时候要去掉 / ， 中间还有一些corner case 比如 results 里面只有“/”的时候不能删。

    string simplifyPath(string path) {
        if(path.empty()) return string();
        vector<string> results;
        results.push_back("/");

        for(int i=0; i<path.size(); ){
            while(i+1<path.size() && path[i+1]=='/') ++i; /// redundant backslash

            if(i+2<path.size() && path.substr(i, 3)=="/.."){  /// 要先检查 /..  再检查 /. , 想想为什么
                i=i+3;
                if(results.size()==1)
                    continue;
                else
                    results.pop_back();
            }else if(i+1<path.size() && path.substr(i, 2)=="/."){
                i=i+2;
                continue;
            }else if(i+1<path.size()){
                int j=i+1;
                while(j<path.size() && path[j]!='/') ++j;

                results.push_back(path.substr(i, j-i));
                i=j;
            }else /// 这一行必须有， 为的是最后一个元素是“/”， 不然死循环了
                ++i;
        }

        string str;
        for(int i=0; i<results.size(); ++i){
            if(results.size() > 1 && i==0) /// 如果results只包含 “/”， 则这一行不能运行
                str += results[i].substr(1, results[i].size()-1);
            else
                str += results[i];
        }

        return str;
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
