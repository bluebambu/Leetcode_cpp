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

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}



struct UndirectedGraphNode {
     int label;
     vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution2 { /// lc passed, dfs
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return nullptr;
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> map;

        return dfs(node, map);
    }

    UndirectedGraphNode* dfs(UndirectedGraphNode* node, unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>& map){
        if(map.find(node)!=map.end())
            return map[node];

        UndirectedGraphNode* newnode = new UndirectedGraphNode(node->label);
        map[node]=newnode;
        for(int i=0; i<node->neighbors.size(); ++i){
            newnode->neighbors.push_back(dfs(node->neighbors[i], map));
        }
        return newnode;
    }
};


class Solution3 { /// lc pass, with global hashmap
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> map;
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return nullptr;
        if(map.find(node)!=map.end())
            return map[node];

        UndirectedGraphNode* newnode = new UndirectedGraphNode(node->label);
        map[node] = newnode;
        for(int i=0; i<node->neighbors.size(); ++i)
            newnode->neighbors.push_back(cloneGraph(node->neighbors[i]));

        return newnode;
    }
};



class Solution {
public:
    //////// Leetcode passed, BFS //////////
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return nullptr;
        UndirectedGraphNode *head = new UndirectedGraphNode(node->label);
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> helper;

        queue<UndirectedGraphNode*> q;
        q.push(node);
        helper[node]=head;

        while(q.size()){
            UndirectedGraphNode* tmp=q.front();
            q.pop();

            for(int i=0; i<tmp->neighbors.size() ; ++i){
                UndirectedGraphNode* nb = (tmp->neighbors)[i];

                if(helper.find(nb)==helper.end()){
                    UndirectedGraphNode *newnb = new UndirectedGraphNode(nb->label);
                    helper[nb]=newnb;
                    q.push(nb);
                }
                (helper[tmp]->neighbors).push_back(helper[nb]);
            }
        }
        return head;
    }

    ////////// Leetcode passed, stack DFS   ////////////////////
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return nullptr;
        UndirectedGraphNode * head = new UndirectedGraphNode (node->label);
        unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> helper;
        helper[node]=head;

        vector<UndirectedGraphNode *> stack;
        stack.push_back(node);

        while(stack.size()){
            UndirectedGraphNode * tmp=stack.back();
            stack.pop_back();

            for(auto i : tmp->neighbors){
                if(helper.find(i)==helper.end()){
                    UndirectedGraphNode * newnb = new UndirectedGraphNode (i->label);
                    helper[i]=newnb;
                    stack.push_back(i);
                }
                helper[tmp]->neighbors.push_back(helper[i]);
            }
        }
        return head;
    }
};

// lc passed, BFS, not that good
class Solution4 {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (!node) return nullptr;
		unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> map;
		return bfs(node, map);
	}

	UndirectedGraphNode* bfs(UndirectedGraphNode* node, unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>& map){
		UndirectedGraphNode* root = new UndirectedGraphNode(*node); // 可以全部copy， 这样neighbors的size是正确的，不然需要用到push_back
		map[node] = root;
		queue<UndirectedGraphNode*> q;
		q.push(node);

		while (q.size()){
			auto tmp = q.front();
			q.pop();
			vector<UndirectedGraphNode*>& v = tmp->neighbors;
			for (int i = 0; i<v.size(); ++i){ // neighbors 要在这个for loop中copy， 而不是在前一步一个一个copy。 和surrounded regions是一个道理！！
				if (map.find(v[i]) != map.end()){
					(map[tmp]->neighbors)[i] = map[v[i]];
				}
				else{
					UndirectedGraphNode* newnode = new UndirectedGraphNode(*v[i]);// 最好是全部copy， 这样neighbors的size是正确的，不然需要不断地push_back
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

