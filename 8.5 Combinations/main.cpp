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
    ////////// leetcode passed, ///////////////
    // 8ms
    vector<vector<int>> combine(int n, int k) {

        vector<vector<int>> result;
        if(n<k) return result;
        vector<int> path;

        dfs(n, k, 1, 1, path, result);
        return result;
    }

    void dfs(int n, int k, int start, int passed, vector<int>& path, vector<vector<int>>& result){
        if(passed==k+1){
            result.push_back(path);
            return;
        }

        // n-k+passed get rid of unnecessary search
        for(int i=start; i<=n-k+passed; ++i){
            path.push_back(i);
            dfs(n, k, i+1, passed+1, path, result);
            path.pop_back();
        }
    }
    //////////////////////////////////////////////////////



    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> result;
        vector<int> path;

//        combine_main(n,k, path, result);
        combine_main2(n, k, 1, 0, path, result);

        return result;
    }

    void combine_main(int n, int k, vector<int> path, vector<vector<int>>& result)
    {
        if(path.size()==k)
        {
            result.push_back(path);
            return;
        }

        for(int i=1; i<=n; ++i)
        {
            if(find(path.begin(), path.end(),i)==path.end() && (path.empty() || i>path.back()))
            {
                path.push_back(i);
                combine_main(n, k, path, result);
                path.pop_back();
            }
        }
    }


    void combine_main2(int n, int k, int start, int cur,
                      vector<int> path, vector<vector<int>>& result)
    {
        if(cur==k)
            result.push_back(path);

        for(int i=start; i<=n; ++i)
        {
            path.push_back(i);
            combine_main2(n, k, i+1, cur+1, path, result);
            path.pop_back();
        }
    }
///////////////////////////////////////////////////////////////////
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> path;
        dfs(n, k, 1, path, result);
        return result;
    }

    void dfs(int n, int k, int start, vector<int>& path, vector<vector<int>>& result){
        if(path.size()==k){
            result.push_back(path);
            return;
        }

        for(int i=start; i<=n; ++i){
            path.push_back(i);
            dfs(n, k, i+1, path, result);
            path.pop_back();
        }
    }

};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.combine(4,2);

    for(auto i:b)
    {for(auto j: i)
            cout<<j<<" ";
     cout<<endl;
    }
}
