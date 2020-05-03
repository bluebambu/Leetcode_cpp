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
    int maxProduct(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];

        int tmp=0,maxres=1, minres=1;
        int result=-999;

        for(int i=0; i<nums.size(); ++i){
            tmp=maxres;

            maxres=max(nums[i], max(maxres*nums[i], minres*nums[i]));
            minres=min(nums[i], min(tmp*nums[i], minres*nums[i]));

            result=max(result, maxres);
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
