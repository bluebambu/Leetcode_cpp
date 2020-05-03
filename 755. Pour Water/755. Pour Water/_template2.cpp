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
//  We are given an elevation map, heights[i] representing the height of the terrain at that index. The width at each index is 1. After V units of water fall at index K, how much water is at each index?

// Water first drops at index K and rests on top of the highest terrain or water at that index. Then, it flows according to the following rules:
// If the droplet would eventually fall by moving left, then move left.
// Otherwise, if the droplet would eventually fall by moving right, then move right.
// Otherwise, rise at it's current position.
// Here, "eventually fall" means that the droplet will eventually be at a lower level if it moves in that direction. Also, "level" means the height of the terrain plus any water in that column.

// We can assume there's infinitely high terrain on the two sides out of bounds of the array. Also, there could not be partial water being spread out evenly on more than 1 grid block - each unit of water has to be in exactly one block.

// Example 1:

// Input: heights = [2,1,1,2,1,2,2], V = 4, K = 3
// Output: [2,2,2,3,2,2,2]
// Explanation:
// #       #
// #       #
// ##  # ###
// #########
//  0123456    <- index

// The first drop of water lands at index K = 3:

// #       #
// #   w   #
// ##  # ###
// #########
//  0123456    

// When moving left or right, the water can only move to the same level or a lower level.
// (By level, we mean the total height of the terrain plus any water in that column.)
// Since moving left will eventually make it fall, it moves left.
// (A droplet "made to fall" means go to a lower height than it was at previously.)

// #       #
// #       #
// ## w# ###
// #########
//  0123456    

// Since moving left will not make it fall, it stays in place.  The next droplet falls:

// #       #
// #   w   #
// ## w# ###
// #########
//  0123456  

// Since the new droplet moving left will eventually make it fall, it moves left.
// Notice that the droplet still preferred to move left,
// even though it could move right (and moving right makes it fall quicker.)

// #       #
// #  w    #
// ## w# ###
// #########
//  0123456  

// #       #
// #       #
// ##ww# ###
// #########
//  0123456  

// After those steps, the third droplet falls.
// Since moving left would not eventually make it fall, it tries to move right.
// Since moving right would eventually make it fall, it moves right.

// #       #
// #   w   #
// ##ww# ###
// #########
//  0123456  

// #       #
// #       #
// ##ww#w###
// #########
//  0123456  

// Finally, the fourth droplet falls.
// Since moving left would not eventually make it fall, it tries to move right.
// Since moving right would not eventually make it fall, it stays in place:

// #       #
// #   w   #
// ##ww#w###
// #########
//  0123456  

// The final answer is [2,2,2,3,2,2,2]:

//     #    
//  ####### 
//  ####### 
//  0123456 

// Example 2:

// Input: heights = [1,2,3,4], V = 2, K = 2
// Output: [2,3,3,4]
// Explanation:
// The last droplet settles at index 1, since moving further left would not cause it to eventually fall to a lower height.

// Example 3:

// Input: heights = [3,1,3], V = 5, K = 1
// Output: [4,4,4]

// Note:

//     heights will have length in [1, 100] and contain integers in [0, 99].
//     V will be in range [0, 2000].
//     K will be in range [0, heights.length - 1].



// pass, but a bit verbose. speed is fine.
class Solution {
public:
	vector<int> pourWater(vector<int>& heights, int V, int K) {
		int left = K, right = K, n=heights.size(); 

		while (V>0){
			// prior to find first left pointer boundary
			while (left > 0 && (heights[left - 1] == heights[left])) --left; 

			// if find a cave, dig into it
			if (left>0 && (heights[left - 1] < heights[left])){
				left = right = left - 1; 
				continue;
			} 

			// then find right pointer boundary
			while (right < n - 1 && (heights[right + 1] == heights[right])) ++right; 

			// dig into right cave if there is no left side cave
			if (right<n-1 && (heights[right+1] < heights[right])){
				left = right = right + 1; 
				continue;
			} 
			
			// theoretical flat land volume
			int toFill = right - left + 1; 
			//                         #
			// ########  becomes   #########, land is split
			if (K >= left && K <= right){
				heights[K] += 1;
				V -= 1;
				left = right = K; // this case, left and right are at the new tip. 
				continue;
			}
				
			// can not fill the whole flat land
			if (V < toFill){
				if (K >= right){
					for (int i = right; V > 0; --i, --V)
						heights[i] += 1;
				}
				else if(K <= left){
					for (int i = left; V > 0; ++i, --V)
						heights[i] += 1;
				}
			}
			else{
			// else directly delete the flat land volume
				for (int i = right; i >= left; --i){
					heights[i] += 1; 
					--V; 
				}
			}
		}

		return heights; 
	}
};




int main(){
	Solution a; 

	vector<int> b = { 3, 1, 3 }; 
	vector<int> c = { 2, 1, 1, 2, 1, 2, 2 }; 
	vector<int> d = { 2, 2, 3, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1 };

	prt1Layer(a.pourWater(d, 10, 11)); 


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

