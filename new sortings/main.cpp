#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <map>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};


class Solution
{
public:
    void BubbleSort(vector<int>& intset)
    {
        for(int i=0; i<intset.size();++i)
            for(int j=0; j+1<intset.size()-i; ++j)
        {
            if(intset[j] > intset[j+1]) swap(intset[j], intset[j+1]);
        }
    }

    void SelectSort(vector<int>& intset)
    {
        int min=-999, idxmin=-1;

        for(int i=0; i<intset.size(); ++i)
        {
            min=999;
            idxmin=-1;

            for(int j=i; j<intset.size();++j)
            {
                if(intset[j] < min)
                {
                    min=intset[j];
                    idxmin=j;
                }
            }

            swap(intset[i], intset[idxmin]);
        }
    }

    void HeapSort(vector<int>& intset)
    {
        int size = intset.size();

        while(1)
        {
            int lastp = (size-2)/2; // last parent

            for(int i=lastp; i>=0; --i)
            {
                Heapify(intset, i, size);
            }

            swap(intset[0], intset[(size--)-1]);

            if(size==0) break;
        }
    }

    void Heapify(vector<int>& intset, int idx, int size)
    {
        int left = 2*idx + 1;
        int right = 2*(idx + 1);
        int imax = idx;

        if(left < size && intset[left] > intset[idx]) // 这里是找到 parent，left，right最大的一个，而不是比 parent大的那一个
        {
            imax = left;
        }

        if(right < size && intset[right] > intset[imax])
        {
            imax = right;
        }

        if(imax!=idx)
        {
            swap(intset[imax], intset[idx]);
            Heapify(intset, imax, size);
        }
    }

    void RadiixSort(vector<int>& intset)
    {
        map<int, vector<int>> bucket;

        for(int i : intset )
        {
            bucket[i%10].push_back(i);
        }

        int k=0;

        for(auto i : bucket)
            for(auto j : i.second)
                intset[k++]=j;


        bucket.clear();


        for(int i : intset)
            bucket[(i/10)%10].push_back(i);


        k=0;

        for(auto i : bucket)
            for(auto j : i.second)
                intset[k++]=j;
    }

    void QuickSort(vector<int>& intset)
    {
        QuickSort2(intset, 0, intset.size()-1);
    }

    void QuickSort2(vector<int>& intset, int left, int right)
    {
        if(left>=right) return;
        int i = separate(intset, left, right);
        QuickSort2(intset, left, i-1);
        QuickSort2(intset, i+1, right);
    }

    int separate(vector<int>& intset, int left, int right)
    {
        int pivot = intset[right];
        int p=left, q=p;

        while(1)
        {
            if(intset[p]>pivot)
            {
                q=p;
                while(intset[q]>pivot) ++q;

                if(q==right)
                {
                    swap(intset[p], intset[right]);
                    return p;
                }
                else
                {
                    swap(intset[p], intset[q]);
                }
            }

            ++p;

            if(p==right) return p;
        }
    }

    void HeapSort2(vector<int> & data)
    {
        int size = data.size();

        while(size>1)
        {
            int lastp = (size-2)/2;

            for(int j=lastp; j>=0; --j)
                Heapify2(data, j, size);

            swap(data[0], data[size-1]);

            --size;
        }

    }

    void Heapify2(vector<int> & data, int idx, int size)
    {
        int imax = idx, left = idx*2+1, right=(idx+1)*2;

        if( left<size && data[left]>data[idx])
            imax=left;

        if( right<size && data[right]>data[imax])
            imax=right;

        if( imax!=idx)
            {
                swap(data[imax], data[idx]);

                Heapify2(data, imax, size);
            }
    }

    void RadiixSort2(vector<int> & data)
    {
        unordered_map<int, vector<int>> help;

        for(int i : data)
            help[i%10].push_back(i);

        int k=0;

        for(int i=0; i<10; ++i)
        {
            if( help.find(i)!=help.end() )
                {
                    for(int j : help[i])
                        data[k++]=j;
                }
        }

        k=0;
        help.clear();

        for(int i : data)
            help[(i/10)%10].push_back(i);

        for(int i=0; i<10; ++i)
        {
            if( help.find(i)!=help.end() )
                {
                    for(int j : help[i])
                        data[k++]=j;
                }
        }

        k=0;
        help.clear();

        for(int i : data)
            help[(i/100)%10].push_back(i);

        for(int i=0; i<10; ++i)
        {
            if( help.find(i)!=help.end() )
                {
                    for(int j : help[i])
                        data[k++]=j;
                }
        }
    }

    void QuickSort3(vector<int> & data)
    {
        QuickSortMain3(data, 0, data.size()-1);
    }

    void QuickSortMain3(vector<int>& data, int left, int right)
    {
        if(left>=right) return;

        int i = partition2(data, left, right);
        QuickSortMain3(data, left, i-1);
        QuickSortMain3(data, i+1, right);
    }

    int partition2(vector<int>& data, int left, int right)
    // use data[right] as pivot
    {
        int pivot = data[right];
        int p=left, q;

        while(p<right)
        {
            if(data[p] > pivot)
            {
                for(q=p; q<=right; ++q)
                {
                    if(q==right)
                    {
                        swap(data[p], data[right]);
                        return p;
                    }

                    if(data[q] < pivot)
                    {
                        swap(data[p], data[q]);
                        break;
                    }
                }
            }

            ++p;
        }

        return p;
    }

    void HeapSort3(vector<int>& intset)
    {
        int size = intset.size();

        while(size>1)
        {
            int lastp = (size-2)/2;

            for(int i=lastp; i>=0; --i)
            {
                Heapify(intset, i, size);
            }

            swap(intset[0], intset[size-1]);

            --size;
        }
    }

    void Heapify3(vector<int>& intset, int i, int size)
    {
        int left = 2*i+1;
        int right = 2*(i+1);
        int imax = i;

        if(left < size-1 && intset[left] > intset[i])
            imax=left;
        if(right< size-1 && intset[right]>intset[imax])
            imax=right;
        if(imax != i)
        {
            swap(intset[i], intset[imax]);
            Heapify3(intset, imax, size);
        }
    }

    void QuickSort4( vector<int> &intset)
    {
        QuickSort4_main(intset, 0, intset.size()-1);
    }

    void QuickSort4_main(vector<int>& intset, int left, int right)
    {
        if(left>=right) return;
        int i = partition3(intset, left, right);
        QuickSort4_main(intset, left, i-1);
        QuickSort4_main(intset, i+1, right);
    }

    int partition3(vector<int>& intset, int left, int right)
    {
        int pivot = intset[right];
        int p=left, q;

        for(; p<right;)
        {
            if(intset[p] > pivot)
            {
                for(q=p+1; q<=right; ++q)
                {
                    if(q==right)
                    {
                        swap(intset[p], intset[right]);
                        return p;
                    }

                    if(intset[q]<pivot)
                        {
                            swap(intset[p], intset[q]);
                            break;
                        }
                }
            }

            ++p;
        }

        return right;
    }
};

int main()
{
    Solution a;

    vector<int> intset {30,40,20,10,60,50, 80, 90, 70, 5,2,7,8,110};

    a.QuickSort4(intset);

    for(auto i:intset)
        cout<<i<<" ";
}
