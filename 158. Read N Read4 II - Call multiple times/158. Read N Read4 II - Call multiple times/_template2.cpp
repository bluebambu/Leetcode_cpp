// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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


struct TreeNode {
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


// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
	/**
	* @param buf Destination buffer
	* @param n   Maximum number of characters to read
	* @return    The number of characters read
	*/
	int last; 
	int redu; 
	Solution() :last(0),redu(0) {}
	int read(char *buf, int n) {
		if (n < redu){
			redu -= n; 
			return n; 
		}
		buf += last; 
		n -= redu; 
		int cnt = 0; 
		while (1){
			int r = read4(buf); 
			cnt += r; 
			if (r < 4 || n < 4){
				buf += min(r, n); 
				int end = cnt - r + min(r, n); 
				last += end; 
				redu = r > n ? r - n : 0; 
				return end; 
			}
			buf += r; 
			n -= r; 
		}
		return -1; 
	}
};



class Solution {
public:
	deque<char> b;

	int read(char *buf, int n) {
		if (n <= b.size()){
			for (int i = 0; i < n; ++i){
				buf[i] = b.front();
				b.pop_front();
			}
			return n;
		}

		int remain = b.size();
		while (!b.empty()){
			*buf = b.front();
			b.pop_front();
			++buf;
		}
		n -= remain;
		cout << "27 " << n << endl;

		int cnt = remain;
		while (1){
			int r = read4(buf);
			//cout<<r<<endl; 
			if (r < 4 || n < 4){
				int diff = r > n ? r - n : 0;
				for (int i = 0; i < diff; ++i){
					b.push_back(*(buf + n + i));
					//cout<<i<<endl; 
				}
				for (auto i : b)
					cout << i << " ";
				cout << endl;

				return cnt + min(r, n);
			}
			cnt += r;
			buf += r;
			n -= r;
		}
	}
};


// passed
class Solution2 {
public:
	queue<char> remains; 
	int read(char *buf, int n) {
		int cnt = 0; 
		if (!remains.empty()){
			while (n > 0 && !remains.empty()){
				*buf = remains.front(); 
				remains.pop(); 
				buf += 1; 
				cnt += 1; 
				n -= 1; 
			}
		}

		if (n == 0)
			return cnt; 

		int cur; 
		while (n > 0){
			cur = read4(buf); 
			if (n < cur){
				for (int i = 0; i < cur - n; ++i){
					remains.push(buf[n + i]); 
				}
			}
			if (cur < 4 || n < 4)
				break;
			n -= 4; 
			buf += 4; 
			cnt += 4; 
		}

		return cnt + min(cur, n); 
	}
};

class Solution3 {
public:
	vector<char> bbuf; 
	int bufEnd, bufStart; 

	Solution3() :bbuf(4, 0), bufEnd(0), bufStart(0) {}

	int read(char *buf, int n) {
		int res = 0; 
		if (bufStart < bufEnd){
			while (n > 0 && bufStart < bufEnd){
				*buf = bbuf[bufStart++]; 
				buf += 1; 
				++res; 
				--n; 
			}
		}

		if (bufStart >= bufEnd){
			bufStart = 0, bufEnd = 0; 
		}

		while (n > 0){
			bufEnd = read4(bbuf.data()); 
			if (bufEnd == 0)// a must have statement! 
				break;

			bufStart = 0; 
			if (bufEnd > n){
				while (n > 0){
					*buf = bbuf[bufStart++]; 
					--n; 
					buf += 1; 
					++res; 
				}
				return res; 
			}

			while (bufStart < bufEnd){
				*buf = bbuf[bufStart++]; 
				++res; 
				buf += 1; 
				--n; 
			}
		}

		return res; 
	}
}; 

class Solution4 {
public:
	int writePos, readPos; 
	int data[4]; 
	Solution4() :writePos(0), readPos(0){}

	int read(char *buf, int n) {
		int cnt = 0;
		if (readPos != writePos){
			while (n>0 && readPos < writePos){
				buf[cnt] = data[readPos]; 
				++cnt, --n, ++readPos; 
			}
		}
		if (n == 0)
			return cnt; 

		while (true){
			if (readPos == 4)
				readPos = 0; 

			writePos = read4(data); 
			for (; n > 0 && readPos < writePos; ++readPos){
				buf[cnt++] = data[readPos]; 
				--n; 
			}

			if (n == 0)
				return cnt; 
			if (writePos == 0)
				return cnt; 
		}

		return -1; 
	}
};

class Solution5 {
public:
	int writePos, readPos;
	int data[4];
	Solution5() :writePos(0), readPos(0){}

	int read(char *buf, int n) {
		for (int i = 0; i < n; ++i){
			if (readPos == writePos){
				writePos = read4(data); 
				readPos = 0; 
				if (writePos == 0)
					return i; 
			}
			buf[i] = data[readPos++]; 
		}
		return n; 
	}
}; 


class Solution6 {
public:
	int writePos, readPos;
	int data[4];
	Solution5() :writePos(0), readPos(0){}

	int read(char *buf, int n) {
		for (int i = 0; i < n; ++i){
			if (readPos == writePos){
				writePos = read4(data); 
				if (writePos == 0) return i; 
				readPos = 0; 
			}
			buf[i] = data[readPos++]; 
		}
		return n; 
	}
}; 


int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

