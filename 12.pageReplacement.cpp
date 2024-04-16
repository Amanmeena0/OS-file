#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

int optimalPageReplacement(vector<int>& pages, int capacity) {
    int pageFaults = 0;
    unordered_set<int> cache;
    unordered_map<int, int> nextUse; // Map to store the next use of each page
    queue<int> q; // Queue to maintain the order of pages in the cache

    for (int page : pages) {
        if (cache.find(page) == cache.end()) { // Page is not in cache
            pageFaults++;

            if (cache.size() == capacity) { // Cache is full, need to evict
                int pageToEvict = -1;
                int farthestNextUse = INT_MIN;

                for (int p : cache) {
                    if (nextUse.find(p) == nextUse.end()) { // If page won't be used anymore
                        pageToEvict = p;
                        break;
                    }
                    if (nextUse[p] > farthestNextUse) {
                        farthestNextUse = nextUse[p];
                        pageToEvict = p;
                    }
                }

                cache.erase(pageToEvict);
                q.pop();
            }

            cache.insert(page);
            q.push(page);
        }

        // Update next use of pages in cache
        for (int p : cache) {
            if (p != page && nextUse.find(p) == nextUse.end()) {
                nextUse[p] = 0;
            }
            if (p != page) {
                nextUse[p]++;
            }
        }
    }

    return pageFaults;
}

int main() {
    vector<int> pages = {1, 2, 3, 4, 5, 1, 2, 5, 1, 2, 3, 4, 5}; // Reference string
    int capacity = 3; // Capacity of the cache

    int pageFaults = optimalPageReplacement(pages, capacity);

    cout << "Number of page faults using Optimal Page Replacement algorithm: " << pageFaults << endl;

    return 0;
}
