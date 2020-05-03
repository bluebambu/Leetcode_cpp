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


class Solution {
public:
    ////// passed //
    int myAtoi(string str) {
        int sign = 1, base = 0, i = 0;
        while (str[i] == ' ') { i++; }
        if (str[i] == '-' || str[i] == '+') {
            sign = 1 - 2 * (str[i++] == '-');
        }
        while (str[i] >= '0' && str[i] <= '9') {
            if (base >  INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > INT_MAX%10)) {
                 return sign==1 ? INT_MAX :INT_MIN;
            }
            base  = 10 * base + (str[i++] - '0');
        }
        return base * sign;
    }
};

int main()
{
    Solution a;
    string b("");

    auto c=a.myAtoi(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
