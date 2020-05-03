#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


//
//smart_ptr.h : our simple smart pointer
//
// 最重要的是 constructor， copy， assign

template <class T>
class SmartPointer {
public:
    SmartPointer(T *ptr) {
        ref = ptr;
        ref_count = new int(0);
        *ref_count = 1;
    }
    SmartPointer(SmartPointer<T> &sptr) {
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
    }

    // 注意返回值是  SmartPointer<T>&  template + reference
    SmartPointer<T>& operator = (SmartPointer<T> &sptr) {
        if (this == &sptr) return *this; // attention!!
        if (*ref_count > 0) remove();

        /**


The access modifiers work on class level, and not on object level.

That is, two objects of the same class can access each others private members.

        */
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
        return *this;
    }
    ~SmartPointer() {
        remove();
    }
    T getValue() {
        return *ref;
    }

protected:
    T *ref;
    int *ref_count;

    // remove 兼具了 count-- 和 销毁0 count 的resource的任务；
    void remove() {
        --(*ref_count);
        if (*ref_count == 0) {
            delete ref;
            free (ref_count);
            ref = nullptr;
            ref_count = nullptr;
        }
    }
};






int main()
{
    SmartPointer<int> a(new int(8));
    SmartPointer<int> b(new int(12));
    SmartPointer<int> c(b);

}
