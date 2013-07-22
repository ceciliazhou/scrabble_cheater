#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

/* A dictionary object loads words from a given file and is able to tell whether a given word is valid. */
class Dict{ /* to be replaced with Trie */
public:
	Dict(const char* filename){
		ifstream ifs (filename);
		string word;
		while(ifs >> word)
			dict.insert(word);
	}

	bool contains(const string& word) const {
		return dict.find(word) != dict.end();
	}

	~Dict(){};
	unordered_set<string> dict;
};

/*  Scrabble value for characters from 'a' to 'z' */
const int scores[] = { 	1, 3, 3, 2, 1, 4, 2, 
		   	4, 1, 8, 5, 1, 3, 1, 
			1, 3, 10, 1, 1, 1, 
			1, 4, 4, 8, 4, 10};

/* Calculate the score of a word. */
int score(const string word){
	int s = 0;
	for(int i = 0; i < word.length(); i++)
		s += scores[tolower(word[i])-'a'];				
	return s;
}

/* The following compare function is used to determine whether a pair of record <word, score> 
    should be placed before another pair when sorting. */
bool highScoreGoFirst(const pair<string, int>& w1, const pair<string, int>& w2){
	return w1.second > w2.second || (w1.second == w2.second && w1.first > w2.first);
}

/* Build up and pass out records in the form of <word, score> based on a given set of characters and its maximum occurence.
    param:
    	choice: available characters and its maximum occurence.
    	curWord: the word made along the recursive call stack.
    	dict: dictionary to look up valid words.
    	words: the collection of valid words can be made based on choice.
*/
void constructWords(unordered_map<char, int>& choice, string& curWord, const Dict& dict, vector<pair<string, int> >& words){
	for(auto it = choice.begin(); it != choice.end(); it++){
		if(it->second <= 0)
			continue;

		curWord += it->first;
		it->second--;
		if(dict.contains(curWord))
			words.push_back(make_pair(curWord, score(curWord)));
		constructWords(choice, curWord, dict, words);		
		
		choice[curWord.back()]++;
		curWord.pop_back();		
	}
}


int main(int argc, char** argv){
	if(argc < 2){
		cout << "Usage: " << argv[0] << " rack [dict]" << endl;
		return 0;
	}

	//initialize rack and dictionary.
	Dict dict(argc < 3 ? "dict.txt" : argv[2]);
	char* rack = argv[1];
	unordered_map<char, int> choice;
	for(int i = 0; i < strlen(rack); i++){
		if(choice.find(rack[i]) == choice.end())
			choice[toupper(rack[i])] = 0;
		choice[toupper(rack[i])]++;
	}	

	vector<pair<string, int> > words;
	string word;
	constructWords(choice, word, dict, words);
	sort(words.begin(), words.end(), highScoreGoFirst);

	for(auto it = words.begin(); it != words.end(); it++)
		cout << it->second << ", " << it->first << endl;
}
