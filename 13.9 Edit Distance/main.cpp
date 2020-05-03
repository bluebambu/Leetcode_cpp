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
    //////// mkyforever ans  //////
     int minDistance(string word1, string word2)
     {
         int l1 = word1.size(), l2 = word2.size();

         if(l1 == 0 || l2 == 0)
             return max(l1, l2);

         vector<vector<int> > vvi(l1 + 1, vector<int>(l2 + 1, 0));

         for(int i = 0; i <= l1; ++ i)
             vvi[i][0] = i;
         for(int j = 0; j <= l2; ++ j)
             vvi[0][j] = j;

         for(int i = 1; i <= l1; ++ i)
             for(int j = 1; j <= l2; ++ j)
                 if(word1[i - 1] == word2[j - 1])
                     vvi[i][j] = vvi[i - 1][j - 1];
                 else
                     vvi[i][j] = min(min(vvi[i - 1][j], vvi[i][j - 1]), vvi[i - 1][j - 1]) + 1;

         return vvi[l1][l2];
     }
};


int main()
{
	Solution a;


}
