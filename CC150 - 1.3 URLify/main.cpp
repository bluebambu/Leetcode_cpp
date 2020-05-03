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
    string URLify(string s){
        string result;

        /// get rid of heading and trailing spaces
        int strBegin = s.find_first_not_of(' ');
        int strEnd = s.find_last_not_of(' ');

        s=s.substr(strBegin, strEnd - strBegin +1);

        for(int i=0; i<s.size(); ++i){
            if(s[i]!=' ')
                result.push_back(s[i]);
            else
                result+="%20";
        }

        return result;
    }

};

int main()
{
    Solution a;

    cout<<a.URLify("Mr John Smith ");

}
