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
    int searchInsert(vector<int>& nums, int target) {
        int left=0, right=nums.size()-1, mid;

        while(left<=right){
            mid=left+(right-left)/2;

            if(nums[mid]==target) return mid;
            else if(nums[mid]>target)
                right=mid-1;
            else
                left=mid+1;
        }

        return left;
    }
};

int main()
{
    Solution a;


}
