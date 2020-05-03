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
    vector<int> getRow(int rowIndex) {
        vector<int> result;

        for(int i=0; i<=rowIndex; ++i){
            for(int j=i-1; j>0; --j){
                result[j]=result[j]+result[j-1];
            }
            result.push_back(1);
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
