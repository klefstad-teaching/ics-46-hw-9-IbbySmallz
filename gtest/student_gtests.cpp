#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

#include <set>
#include <vector>
using namespace std;


TEST(IsAdjacentTest, SameLengthOneDiff) {
    EXPECT_TRUE(is_adjacent("code", "cade"));
    EXPECT_FALSE(is_adjacent("code", "code"));
    EXPECT_FALSE(is_adjacent("code", "coda"));
}

TEST(IsAdjacentTest, InsertDeleteCheck) {
    EXPECT_TRUE(is_adjacent("cat", "chat"));
    EXPECT_TRUE(is_adjacent("chat", "hat"));
    EXPECT_FALSE(is_adjacent("chat", "that"));
}

TEST(GenerateWordLadderTest, BasicShortLadder) {
    set<string> dict = {"cade", "cate", "date", "data", "dog", "cat"};
    vector<string> ladder = generate_word_ladder("code", "data", dict);

    EXPECT_EQ(ladder.size(), 5); 
    EXPECT_EQ(ladder.front(), "code");
    EXPECT_EQ(ladder.back(),  "data");
}

TEST(GenerateWordLadderTest, NoSolution) {
    set<string> dict = {"abc", "def"};
    auto ladder = generate_word_ladder("start", "end", dict);
    EXPECT_TRUE(ladder.empty()); // No path
}


TEST(VerifyWordLadderTest, PairCatDog) {
    set<string> word_list;
    load_words(word_list, "words.txt");
    auto ladder = generate_word_ladder("cat", "dog", word_list);

    EXPECT_EQ(ladder.size(), 4);
}
