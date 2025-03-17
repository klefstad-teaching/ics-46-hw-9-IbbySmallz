#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    Graph G;
    string filename = "src/small.txt"; 

    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << "Error reading graph file: " << e.what() << endl;
        return 1;
    }

    vector<int> previous;
    auto dist = dijkstra_shortest_path(G,0, previous);

    for (int i = 0; i < G.numVertices; i++) {
        vector<int> path = extract_shortest_path(dist, previous, i);
        if (path.empty()) {
            cout << "No path from 0 to " << i << endl;
        } else {
            // Print the path
            print_path(path, dist[i]);
        }
        cout << endl;
    }

    return 0;
}