// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


 struct UndirectedGraphNode {
     int label;
     vector<UndirectedGraphNode *> neighbors;
     UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (!node) return nullptr;
		unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> map;
		return bfs(node, map);
	}

	UndirectedGraphNode* bfs(UndirectedGraphNode* node, unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>& map){
		UndirectedGraphNode* root = new UndirectedGraphNode(*node); // ����ȫ��copy�� ����neighbors��size����ȷ�ģ���Ȼ��Ҫ�õ�push_back 
		map[node] = root;
		queue<UndirectedGraphNode*> q;
		q.push(node);

		while (q.size()){
			auto tmp = q.front();
			q.pop();
			vector<UndirectedGraphNode*>& v = tmp->neighbors;
			for (int i = 0; i<v.size(); ++i){ // neighbors Ҫ�����for loop��copy�� ��������ǰһ��һ��һ��copy�� ��surrounded regions��һ�������� 
				if (map.find(v[i]) != map.end()){
					(map[tmp]->neighbors)[i] = map[v[i]];
				}
				else{
					UndirectedGraphNode* newnode = new UndirectedGraphNode(*v[i]);// �����ȫ��copy�� ����neighbors��size����ȷ�ģ���Ȼ��Ҫ���ϵ�push_back 
					map[v[i]] = newnode;
					(map[tmp]->neighbors)[i] = newnode;
					q.push(v[i]);
				}
			}
		}
		return root;
	}
};


int main()
{
	Solution a;

	UndirectedGraphNode* b = new UndirectedGraphNode(5); 
	b->neighbors.push_back(b);
	b->neighbors.push_back(new UndirectedGraphNode(1)); 
	b->neighbors.push_back(new UndirectedGraphNode(2));
	b->neighbors.push_back(new UndirectedGraphNode(3));


	auto c=a.cloneGraph(b);

}

