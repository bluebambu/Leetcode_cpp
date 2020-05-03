    #include <stdio.h>

    void output_array(int data[], int n)
    {
        int i;
        for(i = 0; i < n; i++)
            printf("%d ", data[i]);
        printf("\n");
    }
    void swap(int *a, int *b)
    {
        int x;
        x = *a;
        *a = *b;
        *b = x;
    }
    void insertion_sort(int data[], int n, int increment)
    {
        int i, j;
        for(i = increment; i < n; i += increment)
            for(j = i; j >= increment && data[j] > data[j - increment]; j -= increment)
                swap(&data[j], &data[j - increment]);       // swap �� a[j-1]=a[j] �������ڣ� ���ø�ֵ���һ���������������������ӷ�ʱһЩ��
    }
    void shellsort(int data[], int n)
    {
        int i, j;
        for(i = n / 2; i > 2; i /= 2)
            for(j = 0; j < i; j++)
                insertion_sort(data + j, n - j, i);
        insertion_sort(data, n, 1);
    }


    int main()
    {
        int data[] = {5, 3, 1, 665, 77, 66, 44, 11, 10, 9, 8, 6};
        output_array(data, 12);
        shellsort(data, 12);
        output_array(data, 12);
        return 0;
    }
