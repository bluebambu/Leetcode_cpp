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
    int singleNumber(vector<int>& nums) {
        int result=0;
        int n=sizeof(int)*8; // 要乘以8
        int count[n];
        fill_n(&count[0], n, 0);

        for(int i=0; i<nums.size(); ++i){
            for(int j=0; j<n; ++j){
                count[j]+=(((1<<j)&nums[i])>>j);
                // count[j]+= (nums[i]>>j)&1; 也是相同的效果
            }
        }

        for(int i=0; i<n; ++i){
            count[i]%=3;
        }

        for(int i=0; i<n; ++i){
            result+=count[i]<<i;
        }

        return result;
    }

/////////////////// Leetcode passed, ///////////////////////////////
    int singleNumber(vector<int>& nums) {
        if(nums.size()<4) return nums[0];

        vector<long> count(64, 0);  // 全部用long来防止溢出

        for(auto i : nums){
            for(int j=0; j<64; ++j){
                count[count.size()-j-1]+= (i>>j)&1;
            }
        }

        long result=0;

        for(int i=0; i<64; ++i){
            count[i]%=3;
            result+= (count[i]<<(63-i)); // 这个操作很好！ 不过上面的答案的对count的编排更加合理一些。
        }

        return result;
    }
};

int main()
{
    Solution a;

    vector<int> intset({3,3,3,5});

    auto b = a.singleNumber(intset);


            cout<<b<<" ";
     cout<<endl;

}
