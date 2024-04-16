#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

class DisjointSets {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSets(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int v) : V(v) {
        adjList.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    long long primMST() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> visited(V, false);
        long long minCost = 0;

        pq.push({0, 0}); // {weight, vertex}

        while (!pq.empty()) {
            int u = pq.top().second;
            int w = pq.top().first;
            pq.pop();

            if (visited[u]) continue;

            visited[u] = true;
            minCost += w;

            for (const auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (!visited[v]) {
                    pq.push({weight, v});
                }
            }
        }

        return minCost;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter the edges in the format: source destination weight\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    long long minCost = g.primMST();
    cout << "Minimum Cost Spanning Tree: " << minCost << endl;

    return 0;
}
    