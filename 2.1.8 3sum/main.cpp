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
    vector<vector<int>> threeSum(vector<int>& num, int target)
    // ������һ��sort֮��*i, *j, *k ��Ȼ�������� *i Ҳһֱ�����ӣ�
    //�������Ľ��һ����������û���ظ��ġ�

    {
        vector<vector<int>> result;
        if(!num.size()) return result;
        sort(num.begin(),num.end());


        auto i=num.begin();
        vector<int> temp;

        for(;i<num.end();++i)
        {
            auto j=i+1;
            auto k=num.end()-1;

            while(j<k)
            {
                if(*i+*j+*k<target)
                    ++j;
                else if(*i+*j+*k>target)
                    --k;
                else
                    {
                        result.push_back({*i, *j, *k}); // ������ס����
                        ++j;
                        --k;
                    }
            }


        }
        sort(result.begin(), result.end());
//        result.erase(unique(result.begin(), result.end()), result.end());


        return result;
    }



    vector<vector<int>> threeSum2(vector<int>& num, int target)
    // leetcode �Ĵ𰸡����������ҷ��֣�����Ҫ sort �� erase ������.....
    // �Һ������֣�erase ��Ϊ�˷�ֹ array�������ظ���Ԫ��
    {
        vector<vector<int>> result;
        if (num.size() < 3) return result;
        sort(num.begin(), num.end());

        auto last = num.end();
        for (auto a = num.begin(); a < prev(last, 2); ++a) {
        auto b = next(a);
        auto c = prev(last);
        while (b < c) {
        if (*a + *b + *c < target) {
        ++b;
        } else if (*a + *b + *c > target) {
        --c;
        } else {
        result.push_back({ *a, *b, *c });
        ++b;
        --c;
        }
        }
        }
//        sort(result.begin(), result.end());
//        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
}


    vector<vector<int>> threeSum3(vector<int>& num, int target)
    {
        unordered_map<int, vector<pair<int, int>>> aux;

        vector<vector<int>> result;

        for(int i=0; i<num.size();++i)
            for(int j=i+1;j<num.size();++j )
            {
                aux[num[i]+num[j]].push_back(pair<int, int>(i,j));
            }

//        for ( auto it = aux.begin(); it != aux.end(); ++it )
//            {
//                std::cout << " " << it->first << ":  " ;
//                for(auto i : it->second)
//                    cout<<i.first<<"  "<<i.second<<"  ";
//                cout<<endl;
//            }

        for(int i : num)
        {
            int gap = target - i;

            if(aux.find(gap) != aux.end())
            {
                for(auto j : aux[gap])
                {
                    result.push_back(vector<int>({target, i, num[j.first], num[j.second]}));
                }

            }
        }



        return result;
    }


    vector<vector<int>> threeSum4(vector<int>& num, int target)
    {
        sort(num.begin(), num.end());

        vector<vector<int>> result;


        for(int i=0; i<num.size();++i)
        {
            for(int j=i+1, k=num.size()-1; j<k && j<num.size(); )
            {
                int total = num[i]+num[j]+num[k];

                if(total == target) result.push_back({num[i], num[j++], num[k--]});

                else if(total > target) {--k; continue;}

                else {++j; continue;}
            }
        }

        return result;
    }


    vector<vector<int>> threeSumClosest1(vector<int>& num, int target)
    {
        sort(num.begin(), num.end());

        vector<vector<int>> result={{0}};
        int gap =9999;


        for(int i=0 ; i<num.size() ; ++i    )
        {
            for(int j=i+1, k=num.size()-1 ; j<k ; )
            {
                int total = num[i]+num[j++]+num[k--];

                if(abs(total - target) < gap) {gap = abs(total - target) ; result[0][0]=total;}


            }
        }

        return result;

    }

    vector<vector<int>> threeSum5(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        for(int i=0; i<nums.size(); ++i){
            int begin = i+1,
                end = nums.size()-1,
                target = 0-nums[i];

            for(int j=begin, k=end; j<k; ){
                if(nums[j]+nums[k]==target){
                    result.push_back(vector<int>({nums[i], nums[j], nums[k]}));
                    ++j;
                    --k;
                }
                else if(nums[j]+nums[k]>target)
                    --k;
                else if(nums[j]+nums[k]<target)
                    ++j;
            }
        }

        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }

    vector<vector<int>> threeSum6(vector<int>& nums) {
        vector<vector<int>> result;
        unordered_map<int, vector<pair<int,int>>> buff;

        for(int i=0; i<nums.size(); ++i)
            for(int j=i+1; j<nums.size(); ++j)
                buff[nums[i]+nums[j]].push_back(pair<int, int>(i, j));

        for(int i=0; i<nums.size(); ++i){
            int target = 0-nums[i];

            if(buff.find(target)!=buff.end()){
                for(auto j : buff[target]){
                    if(j.first > i){
                        result.push_back(vector<int>({nums[i], nums[j.first], nums[j.second]}));
                    }
                }
            }
        }
        result.erase(unique(result.begin(), result.end()), result.end());

        return result;
    }

    vector<vector<int>> threeSum7(vector<int>& nums) {
        // leetcode ����ͨ���˵Ĵ𰸣�
        vector< vector<int> > result;
        int n = nums.size();
        if(n<3)
            return result;

        // sort the vector and then use two pointers and scan numbers
        sort(nums.begin(), nums.end());
        int i;
        vector<int> triplet;
        triplet.resize(3);
        int left, right;
        for(i=0; i<n-2; i++)
        {
            if(i > 0 && nums[i] == nums[i-1])
            // avoid duplicated triplets. ���ﲻ���� nums[i]==nums[i+1]
            // ��Ϊ����бƵķ�Χ�� i ���ұߣ�Ϊ�˱�֤�����ӹ� target = 3�� nums[i]
            // �������Ҫ���ظ���������ߵ�Ԫ�أ����������ұߵ�
                continue;
            left = i+1;
            right = n-1;
            // no-descending order
            while(left<right)
            {
                if(nums[left] + nums[right] == 0 - nums[i])
                    // ���������ĺ͵��ж����֮�����Թ��ظ�������
                {
                    while(left+1 < n && nums[left] == nums[left+1])
                    {
                        left = left + 1;
                    }
                    while(right-1 > 0 && nums[right] == nums[right-1])
                    {
                        right = right - 1;
                    }
                    // do duplicated triplets

                    triplet[0] = nums[i];
                    triplet[1] = nums[left];
                    triplet[2] = nums[right];
                    result.push_back(triplet);
                    left = left + 1;
                    right = right - 1;

                }

                else if(nums[left] + nums[right] < -nums[i])
                    left = left + 1;
                else
                    right = right - 1;
            }
        }
        return result;
    }

///////////////////// pass leetcode!!! ///////////////////////////////////////
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        if(nums.size()<3) return result;

        sort(nums.begin(), nums.end());

        for(int i=0; i<nums.size(); ++i){
            int j=i+1, k=nums.size()-1;
            while(j<k){
                int gap = 0-nums[i];
                if(nums[j]+nums[k]>gap)
                    --k;
                else if(nums[j]+nums[k]<gap)
                    ++j;
                else{
                    result.push_back(vector<int>({nums[i], nums[j], nums[k]}));

                    while(j<k && nums[j]==nums[j+1]) ++j; //  Ҫ����Ԫ���ظ���������Ż�����Ȼ�޷��������ݼ��ϣ�������
                    while(j<k && nums[k]==nums[k-1]) --k;

                    ++j;
                    --k;
                }
            }

        while(i<j && nums[i]==nums[i+1]) ++i;
        }

        return result;
    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {0,0,0};
                // 0,1,2,3,4, 5, 6, 7,  8,  9,10, 11,12

    auto i = a.threeSum10(d);

    for(auto& j : i)
    {
        for(auto& k : j)
            cout<<k<<",";
        cout<<endl;
    }
}
