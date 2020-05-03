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
// Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.
// However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle. 
// You need to return the least number of intervals the CPU will take to finish all the given tasks.
// Example 1:
// Input: tasks = ['A','A','A','B','B','B'], n = 2
// Output: 8
// Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

// Note:
// The number of tasks is in the range [1, 10000].
// The integer n is in the range [0, 100].


// pass AC
class Solution {
public:

	int leastInterval(vector<char>& tasks, int n) {
		typedef pair<char, int> PCI; 

		struct comp{
			bool operator()(PCI& a, PCI& b){
				return a.second < b.second; 
			}
		};


		priority_queue<PCI, vector<PCI>, comp> q; 

		unordered_map<char, int> m; 
		for (int i = 0; i < tasks.size(); ++i){
			m[tasks[i]]++; 
		}

		for (auto a : m)
			q.push(a); 

		int bigNo = q.top().second; 
		if (bigNo*(n + 1) <= tasks.size())
			return tasks.size(); 

		int base = (bigNo - 1)*(n+1) + 1; 
		q.pop(); 

		while (!q.empty() && q.top().second == bigNo){
			base += 1; 
			q.pop(); 
		}
		return base; 
	}
};


// 其实不需要追踪哪个字母对应哪个出现次数， 只需要所有的出现次数并排序就够了
class Solution00 {
public:
	int leastInterval(vector<char>& tasks, int n) {
		vector<int> cnt(26, 0);
		for (char task : tasks) {
			++cnt[task - 'A'];
		}
		sort(cnt.begin(), cnt.end());
		int i = 25, mx = cnt[25], len = tasks.size();
		while (i >= 0 && cnt[i] == mx) --i;
		return max(len, (mx - 1) * (n + 1) + 25 - i);
	}
};



class Solution2 {
public:
	int leastInterval(vector<char>& tasks, int n) {
		if (tasks.empty())
			return 0; 

		vector<int> freq(26, 0); 
		for (auto c : tasks){
			freq[c - 'A'] += 1; 
		}

		vector<vector<int>> elem_freq; 
		for (int i = 0; i < 26; ++i){
			if (freq[i] > 0){
				elem_freq.push_back({ i, freq[i] }); 
			}
		}

		sort(elem_freq.begin(), elem_freq.end(), [](vector<int>&a, vector<int>&b){
			return a[1] > b[1]; 
		}); 

		int nround = elem_freq[0][1]; 
		int nmax = 0; 
		for (int i = 0; i < elem_freq.size(); ++i){
			if (elem_freq[i][1] == nround)
				nmax += 1; 
			else
				break;
		}

		return ((n+1)*(nround - 1) + nmax > tasks.size()) ? (n+1)*(nround - 1) + nmax : tasks.size();
	}
};

class Solution3 {
public:
	int leastInterval(vector<char>& tasks, int n) {
		if (tasks.empty()) return 0; 
		vector<int> freq(26, 0); 
		for (auto c : tasks)
			freq[c - 'A'] += 1;;
		sort(freq.rbegin(), freq.rend()); 
		prt1Layer(freq); 
		int m = freq[0], mcnt = 0; 
		for (auto i : freq)
			if (i == m)
				mcnt += 1; 
		return max((int)tasks.size(), (n + 1)*(m - 1) + mcnt); 
	}
}; 


class Solution4 {
public:
	int leastInterval(vector<char>& tasks, int n) {
		if(tasks.size() == 0)
			return 0; 

		map<int, int> freq; 
		for (auto t : tasks) freq[t-'A'] += 1;
		vector<pair<int, int>> elem_freq(freq.begin(), freq.end()); 

		sort(elem_freq.begin(), elem_freq.end(), [](pair<int, int>&a, pair<int, int>&b){
			return a.second > b.second; 
		}); 

		vector<int> nextpos(elem_freq.size(), 0); 

		int nrounds = elem_freq[0].second; 
		string res; 
		for (int i = 0; i < nrounds; ++i){
			for (int j = 0; j < elem_freq.size(); ++j){
				if (res.size() < nextpos[j]){
					res.push_back('*'); 
					--j; 
					continue;
				}

				if (elem_freq[j].second > 0){
					res.push_back(elem_freq[j].first + 'A');
					nextpos[j] += n + 1;
					elem_freq[j].second -= 1;
				}
			}
		}
		
		cout << res << endl; 
		return res.size(); 
	}
}; 


