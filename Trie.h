#include <string>
#include <vector>
using std::string;
using std::vector;

class Trie{
public:
	static const int NUM_OF_CHAR = 26;
	static const int PREFIX = 1;
	static const int WORD = 3;
	static const int NONE = 0;
	
	Trie();
	~Trie();

	/*	Insert a word into the dictionary. 	*/
	void insert(const string& word);
	
	/* 	Return whether a given word is contained in the dictionary.
		param:
			word: the word to be tested.
		return:
			Trie::WORD, if word is a valid word in the dictionary.
			Trie::PREFIX, if word is a prefix of some word(s) in the dictionary
			Trie::NONE, otherwise.
	*/
	int find(const string& word) const;

	/* 	Return a vector of all wrods in the dictionary. 	*/
	vector<string> allWords() const;

private:
	bool endOfWord;
	Trie* successor[NUM_OF_CHAR];

	void insert(const string& word, int cur);
	int find(const string& word, int cur) const;
	void allWords(string& word, vector<string>& all) const;
};

