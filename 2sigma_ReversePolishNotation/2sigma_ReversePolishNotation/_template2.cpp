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

class Token{
public:
	virtual void process(stack<Token*>&) = 0; 
};

class Operand :public Token{
	int _val; 
public:
	Operand() :_val(0) {}
	Operand(int x) :_val(x) {}

	void setVal(int x){ _val = x; }
	int getVal(){ return _val;  }

	void process(stack<Token*>& stk){
		stk.push(this); 
	}
};

class Operator :public Token{
protected:
	string _val; 
public:
	
};

class Plus : public Operator{
public:
	Plus() :Operator(){
		_val = "+"; 
	}

	void process(stack<Token*>& stk){
		int a = dynamic_cast<Operand*>(stk.top())->getVal(); 
		stk.pop(); 
		int b = dynamic_cast<Operand*>(stk.top())->getVal(); 
		stk.pop(); 
		Operand* c = new Operand(a + b); 
		stk.push(c); 
	}
};

//// Creators
class Creator{
public:
	virtual Token* create(const string& ) = 0; 
};

class Oprd_Creator :public Creator{
public:
	Token* create(const string& val){
		return new Operand(stoi(val)); 
	}
};

template<typename T>
class Optr_Creator : public Creator{
public:
	Token* create(const string& val){
		return new T; 
	}
};

class Factory{
	unordered_map<string, Creator*> m; 
public:
	bool isNum(string num){
		return num.size() && num[0] >= '0' && num[0] <= '9'; 
	}

	void reg(string name, Creator* ctor){
			m[name] = ctor; 
	}

	void regNum(string num){
		m[num] = new Oprd_Creator; 
	}

	Creator* genCtor(string val){
		if (m.count(val) == 0){
			if (isNum(val)){
				regNum(val);
			}
			else
				return nullptr; 
		}
		return m[val]; 
	}
};

int main(){
	Factory f; 
	Optr_Creator<Plus> plus_ctor; 
	f.reg("+", &plus_ctor); 

	vector<string> rpn = { "1", "2", "+" }; 
	stack<Token*> stk; 

	for (string& s : rpn){
		f.genCtor(s)->create(s)->process(stk); 
	}

	cout << dynamic_cast<Operand*>(stk.top())->getVal(); 
}
