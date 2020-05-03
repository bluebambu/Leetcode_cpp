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


class Solution {
public:
    int lengthOfLastWord(string s) {
        if(s.empty()) return 0;

        int i = s.size()-1;
        int count=0;

        for(;i>=0; --i){
            if(s[i]!=' '){
                break;
            }
        }


        for(;i>=0; --i){
            if(s[i]!=' '){
                count++;
            }else
                break;
        }

        return count;
    }


    int lengthOfLastWord2(string s) {
        int s_len = s.length();
        while(s_len>0 && s[s_len-1]==' ') {s_len--;}
        int len = 0;
        while(s_len>len && s[s_len-len-1]!=' ') {len++;}
        return len;
    }

};


int main()
{
    Solution a;

    string intset ("akfj saldjfl alskjdflkj asdlfjla  ");

    auto b = a.lengthOfLastWord2(intset);


            cout<<b<<" ";

}
