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
    int maxProfit( vector<int> &price )
    {
        if(price.size()<2) return 0;
        int profit = 0;
        int cur_min = price[0];

        for(int i=1; i<price.size(); i++)
        {
            profit = max(profit, price[i]-cur_min);
            cur_min=min(cur_min, price[i]);
        }
        return profit;
    }

    int maxProfit2( vector<int> &price ){
        if(price.size()<2) return 0;

        int lowest = 1<<31-1, // max int
            maxheigh=0;

        for(int &i : price){
            if(lowest>i) lowest=i;
            if(i-lowest>maxheigh) maxheigh=i-lowest;
        }

        return maxheigh;

    }



};


int main()
{
    Solution a;

    vector<int> intset {10,2,-1, 4,7,2,1,-9,-6,3};

    auto b = a.maxProfit(intset);

            cout<<b<<" ";
     cout<<endl;

}
