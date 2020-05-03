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
//
//一、解题思路1：
//
//在3Sum以及2Sum的基础上，可以总结出KSum的通用算法，那就是数组中按序挑选数字作为target（o(n)），对于余下的序列使用(K-1)Sum算法，其中2Sum的复杂度是o(n)；
//
//
//
//二、针对4Sum的解题思路2：
//
//1、4Sum可以分解为2Sum+2Sum；因此将原始数组中，所有数字两两求和，记录在hash表；那么原来的4Sum=target的问题，就转为从hash表中找到2个Item使其Sum之和为target的问题；满足一个值的item可能有多种组合存在（如题目中的例子item=0，那么（-1,1）（-2,2）（0,0）都应保存在此item下），因此hash表可以将键值作为item值，而将value设为一个list，保存所有满足的组合。
//
//2、如何操作hash表：
//
//　　我们可以倒过来思考，假设A+B+C+D=target，ABCD各不相同；由于hash表保存了所有元素两两之和的结果，即AB、AC、AD、BC、BD、CD都单独存在表中，如果仅仅寻找和为target的item组合的话，一共有AB+CD、AC+BD、AD+BC、BC+AD、BD+AC、CD+AB 6种情况满足和为target，但是他们都只对应一种返回值（A、B、C、D）；
//
//　　为了避免出现6次重复结果，由于一个item中（例AC、BD）两个元素的排列顺序也是按照从小到大有序排列，因此我们只针对AB+CD的情况筛选。即如果两个item的和等与target，同时要满足item1的第二个值B要小于item2的第一个元素C，那么可以当做结果录入返回队列中，否则当做不符合要求。
//
//3、除了以上措施避免重复之外，由于数组队列中存在重复的元素，并且第一轮建立hash表时不会对重复元素筛选剔除。因此要注意不要将某一值计算两次；
//
//
//
//时间复杂度：
//
//第一部分建立hash表需要n(n-1)/2，假设两两和值有x个，每个值平均有k种组合，那么x*k = n(n-1)/2；
//
//所以程序时间复杂度为 o( n(n-1)/2 + x*k*k ) = o( n(n-1)/2 * (1+k) )，即时间复杂度约为o(kn2) ，k取值: 1~n(n-1)/2；
//
//最好的情况是两两和值没有重复，x=n(n-1)/2，k=1；那么程序时间复杂度为o(n2);
//
//最坏的情况是数组中所有元素都相等，那么x=1，k=n(n-1)/2，时间复杂度接近o(n4)；

class Solution
{
public:
////////////////////Leetcode passed///////////////
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        if(nums.size()<4) return result;
        sort(nums.begin(), nums.end()); /// it's necessary to sort at first, otherwise [4,0,0,4] will cause duplicate problems

        unordered_map<int, list<pair<int, int>>> h;

        for(int i=0; i<nums.size(); ++i){
            for(int j=i+1; j<nums.size(); ++j){
                h[nums[i]+nums[j]].push_back(make_pair(i, j));
            }
        }

        for(auto iter=h.begin(); iter!=h.end(); ++iter){
            int remain = target - iter->first;
            if(h.find(remain)!=h.end()){
                auto& cur_l = iter->second;
                auto& remain_l = h[remain];

                for(auto t1=cur_l.begin(); t1!=cur_l.end(); t1++){
                    for(auto t2=remain_l.begin(); t2!=remain_l.end(); ++t2){
                        if(t1->second < t2->first){
                            result.push_back({nums[t1->first], nums[t1->second], nums[t2->first], nums[t2->second]});
                        }
                    }
                }
            }
        }
        sort(result.begin(), result.end());  /// sort and erase duplicate are also necessary!!
        result.erase(unique(result.begin(), result.end()), result.end());

        return result;
    }
    /// Due to , when *iter and h[remian] are matching each other's elements, it is O(k^2) complexity, so total complexity is still O(n3), not O(n2)!!!
    /// So this method is worse than the  left-right squeeze approach.

    ///////////////// Leetcode passed /////////////////////


    vector<vector<int>> fourSum(vector<int> &num, int target)
    {
        vector<vector<int>> result;
        if(!num.size()) return result;

        sort(num.begin(), num.end());

        unordered_map<int, vector<pair<int, int>>> cache;
        // key 是两数的和，vector是value
        // value是一个vector，因为 可能有多对数字的和相等

        for(int i=0;i<num.size();++i)
            for(int j=i+1;j<num.size();++j)
            {
                cache[num[i]+num[j]].push_back(pair<int, int>(i, j));

                // 潜在信息是， i 一定小于 j
            }


        for(int a=0; a<num.size();++a)
            for(int b=a+1; b<num.size();++b)
            {
                // 同样，a一定小于b。 这样的话其实不用后面的排序了
                int key = target - num[a]-num[b];
                if(cache.find(key)!= cache.end())
                {
                    auto vec = cache[key];

                    for(auto& i:cache[key])
                    {
                        if(i.first>num[b])
                        {
                            result.push_back({num[a], num[b],i.first, i.second });

                        }

                    }
                }
            }
            // sort(result.begin(), result.end());
            return result;
    }


};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {1,2,3,4,5,6,7,8,9,10};

    auto f = a.fourSum(d, 22);

    for(auto& i : f)
        {for(auto& j : i)
            cout<<j<<",";
         cout<<endl;
        }
}
