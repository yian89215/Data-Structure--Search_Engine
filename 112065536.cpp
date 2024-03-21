#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include <set>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
int num = 0;
const int ALPHABET_SIZE = 26;


struct TrieNode {
    bool isEndOfWord;
    TrieNode* children[ALPHABET_SIZE];
	set<int> sourceIDs;
};

TrieNode *getNode(){
    TrieNode *pNode =  new TrieNode();
    pNode->isEndOfWord = false;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;
 
    return pNode;
}
void insert(TrieNode *root, string key) {
    // Insert the word
    TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = tolower(key[i]) - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
    //pCrawl->sourceIDs.insert(sourceid);
}
// Function to insert a word into the Trie in reverse order
void insertReverse(TrieNode *root, string word){
    TrieNode *pCrawl = root;
    for (int i = word.length() - 1; i >= 0; i--) {
        int index = tolower(word[i]) - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
    //pCrawl->sourceIDs.insert(sourceid);
}

//Exact search
bool search(TrieNode *root, string query) {
    TrieNode *pCrawl = root;
    for (int i = 0; i < query.length(); i++) {
        int index = (query[i]) - 'a';
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->isEndOfWord;
        
}

//Prefix search
bool prefixSearch(TrieNode *root, string prefix) {
    TrieNode *node = root;
	for (int i = 0; i < prefix.length(); i++) {
		int index = tolower(prefix[i]) - 'a';
		if (node->children[index] == nullptr) {
			return false;
		}
		node = node->children[index];
	}
	return true;
}

//Suffix search
bool suffixSearch(TrieNode *root, string suffix) {
	TrieNode *node = root;
	for (int i = suffix.length() - 1; i >= 0; i--) {
		int index = tolower(suffix[i]) - 'a';
		if (node->children[index] == nullptr) {
			return false;
		}
		node = node->children[index];
	}
	return true;
}

//wildcard
bool wildcardSearch(TrieNode* root, const string& word, int index, string currentWord) {
    if (index == word.size()) {
        return root->isEndOfWord;
    }

    if (word[index] == '*') {
        // Match zero or more characters
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (root->children[i] != nullptr) {
                if (wildcardSearch(root->children[i], word, index, currentWord) ||
                    wildcardSearch(root->children[i], word, index + 1, currentWord)) {
                    return true;
                }
            }
        }
        // Continue searching without consuming the '*'
        return wildcardSearch(root, word, index + 1, currentWord);
    } else {
        int charIndex = tolower(word[index]) - 'a';
        if (root->children[charIndex] != nullptr) {
            return wildcardSearch(root->children[charIndex], word, index + 1, currentWord + word[index]);
        }
    }

    return false;
}


// string parser : output vector of strings (words) after parsing
vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch))
				new_str.push_back(ch);
		}
		parse_string.emplace_back(new_str);
	}
	return parse_string;
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;

	char * strs = new char[str.length() + 1] ; 
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; 
		res.push_back(s); 
		p = strtok(NULL, d);
	}

	return res;
}
// print  node in Trie
void printWordsHelper(struct TrieNode *root, string currentWord){
    if (root->isEndOfWord){
        cout << currentWord << endl;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (root->children[i] != nullptr){
            char ch = 'a' + i;
            printWordsHelper(root->children[i], currentWord + ch);
        }
    }
}
// Function to print all words in Trie
void printTrie(TrieNode *root){
    printWordsHelper(root, "");
}

