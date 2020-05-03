// C program to print all permutations with duplicates allowed
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */

void permute2(vector<int>& a, int l, int r)
{
   if (l == r)
     {for( auto i : a) cout<<i<<" "; cout<<endl;}
   else
   {
       for (int i = l; i <= r; i++)
       {
          swap(a[l], a[i]);
          permute2(a, l+1, r);
          swap(a[l], a[i]); //backtrack
       }
   }
}

void permute3(vector<int> intset, int left, int right)
{
    if(left==right)
    {
        for( auto i : intset)
            cout<<i<<" ";
        cout<<endl;
    }

    for(int i=left; i<=right; ++i)
    {
        swap(intset[left], intset[i]);
        permute3(intset, left+1, right);
        swap(intset[left], intset[i]);
    }
}

////////////////////////////////////////////////////////////////////////
    void sub(vector<int> nums, int start, vector<vector<int>>& result){
        if(start==nums.size()-1) {
            result.push_back(nums);
            return;
        }

        for(int i=start; i<nums.size(); ++i){

            if(i!=start && nums[i]==nums[start]) continue;
            swap(nums[start], nums[i]);
            sub(nums, start+1, result);
            if(start==1){
            for(auto j:nums){
            cout<<j<<" ";
            }
            cout<<endl;}
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        sub(nums, 0, result);
        return result;
    }




/* Driver program to test above functions */
int main()
{
//    char str[] = "ABC";
//    int n = strlen(str);
    vector<int> str {1,2,3};
    permute3(str, 0, str.size()-1);

//    for(auto i:a){
//        for(auto j:i){
//            cout<<j<<" ";
//        }
//        cout<<endl;
//    }
}
