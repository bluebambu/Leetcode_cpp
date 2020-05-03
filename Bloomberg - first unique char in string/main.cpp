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
    char fuc(string s){
        int cnt[256]={0};
        string record;

        for(int i=0; i<s.size(); ++i){
            char tmp = s[i];
            if(cnt[tmp]==0)
                record.push_back(tmp);
            cnt[tmp]++;
        }

        for(int i=0; i<record.size(); ++i){
            if(cnt[record[i]]==1)
                return record[i];
        }

        return 0;
    }
};

int main()
{
	Solution a;

	auto b = a.fuc("abcabcccdabefio94832");

	//for (auto i : b)
	{
		//for (auto j : i)
			cout << b << " ";
		cout << endl;
	}
}
