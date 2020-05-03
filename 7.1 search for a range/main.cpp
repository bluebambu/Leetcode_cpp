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
///////////////// leetcode passed  /////////////
     vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return vector<int>();
        int low = lower(nums, 0, nums.size(), target);
        int high = higher(nums, low, nums.size(), target);

        if(nums[low]!=target || low==nums.size())
            return vector<int>({-1, -1});
            else
            return vector<int>({low, high-1});
    }

    int lower(vector<int>& nums, int start, int end, int target){
        while(start!=end){
            int mid=start+(end-start)/2;

            if(target <= nums[mid])
            end=mid;
            else
            start=mid+1;
        }

        return start;
    }

    int higher(vector<int>& nums, int start, int end, int target){
        while(start!=end){
            int mid=start+(end-start)/2;

            if(target < nums[mid])
            end=mid;
            else
            start=mid+1;
        }

        return start;
    }

///////////// better from mkyforever  /////////////////
     vector<int> searchRange(int A[], int n, int target)
     {
         int l1 = 0, r1 = n - 1, m1;
         while(l1 <= r1)
         {
             m1 = (l1 + r1) / 2;
             if(target <= A[m1])
                 r1 = m1 - 1;
             else
                 l1 = m1 + 1;
         }

         int l2 = 0, r2 = n - 1, m2;
         while(l2 <= r2)
         {
             m2 = (l2 + r2) / 2;
             if(target >= A[m2])
                 l2 = m2 + 1;
             else
                 r2 = m2 - 1;
         }

         if(l1 <= r2)
             return vector<int>{l1, r2};
         else
            return vector<int>{-1, -1};
     }
};

class Solution2 {
public:
    /// my own answer, lc passed, not bad
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result;
        if(nums.empty()) return result;

        int n=nums.size();
        int i=0, j=n;
        int mid=0;
        while(i<j){
            mid = i+(j-i)/2;
            if(nums[mid]<target)
                i=mid+1;
            else
                j=mid;
        }
        if(nums[j]!=target) result.push_back(-1);
        else result.push_back(j);

        i=0, j=n;
        mid=0;
        while(i<j){
            mid = i+(j-i)/2;
            if(nums[mid]<=target)
                i=mid+1;
            else
                j=mid;
        }
        if(nums[j-1]!=target) result.push_back(-1);
        else result.push_back(j-1);

        return result;
    }
};


int main()
{
    Solution a;


}
