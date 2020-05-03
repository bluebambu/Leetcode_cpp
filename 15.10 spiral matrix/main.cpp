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
    /// lc passed
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if(matrix.empty() || matrix[0].empty()) return result;

        int len=matrix.size(), wid=matrix[0].size();
        int beginX=0, beginY=0, endX=len-1, endY=wid-1;

        while(1){
            for(int i=beginY; i<=endY; ++i)
                result.push_back(matrix[beginX][i]);
            if(++beginX>endX) break;

            for(int i=beginX; i<=endX; ++i)
                result.push_back(matrix[i][endY]);
            if(--endY<beginY) break;

            for(int i=endY; i>=beginY; --i)
                result.push_back(matrix[endX][i]);
            if(--endX<beginX) break;

            for(int i=endX; i>=beginX; --i)
                result.push_back(matrix[i][beginY]);
            if(++beginY>endY) break;
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

    vector<vector<int>> matrix {{1,2,3,4,5,6,7,8,9,10},
                                {11,12,13,14,15,16,17,18,19,20}};
    auto b=a.spiralOrder(matrix);

    for(auto i:b)
        cout<<i<<" ";


}
