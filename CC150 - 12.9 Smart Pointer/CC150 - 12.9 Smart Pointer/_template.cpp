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


template<typename T> 
class Sm_ptr{
protected:
	T* resource; 
	int* counterPtr; 
public:
	Sm_ptr(T x) :resource(new T(x)), counterPtr(new int(1)) {}
	Sm_ptr(T* x) :resource(x), counterPtr(new int(1)) {}
	Sm_ptr(const Sm_ptr<T>& other) : resource(other.resource), counterPtr(other.counterPtr) { (*counterPtr)++; }
	Sm_ptr<T>& operator= (const Sm_ptr<T>& other) {
		if (this == &other)
			return *this; 
		if (*counterPtr > 0)
			destruct(); 

		resource = other.resource;
		counterPtr = other.counterPtr; 
		(*counterPtr)++;
		
		return *this; 
	}

	void destruct(){
		--(*counterPtr);
		if (*counterPtr == 0){
			delete resource; 
			resource = nullptr; 
			counterPtr = nullptr; 
		}
	}

	~Sm_ptr(){ destruct();  }

	T get() { return *T; }
	int count(){ return *counterPtr;  }
	int* pcount() { return counterPtr; }

};




int main()
{
	Sm_ptr<int> a(1);
	Sm_ptr<int> b (2);
	auto c = b.pcount();
	b = a;
	cout << *c; 


}