// wrong ans; 
class Solution5{
public:
	string leastInterval(vector<char>& tasks, int n){
		vector<vector<int>> alp_cnt(26, vector<int>(2, 0)); 
		for (auto& c : tasks){
			alp_cnt[c - 'A'][0] += 1; 
		}
		for (int i = 0; i < 26; ++i){
			alp_cnt[i][1] = i; 
		}
		sort(alp_cnt.rbegin(), alp_cnt.rend()); 
		
		vector<int> next_pos(26, 0); 
		string res; 

		while (alp_cnt[0][0]>0){
			for (int i = 0; i < alp_cnt.size(); ++i){
				if (alp_cnt[i][0]==0)
					break;

				if (res.size() >= next_pos[i]){
					res.push_back('A' + alp_cnt[i][1]); 
					--alp_cnt[i][0]; 
					next_pos[i] = res.size() + n; 
				}
				else
					res.push_back('*'); 
			}
		}

		return res; 
	}
};

// wrong ans; 
// {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B'}
// orig: AB*AB*A**A**A**A
// cur : A**A**A**AB*AB*A
class Solution6{
public:
	string leastInterval(vector<char>& tasks, int n){
		unordered_map<char, int> cnt;
		for (auto c : tasks) cnt[c] += 1; 
		map<int, unordered_set<char>> cnt_2_chars; 
		for (auto &p : cnt){
			cnt_2_chars[p.second].insert(p.first); 
		}
		
		unordered_map<char, int> pos; 
		string r; 
		while (!cnt_2_chars.empty()){
			unordered_set<char> &cur_most_chars = cnt_2_chars.rbegin()->second;
			int most_cnt = cnt_2_chars.rbegin()->first; 

			char to_use = *(cur_most_chars.begin()); 
			if (r.size() >= pos[to_use]){
				r.push_back(to_use);
				pos[to_use] = r.size() + n;
				cur_most_chars.erase(to_use);
				if (cur_most_chars.empty())
					cnt_2_chars.erase(prev(cnt_2_chars.end()));
				if (most_cnt > 1)
					cnt_2_chars[most_cnt - 1].insert(to_use);
			}
			else
				r.push_back('*'); 
		}
		return r; 
	}
};

// wrong ans; 
class Solution7{
public:
	string leastInterval(vector<char>& tasks, int n){
		unordered_map<char, int> cnt; 
		for (char c : tasks) cnt[c] += 1; 
		vector<pair<char, int>> char_freq(cnt.begin(), cnt.end()); 
		typedef pair<char, int> pci; 
		sort(char_freq.begin(), char_freq.end(), [](pci& a, pci& b){
			return a.second > b.second; 
		}); 

		string r; 
		int nrounds = char_freq[0].second; 
		unordered_map<char, int> char_pos; 
		for (int i = 0; i < nrounds; ++i){
			while (char_pos[char_freq[0].first] > r.size()){
				r.push_back('*'); 
			}
			for (int j = 0; j < char_freq.size(); ++j){
				if (char_freq[j].second > 0){
					r.push_back(char_freq[j].first); 
					char_pos[char_freq[j].first] = r.size() + n; 
					char_freq[j].second -= 1; 
				}
			}
		}

		return r; 
	}
}; 

