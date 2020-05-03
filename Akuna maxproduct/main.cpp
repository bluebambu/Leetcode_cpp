///  给一个integer数组，找两个数v1 v2使他们乘积最大，并满足a. v1在v2前面，b. v1比v2小
///  nlogn &  n  的解
///
///  @ luke， Xiang， xxxx
//
//
​
#include <iostream>
#include <vector>
#include <string>
#include <set>
​
​
using namespace std;
​
​
class Solution {
public:
    int maxproduct(vector<int> nums){
        if(nums.size()<2) return 0;
​
        set<int> treeset;
        int result=INT_MIN;
        treeset.insert(nums[0]); treeset.insert(nums[1]);
​
        for(int i=2; i<nums.size(); ++i){
            if(nums[i]>=0){ /// 正数找 floor
                auto lower = treeset.lower_bound(nums[i]);
                if(lower != treeset.begin())
                    result = max(result, nums[i]* (*(--lower)));
            }else{ /// 负数找min
                auto bottom = treeset.begin();
                if(*bottom < nums[i])
                    result = max(result, nums[i] * (*bottom));
            }
            treeset.insert(nums[i]);
        }
        return result==INT_MIN ? 0: result;
    }
​
    int maxproduct2(vector<int> nums){
        if(nums.size()<2) return 0;
​
        int neg_min=INT_MAX, neg_max=INT_MIN, pos_max=INT_MIN;
        int result=INT_MIN;
​
        for(int i=0; i<nums.size(); ++i){ /// 左向右， 专门负责 负负相乘 和 负正相乘
            if(nums[i]<0){
                if(neg_min!=INT_MAX && neg_max!=INT_MIN && nums[i]>neg_min){
                    result = max(result, neg_min * nums[i]);
                }
                neg_min = min(neg_min, nums[i]);
                neg_max = max(neg_max, nums[i]);
            }else{
                if(neg_min!=INT_MAX && neg_max!=INT_MIN){
                    result = max(result, neg_max * nums[i]);
                }
            }
        }
​
        for(int i=nums.size()-1; i>=0; --i){ /// 右向左， 专门负责 正正相乘
            if(nums[i]>0){
                if(pos_max!=INT_MIN && nums[i]<pos_max){
                    result = max(result, pos_max*nums[i]);
                }
                pos_max = max(pos_max, nums[i]);
            }
        }
        return result==INT_MIN ? 0: result ;
    }
​
};
​
​
int main()
{
    Solution a;
​
    cout<<a.maxproduct({1, 10, 2, 8, 4, 5})<<endl
        <<a.maxproduct({5, -2, 3, -3, 2})<<endl
        <<a.maxproduct({6,5,4,3,2,1})<<endl
        <<a.maxproduct({-5, -7, -12, 4,8,-11, 9,19})<<endl
        <<a.maxproduct({-2, 0, -5})<<endl;
​
    cout<<endl;
​
    cout<<a.maxproduct2({1, 10, 2, 8, 4, 5})<<endl
        <<a.maxproduct2({5, -2, 3, -3, 2})<<endl
        <<a.maxproduct2({6,5,4,3,2,1})<<endl
        <<a.maxproduct2({-5, -7, -12, 4,8,-11, 9,19})<<endl
        <<a.maxproduct2({-2, 0, -5})<<endl;
}