int main(int argc, char *argv[]){
    // INPUT :
	// 1. data directory in data folder
	// 2. number of txt files
	// 3. output route
	clock_t start, end_time;
    start = clock();
    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);
    for (const auto & entry : fs::directory_iterator(data_dir)) {
        if (entry.path().extension() == ".txt") {
            num++;
        }
    }

	// Read File & Parser Example
	string file, title_name, tmp;
	fstream fi;
	ofstream fout;
	vector<string> tmp_string;
	vector<string> titlename(10000);
	// from data_dir get file ....
	vector<TrieNode*> t(num);
	vector<TrieNode*> tReverse(num);
	for(int i = 0; i < num; i++){
		file = data_dir + to_string(i) + FILE_EXTENSION;
		fi.open(file, ios::in);
		t[i] = getNode();
		tReverse[i] = getNode();
		
		getline(fi, title_name); // GET 
		titlename[i] = title_name;
		tmp_string = split(title_name, " ");// GET TITLENAME WORD ARRAY
		vector<string> title = word_parse(tmp_string);
		for(auto &word : title){
			//cout << word << endl;
			insert(t[i], word);
			insertReverse(tReverse[i], word);
			//printTrie(root);
		}
				
		while(getline(fi, tmp)){// GET CONTENT LINE BY LINE
			tmp_string = split(tmp, " ");// GET CONTENT WORD VECTOR
			vector<string> content = word_parse(tmp_string);// PARSE CONTENT
			for(auto &word : content){
				//cout << word << endl;
				insert(t[i], word);
				insertReverse(tReverse[i], word);
				//printTrie(root);				
			}
		}
		//printTrie(root);
		fi.close();
	}

	// query read
    string whole_line;

    fi.open(query, ios::in);
    fout.open(output, ios::out);
    while(getline(fi, whole_line))
    {
        //cout << endl << whole_line << endl;

        int now_pos = 0;
        int len = whole_line.size();
        int and_or_mode = 0; 
        bool total_result[10000] = {0};

        while(now_pos < len)
        {
            // and
            if(whole_line[now_pos] == '+'){
                now_pos += 2;
                and_or_mode = 1;
            }
			
            //or
            else if(whole_line[now_pos] == '/'){
                now_pos += 2;
                and_or_mode = 2;
            }
			else if(whole_line[now_pos] == '-'){
				now_pos += 2;
				and_or_mode = 3;
			}
            // exact search
            else if(whole_line[now_pos] == '"'){
                int right_boundry;
                for(right_boundry = now_pos + 1; right_boundry < len; right_boundry++)
                    if(whole_line[right_boundry] == '"')
                        break;

                string test;
                test = whole_line.substr(now_pos + 1, right_boundry - now_pos - 1);
                now_pos = right_boundry + 2;

                bool result[10000] = {0};
                for(int i = 0; i < num; i++){
                    if(search(t[i], test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }
                if(and_or_mode == 0){
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1){
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2){
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] || total_result[i];
                }
				else if(and_or_mode == 3){
					for(int i = 0; i < num; i++)
						total_result[i] = !result[i] && total_result[i];
				}
            }
			//wildcard search
			else if(whole_line[now_pos] == '<')
            {
                int right_boundry;
                for(right_boundry = now_pos + 1; right_boundry < len; right_boundry++)
                    if(whole_line[right_boundry] == '>')
                        break;

                string test;
                test = whole_line.substr(now_pos + 1, right_boundry - now_pos - 1);
                now_pos = right_boundry + 2;
                bool result[10000] = {0};
                for(int i = 0; i < num; i++){
                    if(wildcardSearch(t[i], test, 0, "")){
						result[i] = 1;
						//cout << i << endl;
					}
                }
                if(and_or_mode == 0){
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1){
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2){
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] || total_result[i];
                }
				else if(and_or_mode == 3){
					for(int i = 0; i < num; i++)
						total_result[i] = !result[i] && total_result[i];
				}
            }
            // suffixSearch
            else if(whole_line[now_pos] == '*'){
                int right_boundry;
                for(right_boundry = now_pos + 1; right_boundry < len; right_boundry++)
                    if(whole_line[right_boundry] == '*')
                        break;

                string test;
                test = whole_line.substr(now_pos + 1, right_boundry - now_pos - 1);
                now_pos = right_boundry + 2;
                bool result[10000] = {0};
                for(int i = 0; i < num; i++)
                {
                    if(suffixSearch(tReverse[i], test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                if(and_or_mode == 0)
                {
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] || total_result[i];
                }
				else if(and_or_mode == 3){
					for(int i = 0; i < num; i++)
						total_result[i] = !result[i] && total_result[i];
				}
            }

            // prefix
            else
            {
                int right_boundry;
                for(right_boundry = now_pos; right_boundry < len; right_boundry++)
                    if( whole_line[right_boundry] == ' ' )
                        break;

                string test;
                test = whole_line.substr(now_pos, right_boundry - now_pos);
                now_pos = right_boundry + 1;

                bool result[10000] = {0};
                for(int i = 0; i < num; i++)
                {
                    if(prefixSearch(t[i],test))
                    {
                        result[i] = 1;
                        //cout << i << endl;
                    }

                }

                if(and_or_mode == 0)
                {
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i];
                }
                else if(and_or_mode == 1)
                {
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] && total_result[i];
                }
                else if(and_or_mode == 2)
                {
                    for(int i = 0; i < num; i++)
                        total_result[i] = result[i] || total_result[i];
                }
				else if(and_or_mode == 3){
					for(int i = 0; i < num; i++)
						total_result[i] = !result[i] && total_result[i];
				}
            }

        }

		int all_zero =1;
		for(int i = 0; i < num; i++){
			if(total_result[i] == 1){
				fout<<titlename[i]<<endl;
				all_zero = 0;
			}
		}
		if(all_zero == 1){
			fout<<"Not Found!"<<endl;
		}
	}
	fi.close();
	fout.close();
        
    end_time = clock();
}
