// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string> 

using namespace std;


class Solution												
{
public:
	//************************************************************
	// #1: {1,2,3,4}, no repeating elem, find exact target or not
	// [l,r) range
	int bs11(vector<int>& vec, int target){
		int left = 0, right = vec.size(); 
		int mid; 
		while (left + 1 < right){
			mid = left + (right - left) / 2;
			if (vec[mid] <= target){
				left = mid; 
			}
			else
				right = mid; 
		}
		return vec[left] == target ? left : -1;
	}

	// [l,r) range , another while loop condition writing
	// Wrong condition! will go to ininite looping !!!!!! 
	int bs12(vector<int>& vec, int target){
		int left = 0, right = vec.size(); 
		int mid; 
		while (left < right){
			mid = left + (right - left) / 2;
			if (vec[mid] < target){
				left = mid+1; 
			}
			else
				right = mid+1; 
		}
		return vec[left] == target ? left : -1;
	}
	
	// [l,r] range
	int bs2(vector<int>& vec, int target){
		int left = 0, right = vec.size() - 1; 
		int mid;
		while (left < right){
			mid = left + ((right - left) >> 1);
			if (vec[mid] < target)
				left = mid + 1;
			else
				right = mid; 
		}
		return vec[left] == target ? left : -1; 
	}

	//************************************************************
	// ###2: {1,3,3,3,4,5,6} , there are repeating elem in array
	// find the left most target.  
	int bs31(vector<int>& vec, int target){
		int left = 0, right = vec.size()-1; // [left,right] is OK
		int mid; 
		while (left < right){
			mid = left + ((right - left) >> 1);
			if (vec[mid] < target)
				left = mid + 1;
			else
				right = mid - 1; // wrong line!
		}
		return vec[left]==target ? left : -1; // 这个写的不太对， 找不到单一元素！！
	}
	// 这么写才是对的： 
	int bs32(vector<int>& vec, int target){
		int left = 0, right = vec.size()-1; // [left,right] is OK
		int mid; 
		while (left < right){
			mid = left + ((right - left) >> 1);
			if (vec[mid] < target)
				left = mid + 1;
			else
				right = mid; 
		}
		return vec[left]==target ? left : -1; 
	}

	// (l,r] range. (left,right] range is also OK, left needs to start from -1. 
	int bs4(vector<int>& vec, int target){
		int left = -1, right = vec.size() - 1; // (left,right] is OK 
		int mid;
		while (left + 1 < right){
			mid = left + ((right - left) >> 1);
			if (vec[mid] < target)
				left = mid; 
			else
				right = mid; 
		}
		return vec[right] == target ? right : -1; 
	}

	//************************************************************
	// #3: {1,3,3,3,4,5,6} , there are repeating elem in array, find the most right elem
	// [l,r] range
	int bs5(vector<int>& vec, int target){
		int left = 0, right = vec.size(); 
		int mid; 
		while (left < right){
			mid = left + ((right - left) >> 1);	 
			if (vec[mid] < target)
				left = mid + 1;
			else
				right = mid ; 
		}
		return vec[left]==target ? left : -1; //  这么写不太对. 无法使用[l,r]区间
	}

	// 因为找最右边的match，left必须每次在 == 的时候 +1， 但是如果写成
	// if (vec[mid] <= target) left = mid + 1; 则这代表的是 (l, right],互相矛盾. 
	//
	// 用 （l，r)
	// 比较特别的是， 当 left=mid+1 并且 return vec[left-1] 的时候， left 就不会取到 -1 了
	// 这与一般的二分还是不太相同，可以多想想 
	int bs51(vector<int>& vec, int target){
		int left = 0, right = vec.size();
		int mid; 
		while (left < right){
			mid = left + ((right - left) >> 1);
			if (vec[mid] <= target)
				left = mid + 1;
			else
				right = mid; 
		}
		return vec[left - 1] == target ? left - 1 : -1;
	}
	

	// [l,r) range
	// 这个是最原生的， 最适合解这中情况的。 
	int bs6(vector<int>& vec, int target){
		int left = 0, right = vec.size(); 
		int mid; 
		while (left + 1 < right){
			mid = left + ((right - left) >> 1);
			if (vec[mid] <= target)
				left = mid;
			else
				right = mid; 
		}
		return vec[left] == target ? left : -1;
	}

};

int main()
{
	Solution a;
	vector<int> b = { 1, 3, 4, 6, 8, 9 }; 
	vector<int> c = { 1, 3, 3, 3, 3, 4, 6, 6, 6, 6, 8, 9 };
	//				{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11 }

	cout<<"bs1 : "<<a.bs11(b, 9)<<endl; 
	cout<<"bs2 : "<<a.bs2(b, 9)<<endl; 
	cout<<"bs3 : "<<a.bs32(c, 4)<<endl; 
	cout<<"bs4 : "<<a.bs4(c, 5)<<endl; 
	cout<<"bs5 : "<<a.bs5(c, 1)<<endl; 
	cout<<"bs6 : "<<a.bs6(c, 9)<<endl; 


}

