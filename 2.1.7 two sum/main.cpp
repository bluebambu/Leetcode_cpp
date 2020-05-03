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
    vector<int> twoSum(vector<int> &num, int target)
    {
        unordered_map<int, int> temp;

        for(int i=0; i<num.size();i++)
            temp[num[i]]=i;

        for(auto i:num)
        {
            if(temp.find(target -i)!=temp.end())
            {
                int a = temp[i];
                int b = temp[target - i];
                vector<int> result;
                result.push_back(a<b?a:b);
                result.push_back(a>b?a:b);
                return result;

            }
        }
    }


    vector<int> twoSum2(vector<int> &num, int target)
    {
        unordered_map<int, int> label;

        vector<int> result;
        int j=0;

        for(int i : num) label[i]=j++;

        for(int i : num)
        {
            int dif = target - i;

            if(label.find(dif)!= label.end())
            {
                result.push_back(label[i]+1);
                result.push_back(label[dif]+1);
                break;

            }
        }

        return result;
    }


    vector<int> twoSum3(vector<int> &num, int target)
    {
        sort(num.begin(), num.end());
        // 夹逼法，元素的下标已经被改变了，无法追踪，因此不能用在此处。

        vector<int> result;

        int n = num.size();

        for(int i=0, j=n-1 ; i<=j ;)
        {
            int total = num[i] + num[j];

            if(total > target) {--j;continue;}

            else if(total < target) {++i; continue;}

            else
            {
                result.push_back(i+1);
                result.push_back(j+1);
                break;
            }
        }

        return result;
    }


    vector<int> twoSum4(vector<int>& nums, int target)
    // 考虑array 中间有重复元素的情况
    // 考虑 target = nums[i] * 2 的情况
    {
        vector<int> result;
        unordered_map<int, vector<int>>  buff;

        for(int i=0; i<nums.size(); ++i)
            buff[nums[i]].push_back(i);

        for(int i: nums){
            int j = target -i;

            if(j!=i && buff.find(j)!=buff.end()){
                result.push_back(buff[i][0]+1);
                result.push_back(buff[j][0]+1);
                return result;
            }
            else if(j==i && buff[i].size()>1){
                result.push_back(buff[i][0]+1);
                result.push_back(buff[i][1]+1);
                return result;
            }
        }

        return result;
    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};

    vector<int> d {1,299,54,2,645,5,6,3};

    vector<int> len_final = a.twoSum2(d,10);

    for(float i : len_final)
        cout<<i<<",";
    cout<<endl;
}
