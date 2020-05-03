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
    /// lc pass, bits operation
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        if(word.size()==0) return vector<string>(1, string());

        int size=word.size();

        for(int i=0; i<(1<<size); ++i){
            string tmp;

            for(int j=0; j<size; ){
                if(i>>j & 1){ // check every bits, if it is 1, find consecutive 1 s, then replace with number
                    int k=j;
                    while(i>>k & 1) ++k;

                    int consecutive = k-j;

                    string num = to_string(consecutive);
                    tmp.insert(tmp.end(), num.begin(), num.end());
                    j=k;

                }else{ // not bit 1, copy to tmp string
                    tmp.push_back(word[j]);
                    j++;
                }
            }

            result.push_back(tmp);
        }
        return result;
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
