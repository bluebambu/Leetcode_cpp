#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    //////// TLE ///////////////
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        int result=0;

        for(int i=0; i<heights.size(); ++i){
            int left=i, right=i;
            while(left >=0 && heights[left] >= heights[i]) --left;
            while(right <heights.size() && heights[right] >= heights[i]) ++right;

            result = max(result, heights[i]*(right-left-1));
        }

        return result;
    }



    ////////////////Leetcode passed, stack ///////////////////////////
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        heights.push_back(0);

        stack<int> st;

        int result=0;
        for(int i=0; i<heights.size(); ++i){
            if(st.empty() || heights[i]> heights[st.top()])
                st.push(i);
            else{
                while(!st.empty() && heights[i] < heights[st.top()]){
                    int cur_top = st.top();
                    st.pop();
                    int left = st.empty() ? -1 : st.top();
                    result = max(result, (i - left -1)*heights[cur_top]);  /// (i- left -1) 要仔细体会； st.empty() 的情况要考虑
                }
                st.push(i);
            }
        }
        return result;
    }


};



int main()
{
    Solution a;
    vector<int> b({2,1,5,6,2,3});

    auto c=a.LargestRectang3(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
