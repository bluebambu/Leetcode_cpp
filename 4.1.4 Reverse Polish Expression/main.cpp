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
//////////////////////// leetcode passed
    int evalRPN(vector<string>& tokens) {
        if(tokens.empty()) return 0;

        vector<int> stack;
        for(int i=0; i<tokens.size(); ++i){
            if(tokens[i].size()==1 && tokens[i][0] < '0'){
                int n1 = stack.back(); stack.pop_back();
                int n2 = stack.back(); stack.pop_back();
                switch(tokens[i][0]){
                    case '+' : stack.push_back(n1 + n2); break;
                    case '-' : stack.push_back(n2 - n1); break; /// caution: order of n1 & n2
                    case '*' : stack.push_back(n1 * n2); break;
                    case '/' : stack.push_back(n2 / n1); break; /// caution: order of n1 & n2
                }
            }else
                stack.push_back(atoi(tokens[i].c_str()));
        }
        return stack.back();
    }

};


int main()
{
	Solution a;


}
