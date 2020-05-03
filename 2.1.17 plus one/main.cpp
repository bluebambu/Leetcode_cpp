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
    vector<int> plusOne(vector<int> &digits)
    {
        *(digits.end()-1)+=1;

        for(auto i=digits.end()-1;i>digits.begin();--i)
        {
            if(*i==10)
            {
                *i = 0;
                *(i-1)+=1;
            }
        }

        if(*digits.begin()==10)
        {
            *digits.begin()=0;
            digits.insert(digits.begin(),1);
        }
    }

    vector<int> plusOne2(vector<int> &digits)
    {
        *(digits.end()-1)+=1;

        for(int n=digits.size()-1; n>0; --n)
        {
            if(digits[n]==10)
            {
                digits[n]=0;
                digits[n-1]+=1;
            }
        }

        if(digits[0]==10)
        {
            digits[0]=0;
            digits.insert(digits.begin(), 1);
        }

        return digits;
    }

    //////////////// leetcode passed /////////////////
    vector<int> plusOne(vector<int>& digits) {
        int carry=0;
        digits[digits.size()-1]+=1;

        for(int i=digits.size()-1; i>=0; --i){
            digits[i]+=carry;
            carry=digits[i]/10;
            digits[i] %=10;
        }

        if(carry==1){
            digits.insert(digits.begin(),1);
        }
        return digits;
    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {9,9,9,9};

    a.plusOne2(d);

    for(auto i : d)
        cout<<i<<",";
    cout<<endl;
}
