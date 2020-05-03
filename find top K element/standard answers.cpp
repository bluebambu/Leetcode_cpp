#include <iostream>
#include <map>
#include <tr1/unordered_map>
#include <vector>
#include <queue>

using namespace std;

typedef     pair<string,int>        PSI;
typedef     vector<PSI>             VPSI;

struct MinPQComparator{ // for min heap priority queue
    // frequency, then item:
    bool operator() (const PSI &lhs, const PSI &rhs) const {
        if (lhs.second >  rhs.second) return true;
        if (lhs.second <  rhs.second) return false;
        if (lhs.second == rhs.second) return (lhs.first < rhs.first);
    };
};

typedef     priority_queue <PSI, vector<PSI >, MinPQComparator> myMinPQ_Type;
//typedef     map<string, int> myHash_Type;
typedef     tr1::unordered_map<string, int> myHash_Type;
//=============================================================================

myHash_Type     FrequencyOf;    //O(M) space
myMinPQ_Type    MinHeapPQ;  //O(K) space
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

void solveIt(){ // via Min Heap
    //map<string, int>::iterator it;
    tr1::unordered_map<string, int>::iterator it;
    for(it = FrequencyOf.begin(); it != FrequencyOf.end(); ++it){   // O(M)
        MinHeapPQ.push(make_pair(it->first, it->second));       // O(log K)

        if (MinHeapPQ.size() > K){
            // surely the top is NOT one of K most frequent items! Discard it.
            MinHeapPQ.pop();    // O(log K)
        }
    };// for it
};
//-----------------------------------------------------------------------------

void printResult(){
    vector<PSI> myStack;
    while(!MinHeapPQ.empty()){
        myStack.push_back(MinHeapPQ.top());
        MinHeapPQ.pop();
    };

    //print reverse order: most frequent first
    for(int i = myStack.size()-1; i>=0; i--){
        cout << myStack[i].first<<" "<<myStack[i].second << endl;
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
