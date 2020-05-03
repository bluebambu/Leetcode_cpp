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

class Solution4 {
public:
	// bfs
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> wordList) {
		queue<string> q; 
		q.push(beginWord); 
		unordered_set<string> d(wordList.begin(), wordList.end()); 
		unordered_map<string, unordered_set<string>> path; 
		bool success = false; 
		if (d.count(endWord) == 0) return{};
		
		while (!q.empty()){
			int sz = q.size(); 
			unordered_set<string> v_cur_rnd;
			for (int i = 0; i < sz; ++i){
				string f = q.front(); 
				q.pop(); 

				for (int i = 0; d.size() && i < f.size(); ++i){
					char c = f[i]; 
					string copy = f; 
					for (char r = 'a'; r <= 'z'; ++r){
						copy[i] = r; 
						if (d.count(copy)){
							path[f].insert(copy); 
							v_cur_rnd.insert(copy); 
							q.push(copy); 
						}
						if (copy == endWord){
							path[f].insert(copy); 
							success = true; 
						}
					}
				}
			}

			prt1Layer(v_cur_rnd); 

			for (auto& w : v_cur_rnd){
				d.erase(w); 
			}
			if (success)
				break; 
		}

		vector<vector<string>> res; 
		vector<string> p; 
		p.push_back(beginWord); 
		dfs(beginWord, endWord, path, p, res); 

		return res; 
    }

	void dfs(const string& b, const string& e, unordered_map<string, unordered_set<string>>& m, vector<string>& p, vector<vector<string>>& res){
		if (b == e) {
			res.push_back(p); 
			return; 
		}

		for (const string& nxt : m[b]){
			p.push_back(nxt); 
			dfs(nxt, e, m, p, res); 
			p.pop_back(); 
		}
	}
};

// pass, 99.5% 
class Solution5 {
public:
	// bfs
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> wordList) {
		unordered_set<string> front, tail, d(wordList.begin(), wordList.end()); 
		if (d.count(endWord) == 0) return{}; 

		front.insert(beginWord); d.erase(beginWord); 
		tail.insert(endWord); d.erase(endWord); 
		bool success = false; 
		bool isFront = true; 
		unordered_map<string, unordered_set<string>> path; 

		while (front.size()){
			if (front.size() > tail.size()){
				isFront = !isFront; 
				swap(front, tail); 
			}

			unordered_set<string> nxt_queue; 
			for (auto& s : front){
				for (int i = 0; i < s.size(); ++i){
					string copy = s; 
					char c = s[i]; 
					for (char r = 'a'; r <= 'z'; ++r){
						if (r == c) continue;;
						copy[i] = r; 
						if (d.count(copy)){
							nxt_queue.insert(copy); 
							isFront ? path[s].insert(copy) : path[copy].insert(s); 
						}
						if (tail.count(copy)){
							isFront ? path[s].insert(copy) : path[copy].insert(s); 
							success = true;
						}
					}
				}
			}

			for (auto& w : nxt_queue){
				d.erase(d.find(w)); 
			}

			front = nxt_queue; 

			if (success)
				break; 
		}

		vector<vector<string>> res; 
		vector<string> p; 
		p.push_back(beginWord); 
		dfs(beginWord, endWord, path, p, res); 

		return res; 
    }

	void dfs(const string& b, const string& e, unordered_map<string, unordered_set<string>>& m, vector<string>& p, vector<vector<string>>& res){
		if (b == e) {
			res.push_back(p); 
			return; 
		}

		for (const string& nxt : m[b]){
			p.push_back(nxt); 
			dfs(nxt, e, m, p, res); 
			p.pop_back(); 
		}
	}
};



/////////////// Leetcode passed, from other people, a better solution with DFS output ////////////////
class Solution{
	bool buildNexts(string start, string end, unordered_set<string> &dict, map<string, vector<string>> &nexts) {
		unordered_set<string> head{ start }, tail{ end };
		int len = start.size();
		bool headIsFront = true, found = false;

		while (!head.empty() && !tail.empty()) {
			if (head.size() > tail.size()) {
				swap(head, tail);
				headIsFront = !headIsFront;
			}
			unordered_set<string> tmp;
			for (auto word : head) {
				dict.erase(word);
				string headWord = word;
				for (int i = 0; i < len; ++i) {
					char letter = word[i];
					for (int j = 'a'; j <= 'z'; ++j) {
						word[i] = j;
						if (tail.find(word) != tail.end()) {
							headIsFront ? nexts[headWord].push_back(word) : nexts[word].push_back(headWord);
							found = true;
						}
						else if (!found && dict.find(word) != dict.end()) {
							headIsFront ? nexts[headWord].push_back(word) : nexts[word].push_back(headWord);
							tmp.insert(word);
						}
					}
					word[i] = letter;
				}
			}
			if (found) return true;
			for (auto word : tmp) /// it's important to delete words here, but no other places!
				dict.erase(word);
			head = tmp;
		}
		return false;
	}

