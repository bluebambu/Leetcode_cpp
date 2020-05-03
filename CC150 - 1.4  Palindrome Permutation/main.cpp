#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <bitset>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    /// it is similar to the problem: single number. odd number of 1 number in even numbers of other numbers.
    /// wrong, because here you don't know how many unique chars are in the string.
    /// but in the SingleNumber problem, you do know that!!
    bool PerlindromPerm(string s){
        int bits=0;

        for(int i=0; i<s.size(); ++i){
            int ch = s[i]-'a';

            if(bits & (1<<ch) )
                bits &= ~(1<<ch);  /// !!! turn bit 1 off.
            else
                bits |= 1<<ch;
        }

        return ((bits-1) & bits) == 0 || bits==0;
    }
};

///

int main()
{
    Solution a;

    cout<<a.PerlindromPerm("abac");
}
