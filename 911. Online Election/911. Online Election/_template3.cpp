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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 

class TopVotedCandidate {
public:
	unordered_map<int, int> rec; 
	map<int, int> history; 
	int highest, highest_person; 

    TopVotedCandidate(vector<int> persons, vector<int> times) {
		highest = 0; 
		for (int i = 0; i < persons.size(); ++i){
			rec[persons[i]] += 1; 
			if (rec[persons[i]] >= highest){
				highest = rec[persons[i]]; 
				highest_person = persons[i]; 
			}
			history[times[i]] = highest_person; 
		}
    }
    
    int q(int t) {
		return (prev(history.upper_bound(t)))->second; 
    }
};



class TopVotedCandidate2 {
public:
	unordered_map<int, int> rec; 
	vector<int> history_time, history_champ; 
	int highest, highest_person; 

    TopVotedCandidate(vector<int> persons, vector<int> times) {
		highest = 0; 
		for (int i = 0; i < persons.size(); ++i){
			rec[persons[i]] += 1; 
			if (rec[persons[i]] >= highest){
				highest = rec[persons[i]]; 
				highest_person = persons[i]; 
			}
			history_time.push_back(times[i]); 
			history_champ.push_back(highest_person); 
		}
    }
    
    int q(int t) {
		int idx = prev(upper_bound(history_time.begin(), history_time.end(), t)) - history_time.begin(); 
		return history_champ[idx]; 
    }
};


class TopVotedCandidate3 {
public:
	unordered_map<int, int> person_vote_map;
	map<int, int> time_person_map;
	TopVotedCandidate3(vector<int> persons, vector<int> times) {
		int n = persons.size(); 
		int maxVote = 0, maxPerson = 0; 

		for (int i = 0; i < n; ++i){
			person_vote_map[persons[i]] += 1; 
			if (person_vote_map[persons[i]] >= maxVote){
				maxVote = person_vote_map[persons[i]]; 
				maxPerson = persons[i]; 
			}
			time_person_map[times[i]] = maxPerson; 
		}
	}

	int q(int t){
		return (prev(upper_bound(time_person_map.begin(), time_person_map.end(), t)))->second; 
	}
};



int main(){

	vector<int> b = { 0, 1, 1, 0, 0, 1, 0 },
		c = { 0, 5, 10, 15, 20, 25, 30 }; 

	TopVotedCandidate a(b, c); 

	cout << a.q(3) << endl; 
	cout << a.q(12) << endl; 
	cout << a.q(25) << endl; 
	cout << a.q(15) << endl; 
	cout << a.q(24) << endl; 
	cout << a.q(8) << endl; 
	


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

