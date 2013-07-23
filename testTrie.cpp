#include <cassert>
#include <string>
#include <iostream>
#include "Trie.h"

using namespace std;

void test(){
	Trie t;
	string s[5] = {"word", "abandon", "abuse", "back", "bed"};
	for(int i = 0; i < 5; i++)
		t.insert(s[i]);

	for(int i = 0; i < 5; i++){
		assert(t.contains(s[i]) == 1);
		for(int j = 1; j < s[i].length(); j++)
			assert(t.contains(s[i].substr(0, j)) == 2);
			
		assert(t.contains(s[i]+"a") == 0);			
	}

	vector<string> words = t.allWords();
	for(int i = 0; i < words.size(); i++)
		cout << words[i] << endl;
	
}

int main(){
	test();
}