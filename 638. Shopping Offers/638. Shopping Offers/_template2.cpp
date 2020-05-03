// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);

	while (q.size()){
		int n = q.size();
		for (int i = 0; i < n; ++i){
			TreeNode* front = q.front();
			q.pop();

			if (!front)
				cout << "# ";
			else{
				cout << front->val << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
//  In LeetCode Store, there are some kinds of items to sell. Each item has a price.

// However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.

// You are given the each item's price, a set of special offers, and the number we need to buy for each item. The job is to output the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers.

// Each special offer is represented in the form of an array, the last number represents the price you need to pay for this special offer, other numbers represents how many specific items you could get if you buy this offer.

// You could use any of special offers as many times as you want.

// Example 1:

// Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
// Output: 14
// Explanation: 
// There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
// In special offer 1, you can pay $5 for 3A and 0B
// In special offer 2, you can pay $10 for 1A and 2B. 
// You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.

// Example 2:

// Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
// Output: 11
// Explanation: 
// The price of A is $2, and $3 for B, $4 for C. 
// You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C. 
// You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C. 
// You cannot add more items, though only $9 for 2A ,2B and 1C.


// pass AC
class Solution {
public:
	int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
		int res = INT_MAX; 
		for (int i = 0; i < special.size(); ++i){
			vector<int>& curSpecial = special[i]; 
			int j = 0; 
			for (; j < needs.size(); ++j){
				if (needs[j] < curSpecial[j]){
					break; 
				}
			}
			if (j != needs.size()){
				continue;
			}

			for (int k = 0; k < needs.size(); ++k){
				needs[k] -= curSpecial[k]; 
			}
			res = min(res, curSpecial.back() + shoppingOffers(price, special, needs)); 
			for (int k = 0; k < needs.size(); ++k){
				needs[k] += curSpecial[k]; 
			}
		}

		int res2 = 0;
		for (int k = 0; k < needs.size(); ++k)
			res2 += needs[k] * price[k];

		res = min(res, res2);
		return res; 
	}
};


// tried a dp method. has error. 
class Solution2 {
public:
	int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
		int topState = getState(needs), numOffr = special.size(); 
		vector<vector<int>> dp(topState + 1, vector<int>(numOffr + 1, 0));
		
		for (int i = 1; i < topState + 1; ++i){
			dp[i][0] = calcRaw(price, getRealVec(i)); 
		}

		for (int j = 1; j <= numOffr; ++j){
			for (int i = 1; i <= topState; ++i){
				dp[i][j] = INT_MAX; 
				vector<int> curOffer = special[j - 1]; 
				for (int k = 0; offrGood(i, curOffer, k) ; ++k){
					int offrStripped = stripOffr(i, curOffer, k); 
					dp[i][j] = min(dp[i][j - 1], dp[offrStripped][j - 1] + curOffer.back()); 
				}
			}
		}

		return dp.back().back(); 
	}

	int getState(vector<int> needs){
		int base = 6; 
		int res = 0; 
		for (int i = 0; i < needs.size(); ++i){
			res = base*res + needs[i]; 
		}
		return res; 
	}

	vector<int> getRealVec(int state){
		int base = 6; 
		vector<int> r; 
		while (state > 0){
			r.push_back(state % 6); 
			state /= 6; 
		}
		reverse(r.begin(), r.end()); 
		return r; 
	}

	int calcRaw(vector<int>& price, vector<int> realVec){
		int r = 0; 
		for (int i = 0; i < price.size(); ++i){
			r += price[i] * realVec[i]; 
		}
		return r; 
	}

	bool offrGood(int state, vector<int>& curOffer, int freq){
		vector<int> realvec = getRealVec(state); 
		for (int i = 0; i < freq; ++i){
			for (int j = 0; j < realvec.size(); ++j){
				if (realvec[j] < curOffer[j])
					return false; 
				realvec[j] -= curOffer[j]; 
			}
		}
		return true; 
	}

	int stripOffr(int state, vector<int>& curOffer, int freq){
		vector<int> realvec = getRealVec(state);
		for (int i = 0; i < freq; ++i){
			for (int j = 0; j < realvec.size(); ++j){
				realvec[j] -= curOffer[j];
			}
		}
		return getState(realvec);
	}
}; 


class Solution3 {
public:
	int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
		return dfs(price, special, special.size()-1, needs); 
	}

	int dfs(vector<int>& price, vector<vector<int>>& special, int curId, vector<int> needs){
		int r = 0; 

		if (curId < 0){
			for (int i = 0; i < price.size(); ++i)
				r += price[i] * needs[i];
			return r;
		}

		r = dfs(price, special, curId - 1, needs); 

		vector<int>& curSpecial = special[curId]; 
		bool good = true; 
		int freq = 0;  // important
		while (true){
			freq += 1; 

			for (int i = 0; i < needs.size(); ++i){
				if (needs[i] < curSpecial[i]){
					good = false; 
					break;
				}

				needs[i] -= curSpecial[i]; 
			}
			if (!good)
				break;

			r = min(r, dfs(price, special, curId - 1, needs) + freq * curSpecial.back()); 
		}

		return r; 
	}
}; 

class Solution4 {
public:
	map<vector<int>, int> cache; 
	int shoppingOffers(vector<int>& price, vector<vector<int>>& specials, vector<int>& needs) {
		int items_num = price.size(); 
		for (int i = 0; i < items_num; ++i){
			vector<int> item_fake_special(items_num, 0); 
			item_fake_special[i] = 1; 
			item_fake_special.push_back(price[i]); 
			specials.push_back(item_fake_special); 
		}

		prt2Layer(specials); 

		return dfs(needs, specials);
	}

	int dfs(vector<int> needs, vector<vector<int>>& specials){
		if (cache.count(needs))
			return cache[needs]; 

		bool all_clear = true; 
		for (auto i : needs)
			if (i != 0)
				all_clear = false; 
		if (all_clear)
			return 0; 

		int res = INT_MAX; 
		for (vector<int>& sp : specials){
			int sp_price = sp.back(); 
			bool is_special_valid = true; 
			for (int i = 0; i < sp.size() - 1; ++i){
				if (sp[i] > needs[i]){
					is_special_valid = false; 
					break;
				}
			}
			if (!is_special_valid)
				continue;

			vector<int> next_possible_need = needs; 
			for (int i = 0; i < sp.size() - 1; ++i){
				next_possible_need[i] -= sp[i]; 
			}

			res = min(res, sp_price + dfs(next_possible_need, specials)); 
		}

		cache[needs] = res; 
		return res; 
	}
}; 

int main(){
	Solution a; 
	Solution4 a2;

	vector<int> price = { 2, 5 }; 
	vector<vector<int>> offer = { { 3, 0, 5 }, { 1, 2, 10 } }; 
	vector<int> needs = { 3, 2 }; 

	vector<int> price2 = { 9, 9 };
	vector<vector<int>> offer2 = { { 1, 1, 1 } };
	vector<int> needs2 = { 2, 2 };

	cout << a.shoppingOffers(price, offer, needs) << endl; 
	cout << a2.shoppingOffers(price2, offer2, needs2) << endl;


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

