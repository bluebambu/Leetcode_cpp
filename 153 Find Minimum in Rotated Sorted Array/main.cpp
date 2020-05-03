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

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/


class Solution
{
public: // leetcode passed
    int findMin(vector<int>& nums) {
        if(nums.empty()) return 0;
        if(nums.size()==1) return nums[0];

        int start=0, end=nums.size()-1;

        while(1){
            int mid = start+(end-start)/2;

            if(start==mid) return nums[start]>nums[end] ? nums[end] : nums[start];

            if(nums[mid] > nums[end]){
                start=mid;
                continue;
            }else if(nums[mid]<nums[end]){
                end=mid;
                continue;
            }

        }
    }

};

int main()
{


}
