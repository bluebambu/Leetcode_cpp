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
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// 1+2*(..)   1*2/3*4/5/6*8*9   1*2+3/4*5-6*8/7

// 7
// 8	/
// 6	*
// 5	-
// 4	*
// 3	/
// 2	+
// 1	*


// perfect answer!!! Pass all the tests
// only drawback is that can not process negative number

// key point: 1. 2 stacks, one for number, one for operators
//			  2. operators have different priority. '+' pops '-', '-' pops '*', '*' pops '/'
//			  3. '(' will be pushed into the op stack, and when meet ')', pop everything until '(' 
//			  4. during '(...)' poping, still process rule 2. 
//			  5. if op priority are same, also need to pop the stack. 
class calculator{
private:

	void onestep(stack<double>& values, stack<char>& operators){
		double first = values.top();
		values.pop();
		double second = values.top();
		values.pop();
		char op = operators.top();
		operators.pop();

		double result;
		switch (op){
		case '+': result = first + second; break;
		case '-': result = second - first; break;
		case '*': result = first*second; break;
		case '/': result = second / first; break;
		}
		values.push(result);
	}

	double priority(char a){
		switch (a){
		case '+': return 0; 
		case '-': return 1;
		case '*': return 2;
		case '/': return 3;
		}
		return -1; /// I put '(' into operators stack, and assign its priority as -1.
	}

	bool isNum(char c){
		return c >= '0' && c <= '9'; 
	}
	bool isOp(char c){
		return c == '+' || c == '-' || c == '*' || c == '/'; 
	}


public:
	double processBracket(string expr){
		stack<double> vst; 
		stack<char> opst; 
	
		for (int i = 0; i < expr.size(); ++i){
			if (isNum(expr[i])){
				double j = i + 1; 
				while (isNum(expr[j])) ++j; 
				double cur = stoi(expr.substr(i, j - i));
				vst.push(cur); 
				i = j - 1; 
				continue;
			}

			if (isOp(expr[i])){
				double prio = priority(expr[i]); 
				if (opst.empty() || opst.top() == '(' || prio > priority(opst.top()))
					opst.push(expr[i]); 
				else{
					while (!opst.empty() && opst.top() != '(' && prio <= priority(opst.top())){
						onestep(vst, opst); 
					}
					opst.push(expr[i]); 
				}
				continue;
			}

			if (expr[i] == '('){
				opst.push('('); 
				continue;
			}
			
			if (expr[i] == ')'){
				while (!opst.empty() && opst.top() != '('){
					onestep(vst, opst); 
				}
				opst.pop(); 
				continue;
			}
		}

		while (opst.size())
			onestep(vst, opst); 

		return vst.top(); 
	}
};

/***  tips
如果该数字之前的符号是加或减，那么把当前数字压入栈中，注意如果是减号，则加入当前数字的相反数，因为减法相当于加上一个相反数。
*/


int main(){
	calculator a; 

	cout << a.processBracket("1+(23+(6-4)/2)-2") <<endl; //23
	cout << a.processBracket("1+(2*(6-4*2) - 2)-2")<<endl; // 1 

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

