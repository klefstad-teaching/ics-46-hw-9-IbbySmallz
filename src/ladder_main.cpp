#include <iostream>
#include <string>
#include <set>
#include "ladder.h"
using namespace std;

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    cout << "Dictionary loaded. Number of words = " << word_list.size() << endl;

    cout << "Enter start word: ";
    string begin_word;
    cin >> begin_word;
    cout << "Enter end word: ";
    string end_word;
    cin >> end_word;

    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words must differ!");
    }

    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);

    print_word_ladder(ladder);

    return 0;
}
