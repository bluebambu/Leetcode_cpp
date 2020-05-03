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
    //////////// passed //////////////
    bool isValid(string s) {
        if(s.empty()) return true;
        stack<int> st;

        for(int i=0; i<s.size(); ++i){
            if(s[i]=='(' || s[i]=='[' || s[i]=='{')
                st.push(i);
            else{
                switch(s[i]){
                    case ')' : if(!st.empty() && s[st.top()]=='(')
                                    st.pop();
                                else
                                    return false;
                                break;
                    case ']' : if(!st.empty() && s[st.top()]=='[')
                                    st.pop();
                                else
                                    return false;
                                break;
                    case '}' : if(!st.empty() && s[st.top()]=='{')
                                    st.pop();
                                else
                                    return false;
                                break;
                    default  :  return false;
                }
            }
        }

        return st.empty();
    }


    //////////////////////////////////
    bool validParenthesis(string str)
    {
        vector<char> parenStack;

        for(auto i : str)
        {
            switch(i)
            {
            case ')':
                if(parenStack.back()!='(')
                    return false;
                else
                    parenStack.pop_back();
                break;

            case ']':
                if(parenStack.back()!='[')
                    return false;
                else
                    parenStack.pop_back();
                break;

            case '}':
                if(parenStack.back()!='{')
                    return false;
                else
                    parenStack.pop_back();
                break;

            case '(':
            case '[':
            case '{':
                parenStack.push_back(i);
                break;
            }
        }

        if(parenStack.size()==0) // ∫‹÷ÿ“™£°£°
            return true;
        else
            return false;
    }
///////////////////////Leetcode answer ////////////////////////
    bool isValid(string s) {
        stack<char> paren;
        for (char& c : s) {
            switch (c) {
                case '(':
                case '{':
                case '[': paren.push(c); break;
                case ')': if (paren.empty() || paren.top()!='(')
                            return false;
                          else
                            paren.pop();
                          break;

                case '}': if (paren.empty() || paren.top()!='{')
                            return false;
                          else
                            paren.pop();
                          break;

                case ']': if (paren.empty() || paren.top()!='[')
                            return false;
                          else
                            paren.pop();
                          break;

                default: ; // pass
            }
        }
        return paren.empty() ;
    }
};

int main()
{
    Solution a;
    string b("([][][]{{{}}}");

    auto c=a.validParenthesis(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
