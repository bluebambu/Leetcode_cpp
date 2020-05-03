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
//////// leetcode passed ， 基于 交换， 貌似耗时会长一些  //////////////// best!
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path=nums;
        perm(path, result, 0);
        return result;
    }

    void perm(vector<int>& path, vector<vector<int>>& result, int idx){
        if(idx==path.size())
            result.push_back(path);

        for(int i=idx; i<path.size(); ++i){
            swap(path[idx], path[i]);
            perm(path, result, idx+1);
            swap(path[i], path[idx]);
        }
    }
///////////////// Leetcode passed, 基于 构建新的buff /////////////////////
    vector<vector<int>> permute2(vector<int>& num)
    {
        vector<vector<int>> result;
        vector<int> buff;

        permute2_main(num, buff, result);
        return result;
    }

    void permute2_main(vector<int>& num, vector<int>& buff, vector<vector<int>>& result)
    {
        if( buff.size()==num.size())
        {
            result.push_back(buff);
            return;
        }

        for(auto i : num)
        {
            if(find(buff.begin(), buff.end(), i)==buff.end())
            {
                buff.push_back(i);
                permute2_main(num, buff, result);
                buff.pop_back();
            }
        }
    }

    ////////////////Leetcode passed, iterative ///////////////////////////
    /**            [  1 , 2  ]
                     ^  ^  ^
    insert 3:        |  |  |    3 possibilities

    **/
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<vector<int>> buffer;
        result.push_back(vector<int>());

        for(int i=0; i<nums.size(); ++i){
            int vec_n = result.size();
            for(int j=0; j<vec_n; ++j){
                int vec_size = result[j].size();
                for(int k=0; k<=vec_size; ++k){
                    vector<int> tmp(result[j]);
                    tmp.insert(tmp.begin()+k, nums[i]);
                    buffer.push_back(tmp);
                }
            }
            result=buffer;
            buffer.clear();
        }

        return result;
    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.permute3(intset);

    for(auto i:b)
    {for(auto j: i)
            cout<<j<<" ";
     cout<<endl;
    }
}
