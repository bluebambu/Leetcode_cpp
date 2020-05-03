// CC150 - 7.3 Jukebox.cpp : Defines the entry point for the console application.
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
#include <random>
#include <ctime>
#include <unordered_set>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct mp3 {};

class song {
	mp3 _mp3; 
public:
	string name; 
	int length; 
	string author; 
	string album; 
	Artist artist; 

	song() {}
};

class Artist {}

class CD {
	vector<song> songs; 
public:
	CD() {}
	
	void Add(song s) { songs.push_back(s);  }
	
	string	name; 
	int		total; 
	Artist	artist; 

};

class Playlist {
	vector<song> list; 
public:
	Playlist() {}

	void addSong(song s) {}

	void addCD(CD cd) {}

	void shuffle() {}

	void repeatPlay() {}


};

class User {};
class CDPlayer {};
class SongSelector {};

class Jukebox {
protected:
	unordered_set<CD> collections; 
	
	User usr; 
	CDPlayer cdPlayer; 
	SongSelector ss; 
public:
	Jukebox() {}

	void AddSong() {}
	void AddCD() {}

	void PlaySong() {}
	void PlayCD() {}
	

};