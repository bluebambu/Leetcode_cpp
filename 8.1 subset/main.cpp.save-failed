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
    /// bits operation
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for(int i=0; i<(1<<nums.size()); ++i){
            vector<int> tmp;

            for(int j=0; j<nums.size(); ++j){
                if(i>>j & 1)
                    tmp.push_back(nums[j]);
            }
            result.push_back(tmp);
        }
        return result;
    }

    /// lc passed, iterative
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result(1, vector<int>());

        for(int i=0; i<nums.size(); ++i){
            int curNum = nums[i], cur_size = result.size();
            auto tmp = result;
            result.insert(result.end(), tmp.begin(), tmp.end());
            /// 不能直接 double size， 需要辅助的tmp的帮助
            /// 见 http://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector

            for(int j=cur_size; j<result.size(); ++j){
                result[j].push_back(curNum);
            }
        }
        return result;
    }

    ////////////// 模板答案 //////////////////////////
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        sub(nums, vector<int>(), 0, nums.size()-1, result);
        return result;
    }

    void sub(vector<int>& nums, vector<int> temp, int start, int end, vector<vector<int>>& result){
        result.push_back(temp);

        for(int i=start; i<=end; ++i){
            temp.push_back(nums[i]);
            sub(nums, temp, i+1, end, result);
            temp.pop_back();
        }
    }

    ////////////// 模板答案 2 //////////////////////////
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> path;
        sub(nums, path, result);
        return result;
    }

    void sub(vector<int>& nums, vector<int>& path, vector<vector<int>>& result){
        if(path.size()<=nums.size())
            result.push_back(path);

        for(int i : nums){
            if(path.empty() || i>path.back()){
                path.push_back(i);
                sub(nums, path, result);
                path.pop_back();
            }
        }
    }

////////////////////////    二进制法   //////////////////////////
    vector<vector<int> > subsetsBinary(vector<int> &S) {
        sort(S.begin(), S.end()); // 输出要求有序
        vector<vector<int> > result;
        const size_t n = S.size();
        vector<int> v;
        for (size_t i = 0; i < 1 << n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (i & 1 << (n-1-j)) v.push_back(S[j]);
            }
            result.push_back(v);
            v.clear();
        }
        return result;
    }



    //////////////////// Leetcode 答案 ////////////////
    vector<vector<int>> subsets5(vector<int> &S) {
        sort(S.begin(), S.end()); // 输出要求有序
        vector<vector<int> > result;
        vector<int> path;
        subsets(S, path, 0, result);
        return result;
    }

    void subsets(const vector<int> &S, vector<int> &path, int step, vector<vector<int> > &result){
        if (step == S.size()){
            result.push_back(path);
            return;
        }

        // 不选 S[step]
        subsets(S, path, step + 1, result);
        // 选 S[step]
        path.push_back(S[step]);
        subsets(S, path, step + 1, result);
        path.pop_back();
    }

    ///////////////////////////////
    vector<vector<int>> subsets2(vector<int> &s){
        sort(s.begin(), s.end());

        vector<vector<int>> result;
        vector<bool> selected(s.size(), false);
        subsets2_main(s, selected, 0, result);
        return result;
    }

    void subsets2_main(vector<int>& s, vector<bool> &selected, int step, vector<vector<int>> &result){
        if(step == s.size()){
            vector<int> subset;
            for(int i=0; i<s.size();++i){
                if(selected[i])
                    subset.push_back(s[i]);
            }
            result.push_back(subset);
            return;
        }

        selected[step] = false;
        subsets2_main(s, selected, step+1, result);

        selected[step] = true;
        subsets2_main(s, selected, step+1, result);
    }

    void subsets3(vector<int>& s, int i, int j, int k, vector<vector<int>>& result){
    // 05-01-2016 现在这个算法成功了， 在加了 pop_back()  之后。
        if(i==0 && j==0 && k==0){
            result.push_back(s);
            return;
        }

        if(i!=0)
            {s.push_back(1);
            subsets3(s, i-1, j, k, result);s.pop_back();}
        if(j!=0)
            {s.push_back(2);
            subsets3(s, i, j-1, k, result);s.pop_back();}
        if(k!=0)
            {s.push_back(3);
            subsets3(s, i, j, k-1, result);s.pop_back();}
    }




};

int main()
{
    Solution a;

    vector<int> intset({});

    vector<vector<int>> result;

    a.subsets3(intset, 1, 1, 1, result);

    for(auto i:result)
        {
            for(auto j:i)
                cout<<j<<" ";
            cout<<endl;
        }
}
