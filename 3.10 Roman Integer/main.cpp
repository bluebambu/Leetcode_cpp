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
    string intoRoman(int num)
    {
        const int radix[]     = {1000, 900, 500, 400, 100, 90,  50,  40,   10,  9,    5,   4,    1};
        const string symbol[] = {"M",  "CM","D", "CD", "C","XC","L", "XL", "X", "IX", "V", "IV", "I"};

        string Roman;

        for(size_t i=0; num>0 ; ++i)
        {
            int count = num / radix[i];
            num = num % radix[i];

            for(;count>0;--count) Roman+=symbol[i];
        }

        return Roman;
    }

    string intoRoman2(int num){
        vector<int> number = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> letter = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        string roman;

        for(int i=0; i<number.size(); ++i){
            int count = num/number[i];
            num %= number[i];

            for(;count>0;--count)
                roman += letter[i];
        }

        return roman;
    }


};

int main()
{
    Solution a;
    int b = 82;

    auto c=a.intoRoman2(b);
    for(auto i : c)
        cout<<i;

}
