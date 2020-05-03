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
                            data[j+1]= data[j];  // ˳����ȷ��Ԫ�أ�λ��ȫ������һλ��ֱ���ҵ�Ӧ������ĵص㡣
                        else
                            break;
                    }
                data[j+1] = temp;  // ���һ������� +1 .
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

            int step = unitNo/2;  // stepΪ������ÿ�μ�Ϊԭ����һ�롣  for each group: [ (n-1)*step ,

            for(;step > 1; step /= 2)
            {
                for(int j=0 ; j < step ; j++)
                {
                    InsertionSort(data+j, unitNo - j, step);  // ��data+j ��ʼ insert sort�� һֱ������data��ĩβ������Ϊstep
                }
            }
            InsertionSort(data, unitNo, 1);

            return true;
        }
    void InsertionSort(Type* data, int TotalN, int step) // �˴�totalN����������������ĳ��ȣ����������������Ǳ仯�ģ����Բ�һ����step����������
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

    void QuickPartition(Type* data, int l, int r)   // �����ź�size���ܸ�죬0  �� N-1�� ��N �������� �����˴�û�й�ϵ.....
        {
            if(l>=r-1) return; // >= ����Ҫ
            int i = partition(data, l, r);
            QuickPartition(data, l, i);
            QuickPartition(data, i+1, r);
        }

    int partition(Type* data, int l, int r)
        {
            if(l==r-1) return l;

            int pivot = data[l];
            int i=l, j=r-1; // �˴� i ���ܵ��� l+1, ��ΪҪ���� a[l] ����С������� �� j=l ʱ�����������п��ܷ�������
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
            if(r-l==1)   // ע�� Mergesort �����ֵײ����
                {
                    if(data[l]>data[r])
                        exchg(data[l], data[r]);
                    return;
                }

            int mid = (r+l)/2; // �˴�Ϊ�Ӻţ���
            MergeSort(data, l,mid);
            MergeSort(data, mid+1, r);

            int n=r-l+1;
            int i=0, j=l, k=mid+1;
            Type temp[n];

            for( i=0; i<n ; i ++)  // ������������� j k Ϊ������ i ��̫���׿���  j < mid+1 && k < r+1
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

             i++; // ���Ҫ�� for ѭ����ע�� ���һ��ѭ�������Ƿ���� �� break ����ѭ������֮ǰ���������һ�β��������ԣ� ��


            if( k==r+1) // ע��˴��� r + 1
                {

                    for(;i<n; i++)   // ��һ���ֺŲ���ʡ�ԣ���
                    {temp[i] = data[j];
                    j++;}
                }

            if( j == mid+1 )
                {
                    for(;i<n; i++)
                    {temp[i] = data[k];
                    k++;}
                }


            for(i=0; i < n; i++) {data[l+i]=temp[i];}  // ע��˴��� l + i.



        }
///////////////######################////////////////////

    bool BucketSort( int arrsize, Type minvl, Type maxvl)
        {
            BucketSort(data, arrsize, minvl, maxvl);
        }

    void BucketSort(Type* data, int arrsize, Type minvl, Type maxvl )  // Ҫ������ͬԪ����ô���أ�����
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
    int intset[] = {30,40,20,10,60,50, 80, 90, 70,110, 5,2,7,8};  // �˴� SortClass ��ʵ����operate intset[]�� ������ �� ����һ�������copy�����ǣ�����
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
