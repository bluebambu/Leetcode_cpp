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
    /////////Leetcode passsed, best answer, O(n), space O(1) ///////////
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        int max=0;
        int peak=height[0];
        int result=0;

        for(int i=1; i<height.size(); ++i){
            if(height[i]>height[max])
                max=i;
        }

        for(int i=0; i<max; ++i){
            if(height[i]>peak) peak=height[i];
            else result+=peak-height[i];
        }

        peak=height[height.size()-1];

        for(int i=height.size()-1; i>max; --i){
            if(height[i]>peak) peak=height[i];
            else result+=peak-height[i];
        }

        return result;
    }

/////////////////////////////////////////////////////////////
    int TrappingWater(vector<int> d)
    {
        int result=0;

        for(int i=0; i<d.size(); ++i)
        {
            int lmax=-999, rmax=-999,
                lmaxid=-1, rmaxid=-1;

            for(int j=i-1; j>=0 ; --j)
            {
                if(d[j]>lmax)
                {
                    lmax=d[j];
                    lmaxid=j;
                }
            }

            for(int k=i+1; k<d.size() ; ++k)
            {
                if(d[k]>rmax)
                {
                    rmax=d[k];
                    rmaxid=k;
                }
            }

            if(lmaxid!=-1 && rmaxid!=-1 && lmax>d[i] && rmax>d[i])
                result+=((lmax<rmax ? lmax : rmax)-d[i]);

        }

        return result;


    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {1,1,1,1,1,1,1,3,1,1,1,1};

    auto len_final=a.TrappingWater(d);


        cout<<len_final;

//
//    }
}
