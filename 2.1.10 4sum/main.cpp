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
//һ������˼·1��
//
//��3Sum�Լ�2Sum�Ļ����ϣ������ܽ��KSum��ͨ���㷨���Ǿ��������а�����ѡ������Ϊtarget��o(n)�����������µ�����ʹ��(K-1)Sum�㷨������2Sum�ĸ��Ӷ���o(n)��
//
//
//
//�������4Sum�Ľ���˼·2��
//
//1��4Sum���Էֽ�Ϊ2Sum+2Sum����˽�ԭʼ�����У���������������ͣ���¼��hash����ôԭ����4Sum=target�����⣬��תΪ��hash�����ҵ�2��Itemʹ��Sum֮��Ϊtarget�����⣻����һ��ֵ��item�����ж�����ϴ��ڣ�����Ŀ�е�����item=0����ô��-1,1����-2,2����0,0����Ӧ�����ڴ�item�£������hash����Խ���ֵ��Ϊitemֵ������value��Ϊһ��list�����������������ϡ�
//
//2����β���hash��
//
//�������ǿ��Ե�����˼��������A+B+C+D=target��ABCD������ͬ������hash����������Ԫ������֮�͵Ľ������AB��AC��AD��BC��BD��CD���������ڱ��У��������Ѱ�Һ�Ϊtarget��item��ϵĻ���һ����AB+CD��AC+BD��AD+BC��BC+AD��BD+AC��CD+AB 6����������Ϊtarget���������Ƕ�ֻ��Ӧһ�ַ���ֵ��A��B��C��D����
//
//����Ϊ�˱������6���ظ����������һ��item�У���AC��BD������Ԫ�ص�����˳��Ҳ�ǰ��մ�С�����������У��������ֻ���AB+CD�����ɸѡ�����������item�ĺ͵���target��ͬʱҪ����item1�ĵڶ���ֵBҪС��item2�ĵ�һ��Ԫ��C����ô���Ե������¼�뷵�ض����У�������������Ҫ��
//
//3���������ϴ�ʩ�����ظ�֮�⣬������������д����ظ���Ԫ�أ����ҵ�һ�ֽ���hash��ʱ������ظ�Ԫ��ɸѡ�޳������Ҫע�ⲻҪ��ĳһֵ�������Σ�
//
//
//
//ʱ�临�Ӷȣ�
//
//��һ���ֽ���hash����Ҫn(n-1)/2������������ֵ��x����ÿ��ֵƽ����k����ϣ���ôx*k = n(n-1)/2��
//
//���Գ���ʱ�临�Ӷ�Ϊ o( n(n-1)/2 + x*k*k ) = o( n(n-1)/2 * (1+k) )����ʱ�临�Ӷ�ԼΪo(kn2) ��kȡֵ: 1~n(n-1)/2��
//
//��õ������������ֵû���ظ���x=n(n-1)/2��k=1����ô����ʱ�临�Ӷ�Ϊo(n2);
//
//������������������Ԫ�ض���ȣ���ôx=1��k=n(n-1)/2��ʱ�临�ӶȽӽ�o(n4)��

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
        // key �������ĺͣ�vector��value
        // value��һ��vector����Ϊ �����ж�����ֵĺ����

        for(int i=0;i<num.size();++i)
            for(int j=i+1;j<num.size();++j)
            {
                cache[num[i]+num[j]].push_back(pair<int, int>(i, j));

                // Ǳ����Ϣ�ǣ� i һ��С�� j
            }


        for(int a=0; a<num.size();++a)
            for(int b=a+1; b<num.size();++b)
            {
                // ͬ����aһ��С��b�� �����Ļ���ʵ���ú����������
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
