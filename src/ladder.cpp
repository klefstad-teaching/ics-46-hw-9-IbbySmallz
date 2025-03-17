#include "ladder.h"
#include <unordered_set>
#include <algorithm> 
#include <cctype>  

#define my_assert(e) { \
    cout << #e << ((e) ? " passed" : " failed") << endl; \
}

void error(string word1, string word2, string msg) {
    cerr << "ERROR: " << msg 
         << "  (word1='" << word1 << "', word2='" << word2 << "')" << endl;

}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (abs((int)str1.size() - (int)str2.size()) > d) return false;

    int len1 = str1.size(), len2 = str2.size();

    if (len1 == len2) {
        int diffCount = 0;
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                diffCount++;
                if (diffCount > 1) return false;
            }
        }
        return true;
    }
    else {
        const string &longer  = (len1 > len2 ? str1 : str2);
        const string &shorter = (len1 > len2 ? str2 : str1);
        int i = 0, j = 0, mismatch = 0;
        while (i < (int)longer.size() && j < (int)shorter.size()) {
            if (longer[i] != shorter[j]) {
                mismatch++;
                if (mismatch > 1) return false;
                i++;
            } else {
                i++; j++;
            }
        }
        mismatch += (longer.size() - i);
        return (mismatch <= 1);
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

static vector<string> generate_neighbors(const string& word) {
    static const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
    vector<string> result;

    for (int i = 0; i < (int)word.size(); i++) {
        char oldChar = word[i];
        for (char c : ALPHABET) {
            if (c == oldChar) continue; 
            string temp = word;
            temp[i] = c;
            result.push_back(temp);
        }
    }

    for (int i = 0; i <= (int)word.size(); i++) {
        for (char c : ALPHABET) {
            string temp = word;
            temp.insert(temp.begin() + i, c);
            result.push_back(temp);
        }
    }

    for (int i = 0; i < (int)word.size(); i++) {
        string temp = word;
        temp.erase(temp.begin() + i);
        result.push_back(temp);
    }

    return result;
}


vector<string> generate_word_ladder(const string& begin_word, 
                                    const string& end_word,
                                    const set<string>& word_list) 
{
    if (begin_word == end_word) {
        return {};
    }
    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }

    unordered_set<string> dict(word_list.begin(), word_list.end());

    queue< vector<string> > ladder_queue;    
    ladder_queue.push({begin_word});

    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();

        const string& last_word = current_ladder.back();

        vector<string> neighbors = generate_neighbors(last_word);

        for (auto & candidate : neighbors) {
            if (!visited.count(candidate) && dict.count(candidate)) {
                visited.insert(candidate);

                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(candidate);

                if (candidate == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}



void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        cerr << "Cannot open file: " << file_name << endl;
        return;
    }
    string word;
    while (in >> word) {
        // Convert to lowercase
        for (char& c : word) {
            c = (char)tolower((unsigned char)c);
        }
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
    } else {
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i];
            if (i + 1 < ladder.size()) cout << " ";
        }
        cout << " \n";
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat",   "dog",   word_list).size() == 4);
}