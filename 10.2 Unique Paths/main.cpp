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
//    int uniquePaths(int m, int n)
//    {
//        if(m<1 || n<1) return 0;
//        if(m==1 && n==1) return 1;
//
//        return uniquePaths(m-1, n) + uniquePaths(m, n-1);
//    }

    vector<vector<int>> buff{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
    // 不能在这里用 vector<vector<int>> intset (3, vector<int>(3,7)); 来声明buff，
    // 可能是因为 class 内部mem function的调用次序的关系。

    int uniquePaths2(int m, int n)
    {
        if(m<0 || n<0) return 0;
        if(m==0 && n==0) return buff[0][0]=1;

        if(buff[m][n]>0) return buff[m][n];
        else
        {
            buff[m][n]=uniquePaths2(m-1, n)+uniquePaths2(m, n-1);
            return buff[m][n];
        }
    }

};


int main()
{
    Solution a;

    vector<vector<int>> intset (3, vector<int>(3,7));

    auto b = a.uniquePaths2(2,6);


            cout<<b<<" ";
     cout<<endl;

}
