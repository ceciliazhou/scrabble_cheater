#include "Trie.h"
#include <iostream>
#include <cstring>

using namespace std;

Trie::Trie():endOfWord(false), successor{}{}

Trie::~Trie(){
	for(int i = 0; i < Trie::NUM_OF_CHAR; i++)
		delete successor[i];
}

void Trie::insert(const string& word){
	if(word == "") return;
	return insert(word, 0);
}

void Trie::insert(const string& word, int cur){
	if(cur == word.length()){
		endOfWord = true;
		return;
	}

	int index = tolower(word[cur]) - 'a';
	if(successor[index] == NULL)
		successor[index] = new Trie();
	successor[index]->insert(word, cur+1);
}

int Trie::find(const string& word) const{
	if(word == "") return false;
	return find(word, 0);
}

int Trie::find(const string& word, int cur) const{
	if(cur == word.length())
		return endOfWord ? int(Trie::WORD) : int(Trie::PREFIX);

	int index = tolower(word[cur]) - 'a';
	if(successor[index] == NULL)
		return int(Trie::NONE);
	return successor[index]->find(word, cur+1);
}

vector<string> Trie::allWords() const{
	vector<string> result;
	string word;
	allWords(word, result);
	return result;
}

void Trie::allWords(string& word, vector<string>& all) const{
	if(endOfWord)
		all.push_back(word);
	for(int i = 0; i < Trie::NUM_OF_CHAR; i++){
		if(successor[i] != NULL){
			word.push_back('a' + i);
			successor[i]->allWords(word, all);
			word.pop_back();
		}
	}
}


