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

/// java solution

public int maxDiffSubArrays(ArrayList<Integer> nums) {
        // write your code
        if (nums==null || nums.size()==0) return 0;
        int len = nums.size();
        int[] lGlobalMax = new int[len];
        int[] lGlobalMin = new int[len];
        int lLocalMax = nums.get(0);
        int lLocalMin = nums.get(0);
        lGlobalMax[0] = lLocalMax;
        lGlobalMin[0] = lLocalMin;
        for (int i=1; i<len; i++) {
            lLocalMax = Math.max(lLocalMax+nums.get(i), nums.get(i));
            lGlobalMax[i] = Math.max(lLocalMax, lGlobalMax[i-1]);

            lLocalMin = Math.min(lLocalMin+nums.get(i), nums.get(i));
            lGlobalMin[i] = Math.min(lLocalMin, lGlobalMin[i-1]);
        }

        int[] rGlobalMax = new int[len];
        int[] rGlobalMin = new int[len];
        int rLocalMax = nums.get(len-1);
        int rLocalMin = nums.get(len-1);
        rGlobalMax[len-1] = rLocalMax;
        rGlobalMin[len-1] = rLocalMin;
        for (int i=len-2; i>=0; i--) {
            rLocalMax = Math.max(rLocalMax+nums.get(i), nums.get(i));
            rGlobalMax[i] = Math.max(rLocalMax, rGlobalMax[i+1]);

            rLocalMin = Math.min(rLocalMin+nums.get(i), nums.get(i));
            rGlobalMin[i] = Math.min(rLocalMin, rGlobalMin[i+1]);
        }

        int maxDiff = Integer.MIN_VALUE;
        for (int i=0; i<len-1; i++) {
            if (maxDiff < Math.abs(lGlobalMax[i]-rGlobalMin[i+1]))
                maxDiff = Math.abs(lGlobalMax[i]-rGlobalMin[i+1]);


            if (maxDiff < Math.abs(lGlobalMin[i]-rGlobalMax[i+1]))
                maxDiff = Math.abs(lGlobalMin[i]-rGlobalMax[i+1]);
        }
        return maxDiff;
    }


int main()
{
	Solution a;


}
