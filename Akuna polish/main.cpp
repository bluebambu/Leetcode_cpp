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
    int priority(char op){
        switch(op){
            case '+': return 0;
            case '-': return 0;
            case '*': return 1;
            case '/': return 1;
            case '@': return 2;
        }
    }

    void paren(string& n){
        n.insert(n.begin(), '(');
        n.push_back(')');
    }
//////////////////////// leetcode passed
    string evalRPN(vector<string> tokens) {
        if(tokens.empty()) return 0;

        vector<string> stack;
        vector<char> opstack;

        for(int i=0; i<tokens.size(); ++i){
            if(tokens[i].size()==1 && tokens[i][0]<'0'){
                string s1 = stack.back();
                stack.pop_back();
                char op1 = opstack.back();
                opstack.pop_back();

                string s2 = stack.back();
                stack.pop_back();
                char op2 = opstack.back();
                opstack.pop_back();

                if(priority(op1) < priority(tokens[i][0]))
                    paren(s1);
                if(priority(op2) < priority(tokens[i][0]))
                    paren(s2);

                stack.push_back(s2 + tokens[i][0] + s1);
                opstack.push_back(tokens[i][0]);
            }else{
                stack.push_back(tokens[i]);
                opstack.push_back('@');
            }
        }

        return stack.back();
    }

};


int main()
{
	Solution a;

    cout<<a.evalRPN( { "5", "2", "+", "3", "7", "6","/", "-", "*" });

}
