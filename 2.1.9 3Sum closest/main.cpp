#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

class Solution
{
public:
    int threeSumClosest1(vector<int>& nums, int target){
        // 求 closest的时候，不能删除相同的数，因为你也不知道
        // 这几个相同的数加起来是不是比其他组合离目标更近

        int min_sum=9999, cur_sum=0;
        sort(nums.begin(), nums.end() );

        for(int i=0; i<nums.size()-2;++i){
            if(i>0 && nums[i]==nums[i-1])
                continue;

            for(int j=i+1, k=nums.size()-1; j<k;){
                cur_sum = nums[i]+nums[j]+nums[k];

                if(abs(cur_sum - target)<abs(min_sum - target)){
                    min_sum = cur_sum;

                }

                if(cur_sum > target) --k;
                else ++j;

            }
        }

        return min_sum;
    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {13,2,0,-14,-20,19,8,-5,-13,-3,20,15,20,5,
                    13,14,-17,-7,12,-6,0,20,-19,-1,-15,-2,8,
                    -2,-9,13,0,-3,-18,-9,-9,-19,17,-14,-19,-4,
                    -16,2,0,9,5,-7,-4,20,18,9,0,12,-1,10,-17,-11,
                    16,-13,-14,-3,0,2,-18,2,8,20,-15,3,-13,-12,-2,
                    -19,11,11,-10,1,1,-10,-2,12,0,17,-19,-7,8,-19,
                    -17,5,-5,-10,8,0,-12,4,19,2,0,12,14,-9,15,7,0,
                    -16,-5,16,-12,0,2,-16,14,18,12,13,5,0,5,6};
                // 0,1,2,3,4, 5, 6, 7,  8,  9,10, 11,12

    sort(d.begin(), d.end());

    for(auto i : d)
            cout<<i<<",";
        cout<<endl;




    auto i = a.threeSumClosest1(d, -59);

}