	void buildAns(string start, string end, map<string, vector<string>> &nexts, vector<string> &path, vector<vector<string>> &ans) {
		if (start == end) {
			ans.push_back(path);
			return;
		}
		for (auto s : nexts[start]) {
			path.push_back(s);
			buildAns(s, end, nexts, path, ans);
			path.pop_back();
		}
	}

	vector<vector<string>> findLadders3(string start, string end, unordered_set<string> &dict) {
		vector<vector<string>> ans;
		vector<string> path(1, start);;
		map<string, vector<string>> nexts;
		if (buildNexts(start, end, dict, nexts))
			buildAns(start, end, nexts, path, ans);
		return ans;
	}

};

class Solution2{
	//////////////////////// leetcode passed, self practice , 92ms /////////////////
	vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
		vector<vector<string>> result;
		vector<string> path(1, beginWord);
		unordered_map<string, vector<string>> fwmap;
		if (buildmap(beginWord, endWord, wordList, fwmap))
			buildAns(beginWord, endWord, fwmap, path, result);
		return result;
	}

	bool buildmap(string beginWord, string endWord, unordered_set<string> &wordList, unordered_map<string, vector<string>>& fwmap){

		unordered_set<string> head{ beginWord }, tail{ endWord };
		wordList.erase(beginWord); wordList.erase(endWord);
		bool finished = false, headfront = true;

		while (!head.empty() && !tail.empty() && !finished){
			if (head.size() > tail.size()){
				swap(head, tail);
				headfront = !headfront;
			}

			unordered_set<string> tmp_set;

			for (auto iter = head.begin(); iter != head.end(); ++iter){
				string cur_str = *iter;

				for (int i = 0; i < cur_str.size(); ++i){
					string tmp_str = cur_str;
					for (char j = 'a'; j <= 'z'; ++j){
						tmp_str[i] = j;

						if (tail.find(tmp_str) != tail.end()){
							finished = true;
							headfront ? fwmap[cur_str].push_back(tmp_str) : fwmap[tmp_str].push_back(cur_str);
						}
						else if (!finished && wordList.find(tmp_str) != wordList.end()){
							headfront ? fwmap[cur_str].push_back(tmp_str) : fwmap[tmp_str].push_back(cur_str);
							tmp_set.insert(tmp_str);
						}
					}
				}
			}

			if (finished) 
				return true;

			for (auto word : tmp_set)
				wordList.erase(word);
			head = tmp_set;
		}

		return false;
	}

	void buildAns(string beginWord, string endWord, unordered_map<string, vector<string>>& fwmap, vector<string>& path, vector<vector<string>>& result){
		if (beginWord == endWord){
			result.push_back(path);
			return;
		}

		for (auto word : fwmap[beginWord]){
			path.push_back(word);
			buildAns(word, endWord, fwmap, path, result);
			path.pop_back();
		}
	}
};

class Solution3{
	vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
			
	}
};


