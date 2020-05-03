#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <priority_queue>

//using namespace std;
//
//inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
//inline int log2(int N){return log10(N)/log10(2);}
//
//vector<int> twoSum(vector<int>& nums, int target)
//{
//    int index1 =0;
//    int index2 =0;
//
//    for(auto& i : nums)
//    {
//        if(i<=target)
//        {
//            for(auto& j : nums)
//            {
//                if(j== target - i)
//                {
//                    auto address = &nums.at(1);
//                    int ff = address - nums.begin();
//                }
//            }
//        }
//    }
//
//
//}
	struct comp
	{
		bool operator () (ListNode* a, ListNode* b){
			return a->val > b->val;
		}
	};

    ListNode* mergeKLists(vector<ListNode*>& lists) {
		if(lists.empty()) return nullptr;
		ListNode* dummy = new ListNode(0);

		priority_queue<ListNode*, vector<ListNode*>, comp> pq;

		for(int i=0; i<lists.size(); ++i)
			pq.push(lists[i]);

		ListNode* p=dummy;
		while(!pq.empty())
		{
			ListNode* tmp= pq.top();
			p->next = tmp;
			pq.pop();
			if(tmp->next)	pq.push(tmp->next);

			p=p->next;
		}
        return dummy->next;
    }

int main()
{
    vector<int> j = {1,2,3,4,5};
    twoSum(j, 3);

}
