#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

#include <set>
#include <vector>
using namespace std;


TEST(IsAdjacentTest, SameLengthOneDiff) {
    EXPECT_TRUE(is_adjacent("code", "cade"));
    EXPECT_FALSE(is_adjacent("code", "code"));
    EXPECT_TRUE(is_adjacent("code", "coda"));
}

TEST(IsAdjacentTest, InsertDeleteCheck) {
    EXPECT_TRUE(is_adjacent("cat", "chat"));
    EXPECT_TRUE(is_adjacent("chat", "hat"));
    EXPECT_TRUE(is_adjacent("chat", "that"));
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
    load_words(word_list, "/home/syedi1/ICS46/ics-46-hw-9-IbbySmallz/src/words.txt");
    auto ladder = generate_word_ladder("cat", "dog", word_list);

    EXPECT_EQ(ladder.size(), 4);
}

TEST(DijkstraTest, SingleVertexNoEdges) {
    Graph G;
    G.numVertices = 1;
    G.resize(1);

    std::vector<int> previous;
    auto dist = dijkstra_shortest_path(G, 0, previous);
    
    ASSERT_EQ(dist.size(), 1u);
    EXPECT_EQ(dist[0], 0);

    auto path = extract_shortest_path(dist, previous, 0);
    ASSERT_EQ(path.size(), 1u);
    EXPECT_EQ(path[0], 0);
}

// A simple line: 0 -> 1 (weight=5), 1 -> 2 (weight=2), 2 -> 3 (weight=1)
TEST(DijkstraTest, SimpleLine) {
    
    Graph G;
    G.numVertices = 4;
    G.resize(4);

    G[0].push_back( Edge(0, 1, 5) );
    G[1].push_back( Edge(1, 2, 2) );
    G[2].push_back( Edge(2, 3, 1) );

    std::vector<int> previous;
    auto dist = dijkstra_shortest_path(G, 0, previous);

    ASSERT_EQ(dist.size(), 4u);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 5);
    EXPECT_EQ(dist[2], 7);
    EXPECT_EQ(dist[3], 8);

    auto path = extract_shortest_path(dist, previous, 3);
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(path, expected);
}

TEST(DijkstraTest, NoPath) {
    
    Graph G;
    G.numVertices = 4;
    G.resize(4);

    G[0].push_back( Edge(0, 1, 1) );
    G[1].push_back( Edge(1, 2, 1) );

    std::vector<int> previous;
    auto dist = dijkstra_shortest_path(G, 0, previous);

    ASSERT_EQ(dist.size(), 4u);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 1);
    EXPECT_EQ(dist[2], 2);
    EXPECT_EQ(dist[3], INF);

    auto pathTo3 = extract_shortest_path(dist, previous, 3);
    EXPECT_TRUE(pathTo3.empty());
    EXPECT_EQ(previous[3], -1);
}