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
    bool isMatch(const char *s, const char *p)
    {
        if(*p == '\0') return *s == '\0';

        if(*(p+1)!= '*')
        {
            if(*p == *s || (*p == "." && *s != '\0'))
                return isMatch(s+1, p+1);
            else
                return false;
        }

        else
        {
            while( *p == *s || (*p == '.' && *s!='\0'))
            {
                if(isMatch(s, p+2))
                    return true;
                s++;
            }

            return isMatch(s,p+2);
        }
    }

};

int main()
{
    Solution a;
    string b("");

    auto c=a.isPalindrome(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
