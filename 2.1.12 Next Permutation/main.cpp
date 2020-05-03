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
    void nextPermutation(vector<int> &num)
    {
        if(!num.size()) return;
        if(num.size()==1) return;

        auto i=num.end()-1;

        while(*(i-1)>*i)
        {
            if(i==num.begin()) {cout<<"Last Permutation"<<endl; return;}
            --i;
        }

        auto j=num.end()-1;

        while(*j < *(i-1))
        {
            --j;
        }

        swap(*(i-1), *j);

        sort(i,num.end());

    }

    void nextPermutation2(vector<int> &num)
    {
        int n=num.size()-1;
        int p=n;
        int change=99999;
        int changeID=-1;
        int j=n;

        while(num[p-1]>num[p])
            --p;

        for( ; j>=p ; --j)
        {
            if(num[j]>num[p-1])
            {
                if(num[j]<change)
                {
                    change = num[j];
                    changeID = j;
                }
            }
        }

        swap(num[p-1], num[changeID]);

        sort(num.begin()+p, num.end());



    }

    //////////////////////////////

        void nextPermutation3(vector<int>& nums) {
        int i = nums.size()-1;

        while(i>0 && nums[i]<nums[i-1]) --i;

        if(i==0)
            reverse(nums.begin(), nums.end());
        else{
            // nums[i] is to be replaced
            int j=nums.size()-1;
            while(nums[j]<=nums[i-1]) --j;

            // j  >  i
            swap(nums[j], nums[i-1]);

            reverse(nums.begin()+i, nums.end());  //  错了，不是reverse， 是sort！！！！！
        }
    }
    ////////// Leetcode passed   ////////////////////
    void nextPermutation(vector<int>& nums) {
        if(nums.size()<2) return;

        int j=nums.size()-2;

        while(j>=0 && nums[j]>=nums[j+1]) --j;  // 要注意等于号，有重复元素的时候

        if(j<0){
            sort(nums.begin(), nums.end());
            return;
        }

        int start=j+1, end=nums.size()-1;

        for(int i=end; i>=start; --i){
            if(nums[i]>nums[j]){
                swap(nums[i], nums[j]);
                break; //  break 别忘了。
            }
        }

        sort(nums.begin()+j+1, nums.end());
    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {5,0,7,4,5,6,8,5,4,1};

    a.nextPermutation3(d);

    for(auto i : d)
        cout<<i<<",";
    cout<<endl;

}
