#include <iostream>
#include <tr1/unordered_map>
#include <vector>
#include <queue>

using namespace std;

typedef     pair<string,int>        PSI;
typedef     vector<PSI>             VPSI;
typedef     tr1::unordered_map<string, int>     myHash_Type;

struct MaxHeapComparator{ // Max Heap
    // frequency, then item
    bool operator() (const PSI &lhs, const PSI &rhs) const {
        if (lhs.second >  rhs.second) return false;
        if (lhs.second <  rhs.second) return true;
        if (lhs.second == rhs.second) return (lhs.first > rhs.first);
    };
};
//=============================================================================

myHash_Type     FrequencyOf;    //O(M) space
VPSI            MaxHeap;       //O(M) space
int             N, K;
//=============================================================================

void readInput(){
    cin >> N;
    string aName;
    for(int i = 0; i<N; i++){   //  O(N)
        cin >> aName;
        FrequencyOf[aName]++;   // O(1) hashing;
    };
    cin >> K;
};
//-----------------------------------------------------------------------------

void solveIt(){ // via Max Heap
    tr1::unordered_map<string, int>::iterator it;
    for(it = FrequencyOf.begin(); it != FrequencyOf.end(); ++it){   // O(M)
        MaxHeap.push_back(make_pair(it->first, it->second));
    };// for it

    make_heap(MaxHeap.begin(), MaxHeap.end(), MaxHeapComparator()); // O(M)
};
//-----------------------------------------------------------------------------

void printResult(){
    for(int i=0; i<K;i++){ //O(K)
        if(MaxHeap.size()<1) break;
        PSI aPair = MaxHeap.front();
        pop_heap(MaxHeap.begin(), MaxHeap.end(), MaxHeapComparator());//O(lgM)
        MaxHeap.pop_back();
        cout <<aPair.first <<" "<<aPair.second<<endl;
    }
};
//=============================================================================

int main()
{
    readInput();
    solveIt();
    printResult();
    return 0;
}
