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
    ////// leetcode passed  //////////////////////////
    vector<vector<int>> fourSum2(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        for(int i=0; i<nums.size(); ++i){
            for(int j=i+1; j<nums.size(); ++j){
                for(int k=j+1, l=nums.size()-1; k<l; ){
                    if(nums[i]+nums[j]+nums[k]+nums[l]>target)
                        --l;
                    else if(nums[i]+nums[j]+nums[k]+nums[l]<target)
                        ++k;
                    else if(find(result.begin(), result.end(), vector<int>({nums[i], nums[j],nums[k],nums[l]}))==result.end()){  /// need to verify duplicate
                        result.push_back(vector<int>({nums[i], nums[j],nums[k],nums[l]}));
                        ++k;--l;
                    }else{  /// in case that there are exact same results
                        ++k;--l;
                    }
                }
            }
        }
        //sort(result.begin(), result.end());
        //result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }

    ///////////////// leetcode passed  //////////
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        unordered_map<int, vector<pair<int, int>>> map;

        for(int i=0; i<nums.size(); ++i){
            for(int j=i+1; j<nums.size(); ++j){
                map[nums[i]+nums[j]].push_back(make_pair(i,j));
            }
        }

        for(int i=0; i<nums.size(); ++i){
            for(int j=i+1; j<nums.size(); ++j){
                if( map.find(target-nums[i]-nums[j])!=map.end()  ){
                    for(auto k : map[target-nums[i]-nums[j]]){
                        if(k.first > j){
                            vector<int> tmp({nums[i], nums[j], nums[k.first], nums[k.second]});
                            if(find(result.begin(), result.end(), tmp)==result.end())
                                result.push_back(tmp);
                        }
                    }
                }
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
    vector<int> d {1,2,3,4,5,6,7,8,5,5,5,9,10};

    auto f = a.fourSum2(d, 22);

    for(auto& i : f)
        {for(auto& j : i)
            cout<<j<<",";
         cout<<endl;
        }
}
