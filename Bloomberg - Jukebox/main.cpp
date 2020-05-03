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

class MP3{
public:
    int length;
};

class Song{
public:
    Song(MP3 x, string y):audio(x), name(y), length(x.length) {}
    MP3 audio;
    string name;
    int length;
};

class CD{
public:
    vector<Song> songs;
    string name;
    vector<string> metadata_of_song;
    int totalNum;
};

class Playlist{
public:
    queue<Song> queue;

    Song getNextSong(){
        Song tmp = queue.top();
        queue.pop();
        return tmp;
    }

};

class CDPlayer{
private:
    CD c;
    Playlist p;
public:
    // ctor
    CDPlayer(CD c, Playlist p) {}

    //play song
    void playsong(Song s) {}

    // getters
    Playlist getPlaylist() {return p;}
};

class User{
public:
    string name;

};


class SongSelector {
    CD* cdptr;

public:
    Song getCurrentSong() {}; // ...
};

class JukeBox{
private:
    CDPlayer cdplayer;
    User usr;
    vector<CD> CDcollection;

public:
    JukeBox(CDPlayer x, User usr) { }

};




int main()
{


}
