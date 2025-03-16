#include "ladder.h"

#define my_assert(e) { \
    cout << #e << ((e) ? " passed" : " failed") << endl; \
}

void error(const string& word1, const string& word2, const string& msg) {
    cerr << "ERROR: " << msg 
         << "  (word1='" << word1 << "', word2='" << word2 << "')" << endl;

}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (std::abs((int)str1.size() - (int)str2.size()) > d) {
        return false;
    }

    return false;

}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = (int)word1.size();
    int len2 = (int)word2.size();
    if (std::abs(len1 - len2) > 1) {
        return false;
    }

    if (len1 == len2) {
        int diffCount = 0;
        for (int i = 0; i < len1; i++) {
            if (word1[i] != word2[i]) {
                diffCount++;
                if (diffCount > 1) return false;
            }
        }
        return (diffCount == 1);
    }
    else {
        const string& longer  = (len1 > len2 ? word1 : word2);
        const string& shorter = (len1 > len2 ? word2 : word1);

        int i = 0, j = 0; 
        int mismatchCount = 0;
        while (i < (int)longer.size() && j < (int)shorter.size()) {
            if (longer[i] != shorter[j]) {
                mismatchCount++;
                if (mismatchCount > 1) return false;
                i++;
            } else {
                i++;
                j++;
            }
        }
        mismatchCount += ( (int)longer.size() - i );
        return (mismatchCount == 1);
    }
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

    queue< vector<string> > ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);  

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = current_ladder.back();

        for (const auto& candidate : word_list) {
            if (visited.find(candidate) == visited.end() 
                && is_adjacent(last_word, candidate)) 
            {
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
        cout << "No ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            if (i > 0) cout << " -> ";
            cout << ladder[i];
        }
        cout << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat",   "dog",   word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code",  "data",  word_list).size() == 6);
    my_assert(generate_word_ladder("work",  "play",  word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car",   "cheat", word_list).size() == 4);
}