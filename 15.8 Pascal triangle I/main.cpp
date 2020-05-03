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


class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;

        for(int i=1; i<=numRows; ++i){
            if(i==1) result.push_back(vector<int>({1}));
            else if(i==2) result.push_back(vector<int>({1,1}));
            else{
                vector<int> temp{1,1};

                int last_len = result.back().size();

                for(int j=0; j+1<last_len; ++j){
                    temp.insert(temp.end()-1, result.back()[j]+result.back()[j+1]);
                }

                result.push_back(temp);
            }
        }
        return result;
    }

////////////////////// leetcode passed  ////////////////////////////
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;
        if(numRows<1) return result;

        result.push_back(vector<int>({1}));

        for(int i=1; i<numRows; ++i){
            vector<int> cur;
            for(int j=0; j<i+1; ++j){
                if(j==0)
                    cur.push_back(1);
                else if(j==i)
                    cur.push_back(1);
                else
                    cur.push_back(result[i-1][j-1]+result[i-1][j]);
            }
            result.push_back(cur);
        }
        return result;
    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.permute3(intset);

    for(auto i:b)
    {for(auto j: i)
            cout<<j<<" ";
     cout<<endl;
    }
}
