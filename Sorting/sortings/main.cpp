#include <iostream>
#include <stdlib.h>

using namespace std;


template<typename Type>
class SortClass
{
private:
    Type* data; //data to be sorted;
    int unitNo;


public:
    SortClass() {}
    SortClass(Type* a, int b):data(a), unitNo(b) {}
///////////////######################////////////////////
    bool SelectSort()
        {
            if(data == NULL) return false;

            Type* minvalue;
            for(int i=1; i<unitNo;i++)
            {
                minvalue = FindMin(data, i, unitNo);
                if(data[i-1] > *minvalue)
                    exchg(data[i-1], *minvalue);
            }

            return true;

        }
///////////////######################////////////////////
    bool InsertionSort()
        {
            if(data==NULL) return false;

            exchg(data[0], *(FindMin(data, 0, unitNo)));
            for(int i=2; i<unitNo; i++)
            {
                Type temp = data[i];
                int j;
                for(j = i - 1; j>0 ; j--)
                    {
                        if(data[j] > temp)
                            data[j+1]= data[j];  // 顺序正确的元素，位置全部右移一位，直到找到应当插入的地点。
                        else
                            break;
                    }
                data[j+1] = temp;  // 体会一下这里的 +1 .
            }
            return true;
        }
///////////////######################////////////////////
    bool BubbleSort()
        {
            if(data == NULL) return false;

            int i=0;
            int j=0;

            while(i<unitNo)
            {
                j=0;
                while(j<(unitNo-i))
                    {
                        if(data[j] > data[j+1])
                            exchg(data[j], data[j+1]);
                        j++;
                    }
                i++;
            }
        }
///////////////######################////////////////////
    bool ShellSort()
        {
            if(data == 0) return false;

            int step = unitNo/2;  // step为步长，每次减为原来的一半。  for each group: [ (n-1)*step ,

            for(;step > 1; step /= 2)
            {
                for(int j=0 ; j < step ; j++)
                {
                    InsertionSort(data+j, unitNo - j, step);  // 从data+j 开始 insert sort， 一直操作到data的末尾，步长为step
                }
            }
            InsertionSort(data, unitNo, 1);

            return true;
        }
    void InsertionSort(Type* data, int TotalN, int step) // 此处totalN是用来操作的数组的长度，但是在主程序中是变化的，所以不一定是step的整倍数。
        {
            int i;
            for(i=step; i < TotalN ; i += step )
            {
                for(int j=i; j>0 && data[j] < data[j-step]; j -= step)
                    exchg(data[j], data[j-step]);
            }

        }

///////////////######################////////////////////
    bool QuickSort()
        {
            QuickPartition(data, 0, unitNo);
        }

    void QuickPartition(Type* data, int l, int r)   // 数组编号和size不能搞混，0  ～ N-1， 有N 个数！！ 不过此处没有关系.....
        {
            if(l>=r-1) return; // >= 很重要
            int i = partition(data, l, r);
            QuickPartition(data, l, i);
            QuickPartition(data, i+1, r);
        }

    int partition(Type* data, int l, int r)
        {
            if(l==r-1) return l;

            int pivot = data[l];
            int i=l, j=r-1; // 此处 i 不能等于 l+1, 因为要考虑 a[l] 是最小的情况， 即 j=l 时候的情况（很有可能发生）。
            while(1)
            {
                while(data[j] > pivot && j>i) j--; // the last j value means that data[j] <= pivot; j can be [l, r]. if pivot is the smallest, j=l;
                while(data[i] < pivot && i<j)
                    {i++;}// i can be [l, r]. If i = j, it's ok. i can not > j.
                if(i>=j) break;
                exchg(data[i], data[j]);
            }
            if(data[l] > data[i])
                exchg(data[l], data[i]);
            return i;
        }
///////////////######################////////////////////
    bool MergeSort()
        {
            MergeSort(data, 0, unitNo-1);
        }

