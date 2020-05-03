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
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;

        int wid = matrix.size(), len = matrix[0].size(), total = wid*len;

        int i=0, j=total;

        while(i<j){
            int mid = i+(j-i)/2;

            int x = mid/len, y = mid%len;

            if(matrix[x][y]==target)
                return true;
            else if(matrix[x][y]<target)
                i=mid+1;
            else
                j=mid;
        }

        return false;
    }

    ///////////////////////////////
    int Search2DMatrix(vector<vector<int>>& matrix, int target)
    {
        int row = matrix.size();
        int col = matrix[0].size();

        int p1=0, p2=row-1, p;
        int q1=0, q2=col-1, q;

        while(1)
        {
            int p_mid = (p1+p2)/2 ;

            if(matrix[p_mid][0]>target)
                p2=p_mid-1;
            else
                p1=p_mid+1;

            if(p1>=p2-1 && matrix[p1][0]<target)
            // 此处判断条件比较 tricky
                {
                    p=p1;
                    break;
                }
        }

        while(q1<q2)
        {
            int q_mid = (q1+q2)/2;

            if(matrix[p][q_mid]>target)
                q2=q_mid-1;
            else
                q1=q_mid+1;

            if(matrix[p][q_mid]==target)
                return true;
        }

            return false;



    }

    int Search2DMatrix2(vector<vector<int>>& matrix, int target)
    {
        if(matrix.empty())  return false;
        const int row = matrix.size();
        const int col = matrix.front().size();

        int first = 0;
        int last = row*col-1;

        while(first < last)
        {
            int mid = first + (last - first)/2;
            int value = matrix[mid/row][mid%row];

            if(value == target)
                return true;
            else if(value <target)
                first = mid + 1;
            else
                last = mid-1;
        }

        return false;
    }

};

int main()
{
    Solution a;

    vector<vector<int>> b {
                                {1, 3, 5, 7},
                            {10, 11, 16, 20},
                            {23, 30, 34, 50}
                          };

    auto c = a.Search2DMatrix(b, 3);

        cout<<c<<" ";
}