// wrong ans, 当 ABCABCABC+DEFDEFDEF 这种，最大的A不能覆盖所有 char 的时候， 会fail。 感觉必须要用 map。 
class Solution8{
public:
	string leastInterval(vector<char>& tasks, int n){
		if (n == 0){
			string r; 
			for (auto c : tasks) r.push_back(c); 
			return r; 
		}
		unordered_map<char, int> cnt; 
		for (auto c : tasks) cnt[c] += 1; 
		typedef pair<char, int> pci; 
		vector<pci> char_freq(cnt.begin(), cnt.end()); 
		sort(char_freq.begin(), char_freq.end(), [](pci&a, pci&b){
			return a.second > b.second; 
		}); 

		string r; 
		int nrounds = char_freq[0].second; 
		unordered_map<char, int> pos; 
		for (int i = 0; i < nrounds; ++i){
			for (int j = 0; j <= n; ++j){
				bool found = false; 
				for (int k = 0; k < char_freq.size(); ++k){
					if (char_freq[k].second > 0 && pos[char_freq[k].first] <= r.size()){
						found = true; 
						r.push_back(char_freq[k].first); 
						pos[char_freq[k].first] = r.size() + n; 
						char_freq[k].second -= 1; 
						break;
					}
				}
				if (!found)
					r.push_back('*'); 
			}
		}

		while (r.back() == '*')
			r.pop_back(); 
		return r; 
	}
};

//  pass 5%
class Solution9{
public:
	string leastInterval(vector<char>& tasks, int n){
		unordered_map<char, int> cnt; 
		for (auto c : tasks) cnt[c] += 1; 

		map<int, unordered_set<char>> cnt_char; 
		for (auto&p : cnt)
			cnt_char[p.second].insert(p.first); 

		string r; 
		unordered_map<char, int> pos; 
		while (cnt_char.size()){
			bool found = false; 
			for (auto iter=cnt_char.rbegin(); iter!=cnt_char.rend(); ++iter){
				int curcnt = iter->first; 
				unordered_set<char>&set = iter->second; 
				for (char c: set){
					if (pos[c] <= r.size()){
						r.push_back(c); 
						pos[c] = r.size() + n; 
						set.erase(c); 
						if (set.empty())
							cnt_char.erase(curcnt); 
						if (curcnt > 1)
							cnt_char[curcnt - 1].insert(c); 
						found = true; 
						break;
					}
				}
				if (found)
					break;
			}
			if (!found)
				r.push_back('*'); 
		}
		return r; 
	}
}; 

