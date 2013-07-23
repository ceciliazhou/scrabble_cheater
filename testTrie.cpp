#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>
#include "Trie.h"

using namespace std;

void test(){
	Trie t;
	string s[5] = {"word", "abandon", "abuse", "back", "bed"};
	for(int i = 0; i < 5; i++)
		t.insert(s[i]);

	for(int i = 0; i < 5; i++){
		assert(t.find(s[i]) == Trie::WORD);
		for(int j = 1; j < s[i].length(); j++)
			assert(t.find(s[i].substr(0, j)) == Trie::PREFIX);
			
		assert(t.find(s[i]+"a") == Trie::NONE);			
	}

	sort(s, &s[5]);
	vector<string> words = t.allWords();
	for(int i = 0; i < words.size(); i++)
		assert(words[i] == s[i]);	
}

int main(){
	test();
}