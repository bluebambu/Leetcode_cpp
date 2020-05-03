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
    int nthUglyNumber(int n) {
        if(n==0) return 0;
        vector<int> ugly(1, 1);

        int p2=0, p3=0, p5=0;
        while(ugly.size()<n){
            int m2=ugly[p2]*2, m3=ugly[p3]*3, m5=ugly[p5]*5;
            int minin=min(m2, min(m3, m5));
            if(minin==m2) ++p2;
            if(minin==m3) ++p3;
            if(minin==m5) ++p5;

            ugly.push_back(minin);
        }

        return ugly.back();
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
