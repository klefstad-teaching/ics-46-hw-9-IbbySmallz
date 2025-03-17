#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> dist(n, INF);
    previous.assign(n, -1);

    using Node = pair<int,int>;
    auto cmp = [](const Node& a, const Node& b) {
        return a.first > b.first; // min‐heap by distance
    };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [costSoFar, u] = pq.top();
        pq.pop();

        if (costSoFar > dist[u]) {
            continue;
        }

        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            int newDist = dist[u] + w;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                previous[v] = u;
                pq.push({newDist, v});
            }
        }
    }
    return dist;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    if (destination < 0 || destination >= (int)previous.size()
        || distances[destination] == INF) 
    {
        return path; // empty
    }
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total)
{
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }

    cout << "\n";

    cout << "Total cost is " << total << "\n";
}
