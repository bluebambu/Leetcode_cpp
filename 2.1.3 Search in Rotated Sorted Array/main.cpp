#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}

// left -> right, ascending order
class Solution
{
public:
    int SearchRotatedArray(int a[], int n, int target)
    {
        int first = 0, last = n-1;
        int mid;

        while(first<=last)
        // �Ⱥ� ����ȱ�٣� ��Ϊ��target �� a[last] ��ʱ��
        //���ܻ���� a[first] = a[mid] ������� ���û�еȺţ�
        //���һ�� first == last ������޷����㣬�ᵼ�����һ��Ԫ����������
        {

            mid=(first+last)/2;

            if(a[mid]==target) return 1;
            // rotate to left direction
            else if ( a[first] <= a[mid])
            {
                if(a[first]<=target && target < a[mid])
                    // �Ⱥ� ����ȱ�٣��������ҵ���һ��Ԫ��
                    {
                        last = mid-1;
                        continue;
                    }
                else
                    {
                        first = mid+1;
                        continue;
                    }
            }
            else
            {
                if(a[mid]<target && target<=a[last])
                {
                    first = mid+1;
                    continue;
                }
                else
                {
                    last = mid-1;
                    continue;
                }
            }
        }
        return -1;
    }

    int SearchRotatedArray2(int a[], int n, int target){
        int first=0, last=n-1, mid;
        while(first<=last){
            mid=(first+last)/2;
            if(a[mid]==target) return mid+1;

            if(a[first]<=a[mid])
            {
                if(a[first]<=target && target <=a[mid])
                {
                    last=mid;
                    continue;
                }
                else
                {
                    first=mid+1;
                    continue;
                }
            }
            else
            {
                if(a[mid]<=target && target <= a[last])
                {
                    first=mid;
                    continue;
                }
                else{
                    last=mid-1;
                    continue;
                }
            }

        }
        return -1;
    }
///////////////////////////////////////////////////////
    int search(vector<int>& nums, int target) {
        int start=0, end=nums.size()-1;

        while(start<=end){
            int mid = start+(end-start)/2;

            if(nums[mid]==target) return mid;

            if(nums[end]>nums[mid]){
                if(target>nums[mid] && target <= nums[end]){
                    start=mid+1;
                }else{
                    end=mid-1;
                }
            }else{
                if(nums[start]<=target && target<nums[mid]){
                    end=mid-1;
                }else{
                    start=mid+1;
                }
            }
        }

        return -1;
    }
};




int main()
{
    Solution a;
    int b[] = {3,4,5,6,7,0,1,2};
    int searchResult =
    a.SearchRotatedArray2(b, sizeof(b)/sizeof(int),99);
    cout<<"SearchResult = "<<searchResult<<endl;

    for(auto i : b)
        cout<<i<<",";
}
