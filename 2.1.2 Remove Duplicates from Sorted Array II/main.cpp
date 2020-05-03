#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}

class Solution
{
public:
    int removeDuplicates5(int a[], int n)
    {
        if(n==0) return 0;

        int new_idx=0;
        int iter = 2;

        for(;iter<n;++iter)
        {
            if(a[iter]!=a[iter-2]) // 这个地方是错的！！！！
            {
                a[++new_idx]=a[iter];
            }
        }

        return new_idx+1;
    }

///////////////////////////// 正确答案  general 情况！！ ///////////////////////////
    int removeDuplicates(vector<int>& nums) {
        int times=2;

        if(nums.size()<times+1) return nums.size();

        int idx=times;

        for(int i=times; i<nums.size(); ++i){
            if(nums[i]!=nums[idx-times])
                nums[idx++]=nums[i];
        }
        return idx;
    }

};

int main()
{
    Solution a;
    int b[] = {1,1,1,1,3,3,4,5,6,6,6,6,7,7,8,9,11,14,14};
    int len_final = a.removeDuplicates5(b, sizeof(b)/sizeof(int));
    cout<<"size = "<<len_final<<endl;

    for(int i=0;i<len_final;++i)
        cout<<b[i]<<",";
}