int main(){
	Solution4 a;
	Solution9 a2;

	vector<char> b = { 'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'C', 'C' }; 
	vector<char> b2 = { 'A', 'C', 'D', 'B', 'E', 'F' }; 
	vector<char> b3 = { 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G' }; 
	vector<char> b4 = { 'A', 'A', 'A', 'B', 'B', 'B' }; 
	vector<char> b5 = { 'G', 'C', 'A', 'H', 'A', 'G', 'G', 'F', 'G', 'J', 'H', 'C', 'A', 'G', 'E', 'A', 'H', 'E', 'F', 'D', 'B', 'D', 'H', 'H', 'E', 'G', 'F', 'B', 'C', 'G', 'F', 'H', 'J', 'F', 'A', 'C', 'G', 'D', 'I', 'J', 'A', 'G', 'D', 'F', 'B', 'F', 'H', 'I', 'G', 'J', 'G', 'H', 'F', 'E', 'H', 'J', 'C', 'E', 'H', 'F', 'C', 'E', 'F', 'H', 'H', 'I', 'G', 'A', 'G', 'D', 'C', 'B', 'I', 'D', 'B', 'C', 'J', 'I', 'B', 'G', 'C', 'H', 'D', 'I', 'A', 'B', 'A', 'J', 'C', 'E', 'B', 'F', 'B', 'J', 'J', 'D', 'D', 'H', 'I', 'I', 'B', 'A', 'E', 'H', 'J', 'J', 'A', 'J', 'E', 'H', 'G', 'B', 'F', 'C', 'H', 'C', 'B', 'J', 'B', 'A', 'H', 'B', 'D', 'I', 'F', 'A', 'E', 'J', 'H', 'C', 'E', 'G', 'F', 'G', 'B', 'G', 'C', 'G', 'A', 'H', 'E', 'F', 'H', 'F', 'C', 'G', 'B', 'I', 'E', 'B', 'J', 'D', 'B', 'B', 'G', 'C', 'A', 'J', 'B', 'J', 'J', 'F', 'J', 'C', 'A', 'G', 'J', 'E', 'G', 'J', 'C', 'D', 'D', 'A', 'I', 'A', 'J', 'F', 'H', 'J', 'D', 'D', 'D', 'C', 'E', 'D', 'D', 'F', 'B', 'A', 'J', 'D', 'I', 'H', 'B', 'A', 'F', 'E', 'B', 'J', 'A', 'H', 'D', 'E', 'I', 'B', 'H', 'C', 'C', 'C', 'G', 'C', 'B', 'E', 'A', 'G', 'H', 'H', 'A', 'I', 'A', 'B', 'A', 'D', 'A', 'I', 'E', 'C', 'C', 'D', 'A', 'B', 'H', 'D', 'E', 'C', 'A', 'H', 'B', 'I', 'A', 'B', 'E', 'H', 'C', 'B', 'A', 'D', 'H', 'E', 'J', 'B', 'J', 'A', 'B', 'G', 'J', 'J', 'F', 'F', 'H', 'I', 'A', 'H', 'F', 'C', 'H', 'D', 'H', 'C', 'C', 'E', 'I', 'G', 'J', 'H', 'D', 'E', 'I', 'J', 'C', 'C', 'H', 'J', 'C', 'G', 'I', 'E', 'D', 'E', 'H', 'J', 'A', 'H', 'D', 'A', 'B', 'F', 'I', 'F', 'J', 'J', 'H', 'D', 'I', 'C', 'G', 'J', 'C', 'C', 'D', 'B', 'E', 'B', 'E', 'B', 'G', 'B', 'A', 'C', 'F', 'E', 'H', 'B', 'D', 'C', 'H', 'F', 'A', 'I', 'A', 'E', 'J', 'F', 'A', 'E', 'B', 'I', 'G', 'H', 'D', 'B', 'F', 'D', 'B', 'I', 'B', 'E', 'D', 'I', 'D', 'F', 'A', 'E', 'H', 'B', 'I', 'G', 'F', 'D', 'E', 'B', 'E', 'C', 'C', 'C', 'J', 'J', 'C', 'H', 'I', 'B', 'H', 'F', 'H', 'F', 'D', 'J', 'D', 'D', 'H', 'H', 'C', 'D', 'A', 'J', 'D', 'F', 'D', 'G', 'B', 'I', 'F', 'J', 'J', 'C', 'C', 'I', 'F', 'G', 'F', 'C', 'E', 'G', 'E', 'F', 'D', 'A', 'I', 'I', 'H', 'G', 'H', 'H', 'A', 'J', 'D', 'J', 'G', 'F', 'G', 'E', 'E', 'A', 'H', 'B', 'G', 'A', 'J', 'J', 'E', 'I', 'H', 'A', 'G', 'E', 'C', 'D', 'I', 'B', 'E', 'A', 'G', 'A', 'C', 'E', 'B', 'J', 'C', 'B', 'A', 'D', 'J', 'E', 'J', 'I', 'F', 'F', 'C', 'B', 'I', 'H', 'C', 'F', 'B', 'C', 'G', 'D', 'A', 'A', 'B', 'F', 'C', 'D', 'B', 'I', 'I', 'H', 'H', 'J', 'A', 'F', 'J', 'F', 'J', 'F', 'H', 'G', 'F', 'D', 'J', 'G', 'I', 'E', 'B', 'C', 'G', 'I', 'F', 'F', 'J', 'H', 'H', 'G', 'A', 'A', 'J', 'C', 'G', 'F', 'B', 'A', 'A', 'E', 'E', 'A', 'E', 'I', 'G', 'F', 'D', 'B', 'I', 'F', 'A', 'B', 'J', 'F', 'F', 'J', 'B', 'F', 'J', 'F', 'J', 'F', 'I', 'E', 'J', 'H', 'D', 'G', 'G', 'D', 'F', 'G', 'B', 'J', 'F', 'J', 'A', 'J', 'E', 'G', 'H', 'I', 'E', 'G', 'D', 'I', 'B', 'D', 'J', 'A', 'A', 'G', 'A', 'I', 'I', 'A', 'A', 'I', 'I', 'H', 'E', 'C', 'A', 'G', 'I', 'F', 'F', 'C', 'D', 'J', 'J', 'I', 'A', 'A', 'F', 'C', 'J', 'G', 'C', 'C', 'H', 'E', 'A', 'H', 'F', 'B', 'J', 'G', 'I', 'A', 'A', 'H', 'G', 'B', 'E', 'G', 'D', 'I', 'C', 'G', 'J', 'C', 'C', 'I', 'H', 'B', 'D', 'J', 'H', 'B', 'J', 'H', 'B', 'F', 'J', 'E', 'J', 'A', 'G', 'H', 'B', 'E', 'H', 'B', 'F', 'F', 'H', 'E', 'B', 'E', 'G', 'H', 'J', 'G', 'J', 'B', 'H', 'C', 'H', 'A', 'A', 'B', 'E', 'I', 'H', 'B', 'I', 'D', 'J', 'J', 'C', 'D', 'G', 'I', 'J', 'G', 'J', 'D', 'F', 'J', 'E', 'F', 'D', 'E', 'B', 'D', 'B', 'C', 'B', 'B', 'C', 'C', 'I', 'F', 'D', 'E', 'I', 'G', 'G', 'I', 'B', 'H', 'G', 'J', 'A', 'A', 'H', 'I', 'I', 'H', 'A', 'I', 'F', 'C', 'D', 'A', 'C', 'G', 'E', 'G', 'E', 'E', 'H', 'D', 'C', 'G', 'D', 'I', 'A', 'G', 'G', 'D', 'A', 'H', 'H', 'I', 'F', 'E', 'I', 'A', 'D', 'H', 'B', 'B', 'G', 'I', 'C', 'G', 'B', 'I', 'I', 'D', 'F', 'F', 'C', 'C', 'A', 'I', 'E', 'A', 'E', 'J', 'A', 'H', 'C', 'D', 'A', 'C', 'B', 'G', 'H', 'G', 'J', 'G', 'I', 'H', 'B', 'A', 'C', 'H', 'I', 'D', 'D', 'C', 'F', 'G', 'B', 'H', 'E', 'B', 'B', 'H', 'C', 'B', 'G', 'G', 'C', 'F', 'B', 'E', 'J', 'B', 'B', 'I', 'D', 'H', 'D', 'I', 'I', 'A', 'A', 'H', 'G', 'F', 'B', 'J', 'F', 'D', 'E', 'G', 'F', 'A', 'G', 'G', 'D', 'A', 'B', 'B', 'B', 'J', 'A', 'F', 'H', 'H', 'D', 'C', 'J', 'I', 'A', 'H', 'G', 'C', 'J', 'I', 'F', 'J', 'C', 'A', 'E', 'C', 'H', 'J', 'H', 'H', 'F', 'G', 'E', 'A', 'C', 'F', 'J', 'H', 'D', 'G', 'G', 'D', 'D', 'C', 'B', 'H', 'B', 'C', 'E', 'F', 'B', 'D', 'J', 'H', 'J', 'J', 'J', 'A', 'F', 'F', 'D', 'E', 'F', 'C', 'I', 'B', 'H', 'H', 'D', 'E', 'A', 'I', 'A', 'B', 'F', 'G', 'F', 'F', 'I', 'E', 'E', 'G', 'A', 'I', 'D', 'F', 'C', 'H', 'E', 'C', 'G', 'H', 'F', 'F', 'H', 'J', 'H', 'G', 'A', 'E', 'H', 'B', 'G', 'G', 'D', 'D', 'D', 'F', 'I', 'A', 'F', 'F', 'D', 'E', 'H', 'J', 'E', 'D', 'D', 'A', 'J', 'F', 'E', 'E', 'E', 'F', 'I', 'D', 'A', 'F', 'F', 'J', 'E', 'I', 'J', 'D', 'D', 'G', 'A', 'C', 'G', 'G', 'I', 'E', 'G', 'E', 'H', 'E', 'D', 'E', 'J', 'B', 'G', 'I', 'J', 'C', 'H', 'C', 'C', 'A', 'A', 'B', 'C', 'G', 'B', 'D', 'I', 'D', 'E', 'H', 'J', 'J', 'B', 'F', 'E', 'J', 'H', 'H', 'I', 'G', 'B', 'D' }; 



	cout << a.leastInterval(b5, 1) << endl; 
	cout << a2.leastInterval(b5, 1) << endl; 

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