int main() {
	Solution5 a;

	a.findLadders("a", "c", {"a","b","c"}); 

	string s1 = "hit", s2 = "cog"; 
	vector<string> d = { "hot", "cig", "lot", "cot", "cit", "log" }; 

	auto cc = a.findLadders(s1, s2, d); 
	prt2Layer(cc); 

	string beginWord = "zings";
	string endWord = "brown";

	vector<string> wordList = { "chump", "sours", "mcgee", "piers", "match", "folds", "rinse", "films", "small", "umbel", "assad", "morin", "plied", "basin", "moots", "blurb", "suits", "solve", "sooty", "fluky", "bombs", "nurse", "ceres", "lopes", "yucky", "ricks", "goads", "loses", "coyly", "marcy", "bonds", "niece", "cures", "sonic", "crows", "dicey", "gaped", "buggy", "riles", "homer", "fakir", "hello", "riper", "makes", "laked", "sinus", "fangs", "acton", "spiky", "salts", "boots", "skiff", "maker", "pence", "fells", "cedar", "kited", "raved", "flake", "jiffy", "tanks", "barns", "sized", "gluts", "amman", "jumps", "cavil", "quaff", "rents", "looms", "toner", "gibes", "aside", "drawn", "karin", "torte", "haded", "psych", "hacks", "jesus", "fumed", "lisle", "spays", "sumps", "beats", "tunas", "naked", "bathe", "gulfs", "karma", "snuff", "boast", "grins", "turds", "plant", "spicy", "risen", "tints", "tomas", "stand", "noses", "toxin", "sheep", "paddy", "abase", "jeeps", "dated", "tough", "timid", "forty", "kusch", "pones", "smack", "token", "havel", "vanes", "repay", "chums", "paved", "chimp", "spinx", "smirk", "pupas", "bares", "mites", "egged", "palsy", "gyros", "wolfe", "chips", "pouts", "johns", "barbs", "slunk", "hires", "seals", "rally", "tromp", "roads", "writs", "aches", "corny", "fiats", "hench", "gilts", "blake", "phony", "drams", "skimp", "suing", "horus", "hewer", "barfs", "hewed", "needs", "epsom", "knots", "tided", "befit", "eager", "melva", "coves", "plush", "pawed", "zebra", "gales", "blots", "foggy", "rooks", "comas", "laxly", "cries", "kirks", "monks", "magic", "fugue", "apter", "limos", "congo", "rosin", "seder", "bones", "holes", "fated", "gamay", "snags", "wimpy", "rites", "gilds", "slink", "staph", "sioux", "bends", "wilma", "warts", "reeds", "yolks", "lover", "demon", "salve", "hulas", "shard", "worst", "leach", "omits", "flint", "tines", "julio", "trots", "silly", "cocks", "gleam", "react", "camps", "nicks", "bored", "coded", "swine", "scope", "aloes", "south", "hands", "rainy", "david", "newer", "ferns", "jelly", "index", "gibbs", "truly", "tubes", "opera", "raven", "noyce", "whims", "titus", "hared", "vined", "dealt", "slats", "erick", "rolls", "breed", "udder", "oozed", "prays", "tsars", "harry", "shelf", "norms", "larks", "hazes", "brice", "gifts", "units", "veeps", "dumas", "mommy", "spock", "dotty", "molls", "slobs", "diane", "buddy", "boost", "ginny", "rends", "marks", "timur", "bands", "genes", "slews", "leeds", "karyn", "mobil", "mixes", "ronny", "sadly", "rinks", "smash", "baled", "pulpy", "toils", "yards", "piing", "dried", "veils", "spook", "snaky", "sizer", "spout", "percy", "sheol", "blank", "waxes", "herod", "attar", "doped", "polls", "banes", "penny", "knelt", "laded", "manic", "acids", "squat", "jerry", "stony", "woofs", "idles", "bruin", "carla", "sheik", "hodge", "goody", "merge", "nicer", "scums", "evens", "lames", "wends", "midge", "jives", "tuner", "reins", "boars", "fryer", "realm", "dyson", "narks", "torts", "yawed", "waked", "cress", "curvy", "bongs", "fared", "jilts", "liens", "ducat", "shaft", "pesos", "dulls", "donna", "potty", "winks", "marsh", "giddy", "tiffs", "scoot", "nifty", "daisy", "slots", "stacy", "colby", "skims", "malls", "sifts", "jinns", "flank", "molar", "hatch", "wiped", "taped", "clink", "brims", "credo", "fezes", "molds", "finds", "quids", "terra", "damns", "dusky", "wanes", "musty", "barer", "snare", "honey", "piked", "wiser", "elvin", "dolly", "fetal", "ships", "reign", "cause", "caved", "mecca", "blink", "close", "birth", "pints", "reefs", "amado", "comae", "waite", "willy", "lorry", "nixed", "quire", "napes", "voted", "eldon", "nappy", "myles", "laser", "pesky", "leant", "septa", "mucks", "agree", "sworn", "lofty", "slush", "holst", "tevet", "wases", "cheer", "torah", "treks", "purge", "class", "popes", "roans", "curve", "quads", "magma", "drier", "hales", "chess", "prigs", "sivan", "romes", "finch", "peels", "mousy", "atria", "offer", "coals", "crash", "tauts", "oinks", "dazed", "flaps", "truck", "treed", "colas", "petty", "marty", "cadet", "clips", "zones", "wooed", "haves", "grays", "gongs", "minis", "macaw", "horde", "witch", "flows", "heady", "fuels", "conks", "lifts", "tumid", "husks", "irony", "pines", "glops", "fonds", "covey", "chino", "riggs", "tonya", "slavs", "caddy", "poled", "blent", "mired", "whose", "scows", "forte", "hikes", "riped", "knobs", "wroth", "bagel", "basks", "nines", "scams", "males", "holed", "solid", "farms", "glaxo", "poise", "drays", "ryder", "slash", "rajas", "goons", "bowed", "shirt", "blurs", "fussy", "rills", "loren", "helps", "feels", "fiefs", "hines", "balms", "blobs", "fiord", "light", "dinky", "maids", "sagas", "joked", "pyxed", "lilly", "leers", "galls", "malts", "minos", "ionic", "lower", "peale", "ratty", "tuber", "newed", "whirl", "eases", "wests", "herds", "clods", "floes", "skate", "weeds", "tones", "rangy", "kings", "adder", "pitts", "smith", "coats", "lenny", "sorta", "floss", "looks", "angie", "peppy", "upper", "darin", "white", "lofts", "clint", "jared", "heros", "ruler", "tonia", "sexed", "grail", "villa", "topic", "kenny", "dopes", "hoots", "boobs", "gerry", "eries", "lyres", "lunch", "glove", "cumin", "harms", "races", "today", "crust", "track", "mends", "snout", "shark", "iliad", "shrew", "dorky", "monty", "dodge", "toted", "worse", "dream", "weird", "gaunt", "damon", "rimes", "layer", "salem", "bards", "dills", "hobby", "gives", "shall", "crazy", "brace", "faxed", "pools", "foamy", "viral", "strop", "liver", "ceded", "jolts", "jonah", "tight", "lilia", "hussy", "mutts", "crate", "girls", "marge", "hypos", "mewls", "bulls", "gazes", "wands", "avior", "sonya", "slick", "clump", "cater", "aural", "agave", "grief", "shana", "fices", "moans", "grape", "fetid", "jenna", "humus", "poesy", "cooks", "still", "lease", "wanda", "oddly", "areas", "frats", "imply", "files", "ramon", "seuss", "hubby", "wakes", "rural", "nodal", "doric", "carry", "chefs", "fails", "klaus", "shine", "filly", "yawls", "brows", "cabby", "favor", "styli", "filed", "jinni", "ferry", "balls", "lakes", "voled", "drone", "lusty", "tansy", "among", "trail", "liven", "slake", "madge", "steps", "donne", "sties", "picks", "lacks", "jumpy", "meade", "bogie", "bauer", "scene", "lubes", "brigs", "label", "fines", "grebe", "limns", "mouse", "ensue", "swags", "bunch", "kayla", "micky", "sneak", "bulbs", "camus", "yours", "aisha", "dunne", "volta", "cores", "dweeb", "libby", "flees", "shops", "bided", "satan", "socks", "draws", "golfs", "taunt", "genus", "belts", "orbit", "taxis", "hinds", "fakes", "chart", "wings", "words", "digit", "copse", "deena", "perry", "sanes", "huffy", "chung", "lucks", "fills", "selma", "wafts", "pecks", "trite", "combs", "sooth", "weary", "salty", "brews", "kooky", "robby", "loans", "props", "huang", "marry", "swabs", "tinny", "mince", "japed", "ellis", "lowed", "newly", "loath", "drown", "loved", "joker", "lints", "kinky", "skits", "feats", "hiker", "doles", "every", "dolby", "stirs", "lobed", "fusty", "cozen", "vader", "byron", "dozes", "slows", "bethe", "ploys", "misty", "binds", "bumpy", "spurs", "wolfs", "ernie", "nails", "prows", "seeds", "visas", "dowse", "pores", "jocks", "cower", "hoofs", "mined", "marat", "gorge", "souse", "clack", "liter", "jewel", "hates", "boats", "stark", "blabs", "murks", "woken", "stomp", "peeks", "perky", "pasta", "goats", "hocks", "kinks", "gushy", "outdo", "gelds", "foxes", "fives", "sybil", "upton", "taine", "helga", "mauls", "gills", "grows", "bauds", "aloft", "cline", "payer", "pinch", "thorn", "slits", "thumb", "biked", "cowls", "grams", "disks", "belly", "randy", "hunts", "prize", "minty", "river", "chevy", "gages", "cysts", "years", "scoff", "becky", "inert", "abler", "bevel", "dyers", "tonne", "glows", "ocean", "spits", "bowen", "tings", "baths", "goals", "whiny", "merry", "fares", "leila", "cairo", "honor", "verge", "teary", "pimps", "sarah", "meets", "tamed", "bumps", "alias", "pings", "wears", "dante", "snore", "ruled", "savor", "gapes", "loony", "chaps", "froth", "fancy", "herbs", "cutes", "crowd", "ghana", "teddy", "abate", "scalp", "mules", "patsy", "minks", "shuck", "billy", "helen", "stain", "moles", "jodie", "homed", "stack", "niger", "denny", "kinds", "elves", "waled", "rover", "medan", "churn", "whizz", "green", "reach", "lajos", "mates", "ditch", "grads", "start", "press", "rimed", "hells", "vised", "slums", "notes", "canes", "taper", "camry", "weans", "sinks", "arise", "crown", "prier", "ramps", "wotan", "chars", "mussy", "rodes", "sonar", "cheri", "sired", "snell", "basel", "eider", "sades", "times", "ovule", "gusto", "myrna", "gabby", "dully", "spake", "beast", "towns", "allay", "gaged", "smell", "skids", "clone", "slack", "pooch", "vulva", "arson", "blown", "kongo", "maize", "thick", "brags", "spore", "soles", "trial", "snort", "price", "bowel", "stoke", "pents", "hutch", "flack", "arced", "cubic", "hiram", "tongs", "lades", "coons", "finer", "games", "unpin", "vests", "slabs", "santa", "tamer", "asian", "tease", "miked", "lodes", "vents", "leafy", "stats", "shuts", "bully", "edith", "bloch", "corps", "bloom", "doses", "coins", "skips", "gains", "hided", "coops", "ninja", "pills", "raves", "hanks", "seres", "ewing", "bests", "wrath", "burgs", "thrum", "cabin", "daren", "imams", "junks", "brood", "bacon", "creel", "gazed", "teats", "halos", "gypsy", "ether", "train", "tiles", "bulks", "bolls", "added", "roger", "sites", "balmy", "tilts", "swoop", "jules", "bawdy", "mango", "stoop", "girts", "costs", "lemur", "yucks", "swazi", "okays", "piped", "ticks", "tomes", "filch", "depth", "meals", "coots", "bites", "pansy", "spelt", "leeks", "hills", "drops", "verde", "japes", "holds", "bangs", "maxed", "plume", "frets", "lymph", "modes", "twits", "devon", "cawed", "putty", "sowed", "likes", "quips", "board", "loxed", "slags", "dilly", "refit", "saved", "takes", "meter", "prove", "spacy", "poach", "cilia", "pears", "lists", "gated", "verdi", "shave", "notch", "culls", "shams", "weedy", "gaols", "hoops", "kraft", "burro", "roles", "rummy", "click", "plots", "mitty", "yanks", "drool", "papal", "rearm", "prose", "fucks", "berra", "salas", "tents", "flues", "loves", "poker", "parry", "polyp", "agent", "flown", "walls", "studs", "troll", "baron", "earle", "panda", "wiley", "raged", "sexes", "berne", "vista", "rojas", "cones", "byway", "vases", "wines", "forth", "freya", "gully", "fires", "sails", "dusts", "terse", "booed", "stung", "basic", "saver", "basis", "hmong", "brawn", "pured", "locks", "downs", "punts", "rhine", "metes", "title", "shims", "bents", "blows", "harte", "boyle", "peach", "posts", "olson", "might", "flier", "rubes", "lingo", "tarts", "nexus", "woman", "mains", "finis", "mikes", "pleas", "trams", "shawl", "gunny", "sleds", "ruder", "aries", "usher", "refed", "toady", "caper", "tries", "gimpy", "doors", "thieu", "deere", "mucky", "rests", "mares", "cards", "bouts", "dines", "rants", "giles", "flunk", "enact", "derek", "dover", "conan", "mooed", "fiver", "kaput", "enrol", "payed", "feint", "miner", "shyer", "whelk", "perch", "furor", "hayes", "tammy", "caves", "maims", "cairn", "tract", "legal", "adler", "veldt", "basal", "spiny", "surer", "bolds", "grove", "heaps", "noway", "pokes", "tubed", "beaks", "loots", "drawl", "jones", "typed", "funny", "cells", "beaus", "bayed", "rears", "seats", "hazed", "flubs", "maura", "goths", "rumba", "morse", "fumes", "slide", "snoot", "music", "sully", "perth", "pocks", "mills", "lopez", "sacks", "stine", "gawks", "gavel", "rains", "wound", "hares", "guild", "leger", "foxed", "craws", "rinds", "faced", "groom", "lully", "boded", "lends", "serge", "sword", "faked", "envoy", "stick", "tumor", "riser", "bolts", "trued", "gasps", "thoth", "veers", "verbs", "boles", "lunar", "taxes", "vexes", "pucks", "welsh", "pelts", "shift", "booth", "smote", "spied", "gnawn", "crete", "dough", "tasha", "timed", "wired", "state", "hears", "lauds", "wills", "dummy", "basil", "belie", "calls", "crams", "matts", "gybes", "limed", "snots", "moder", "faces", "sibyl", "spare", "crops", "drips", "frown", "doggy", "pearl", "reese", "curls", "earns", "poles", "tiara", "risks", "lethe", "titan", "tucks", "trace", "vises", "prick", "sears", "ogled", "preps", "livid", "kicky", "candy", "weeps", "tapes", "cokes", "foods", "wards", "coifs", "shirk", "elsie", "ketch", "trunk", "goofs", "kodak", "toyed", "lance", "whale", "soups", "roars", "poxed", "tombs", "noons", "hindi", "basie", "hoffa", "bayou", "tests", "roots", "shove", "hoses", "doled", "tempt", "kilos", "velma", "avers", "dorks", "comic", "fanny", "poops", "sicks", "leary", "merer", "finks", "garbo", "cains", "mimed", "sates", "celli", "flats", "grown", "broth", "augur", "chaos", "sangs", "chide", "barks", "guide", "mewed", "synch", "rings", "scrap", "zings", "howls", "duded", "noemi", "geeks", "nexis", "comte", "helot", "whams", "brand", "hogan", "moira", "trips", "loges", "baits", "winds", "marla", "never", "louis", "anted", "helix", "morns", "heeds", "crags", "rowdy", "becks", "venue", "diary", "stoat", "feeds", "kiths", "riled", "drags", "lucia", "deeps", "sends", "fonts", "swing", "fence", "stout", "trice", "taker", "drugs", "babel", "plows", "pends", "sloes", "gents", "brawl", "arabs", "leaps", "flied", "fulls", "meats", "megan", "burch", "oscar", "evict", "betsy", "lasts", "ethos", "mavis", "petal", "fever", "alone", "snips", "assay", "rocks", "talon", "grass", "clive", "discs", "wrapt", "calfs", "razed", "learn", "bruce", "midst", "swear", "merck", "meyer", "funks", "lobby", "fears", "decay", "sedge", "alien", "reaps", "koran", "range", "enter", "lepke", "honed", "gallo", "staid", "joist", "lines", "paler", "fined", "sorts", "piper", "highs", "busch", "dario", "north", "ashed", "sands", "songs", "rakes", "garza", "pinks", "rival", "leann", "allow", "golds", "hilts", "berry", "hicks", "idler", "weiss", "cider", "desks", "skies", "hulls", "warns", "datum", "brown", "leapt", "dregs", "dozed", "stump", "reply", "finny", "clues", "diode", "dicks", "rabid", "moors", "limbs", "gulls", "scary", "dungs", "liege", "vicky", "nigel", "peeps", "dolls", "blame", "sings", "wants", "fuzes", "proud", "bungs", "seams", "bingo", "buffs", "shire", "decks", "hosed", "scots", "pumas", "jazzy", "books", "ellie", "hayed", "snowy", "twill", "links", "coped", "spats", "reyes", "piles", "hovel", "reads", "wryer", "patty", "sling", "oneal", "waves", "gorse", "ofter", "teams", "strep", "mores", "daily", "spoil", "limes", "foots", "dells", "hakes", "danny", "furls", "flaws", "tarot", "dusty", "potts", "tells", "pager", "claps", "serra", "josie", "award", "pewee", "snack", "lobes", "damps", "tanya", "lures", "mushy", "hertz", "caret", "marco", "parks", "pithy", "synge", "spoon", "troth", "drama", "bleak", "lidia", "banns", "forms", "iambs", "crick", "patel", "mercy", "waded" , "brown"};

	auto b2 = a.findLadders(beginWord, endWord, wordList); 
	cout << b2.size() << endl;
	prt2Layer(b2); 


}