    void MergeSort(Type*& data, int l, int r)
        {
            if(l>=r) return;
            if(r-l==1)   // 注意 Mergesort 有两种底部情况
                {
                    if(data[l]>data[r])
                        exchg(data[l], data[r]);
                    return;
                }

            int mid = (r+l)/2; // 此处为加号！！
            MergeSort(data, l,mid);
            MergeSort(data, mid+1, r);

            int n=r-l+1;
            int i=0, j=l, k=mid+1;
            Type temp[n];

            for( i=0; i<n ; i ++)  // 限制条件最好以 j k 为主，用 i 不太容易控制  j < mid+1 && k < r+1
            {
                if(data[j] <= data[k])
                {
                    temp[i] = data[j];
                    j++;
                }
                else if( data[j] > data[k])
                {
                    temp[i] = data[k];
                    k++;
                }

                if( k == r + 1 || j == mid + 1)
                    break;
             }

             i++; // 如果要用 for 循环，注意 最后一项循环操作是否进行 （ break 会在循环操作之前，所以最后一次操作被忽略） 。


            if( k==r+1) // 注意此处的 r + 1
                {

                    for(;i<n; i++)   // 第一个分号不能省略！！
                    {temp[i] = data[j];
                    j++;}
                }

            if( j == mid+1 )
                {
                    for(;i<n; i++)
                    {temp[i] = data[k];
                    k++;}
                }


            for(i=0; i < n; i++) {data[l+i]=temp[i];}  // 注意此处的 l + i.



        }
///////////////######################////////////////////

    bool BucketSort( int arrsize, Type minvl, Type maxvl)
        {
            BucketSort(data, arrsize, minvl, maxvl);
        }

    void BucketSort(Type* data, int arrsize, Type minvl, Type maxvl )  // 要是有相同元素怎么办呢？？？
        {
            if(minvl == maxvl) return;

            Type Range = maxvl - minvl +1;
            Type* const Buckets = new Type[Range]();  // all units are 0.

            int i, j=0;

            for(i=0; i<arrsize; i++)
            {
                Buckets[data[i]]=data[i];
            }

            for(i=0; i<Range ;i++)
            {
                if(Buckets[i] !=0)
                    data[j++] = Buckets[i];
            }

            delete []Buckets;
        }

///////////////######################////////////////////
    void exchg(Type& a, Type& b) { Type c = a; a = b; b = c;}
///////////////######################////////////////////
    Type* FindMin(Type* arr, int l, int r) // arr[l] -> arr[r-1], otherwise there will be r-l+1 units.
        {
            // if(1) boundary condition, what if r > size of arr
            if(arr==NULL) return NULL;
            Type* MinUnitPtr = &arr[l];

            for(int i=l+1; i<r ; i++)
                {  if( arr[i] < *MinUnitPtr )
                    MinUnitPtr = &arr[i]; }
            return MinUnitPtr;

        }
///////////////######################////////////////////
    void SortPrint() { for(int i=0; i<unitNo; i++) cout<<data[i]<<" ";}
};

int main()
{
    int intset[] = {30,40,20,10,60,50, 80, 90, 70,110, 5,2,7,8};  // 此处 SortClass 其实是在operate intset[]， 而不是 类 中有一个数组的copy，谨记！！！
    int setnum = sizeof(intset)/sizeof(intset[0]);
    cout<<setnum<<endl;

    SortClass<int> ssssss(intset, setnum);
    cout<<"original: ";ssssss.SortPrint();

//    ssssss.SelectSort();
//    cout<<"SelectSort: ";
//    ssssss.SortPrint(); cout<<endl;

//    ssssss.InsertionSort();
//    cout<<endl<<"InsertionSort: ";
//    ssssss.SortPrint(); cout<<endl;

//    ssssss.BubbleSort();
//    cout<<endl<<"BubbleSort: ";
//    ssssss.SortPrint(); cout<<endl;

//    ssssss.ShellSort();
//    cout<<endl<<"ShellSort: ";
//    ssssss.SortPrint(); cout<<endl;

    ssssss.QuickSort();
    cout<<endl<<"QuickSort: ";
    ssssss.SortPrint(); cout<<endl;

//    ssssss.MergeSort();
//    cout<<endl<<"MergeSort: ";
//    ssssss.SortPrint(); cout<<endl;

    ssssss.BucketSort(setnum, 0, 150);
    cout<<endl<<"BucketSort: ";
    ssssss.SortPrint(); cout<<endl;

}
