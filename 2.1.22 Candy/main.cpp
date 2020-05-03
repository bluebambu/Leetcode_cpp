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
    int candy(vector<int> &ratings)
    {
        vector<int> candyNum(ratings.size(),1);

        for(int i=1; i<ratings.size();++i)
        {
            if(ratings[i]>ratings[i-1])
                candyNum[i]= candyNum[i-1]+1;
        }

        for(int j=ratings.size()-2;j>=0;--j)
        {
            if(ratings[j]>ratings[j+1])
                candyNum[j]= max(candyNum[j],candyNum[j+1]+1);
        }

        int result=0;

        for(auto i : candyNum)
            result+=i;

        return result;
    }

};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {2,3,4,4,4,3,2};

    auto len_final = a.candy(d);
    cout<<"result = "<<len_final<<endl;

    for(auto i : d)
        cout<<i<<",";
    cout<<endl;
}
