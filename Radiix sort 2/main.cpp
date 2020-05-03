// This is the text editor interface.
// Anything you type or change here will be seen by the other person in real tim.
#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};


class Solution
{
public:
    vector<int> RadiixSort(vector<int> vec){
        if(vec.empty()) return vec;

        int m = vec[0];
        for(int i=0; i<vec.size(); ++i){
            m = max(m, vec[i]);
        }

        for(int i=1; m/i>0; i*=10)
            cnt_sort(vec, i);

        return vec;
    }

    void cnt_sort(vector<int>& vec, int exp){
        vector<int> radix(vec.size(), 0), buffer(vec.size(), 0);

        for(int i=0; i<vec.size(); ++i)
            ++radix[(vec[i]/exp)%10];

        for(int i=1; i<radix.size(); ++i)
            radix[i]+=radix[i-1];

        for(int i=vec.size()-1; i>=0; --i){
            buffer[radix[(vec[i]/exp)%10]-1] = vec[i];
            --radix[(vec[i]/exp)%10];
        }

        vec = buffer;
    }
};

int main()
{
	Solution a;

	auto b = a.RadiixSort({112, 1, 4,67, 5, 53, 34, 43, 9, 77});

	for (auto i : b)
	{
		//for (auto j : i)
			cout << i << " ";
		cout << endl;
	}
}
