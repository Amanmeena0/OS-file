#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<int> lruList; // Doubly linked list to maintain the order of pages based on their recency
    unordered_map<int, list<int>::iterator> pageMap; // Map to store page number and its iterator in the list

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    void referPage(int page) {
        // If the page is already in the cache
        if (pageMap.find(page) != pageMap.end()) {
            // Move the page to the front of the list to mark it as the most recently used
            lruList.erase(pageMap[page]);
            lruList.push_front(page);
            pageMap[page] = lruList.begin();
        }
        // If the page is not in the cache
        else {
            // If the cache is full, remove the least recently used page
            if (lruList.size() == capacity) {
                int leastRecent = lruList.back();
                lruList.pop_back();
                pageMap.erase(leastRecent);
            }
            // Add the new page to the front of the list
            lruList.push_front(page);
            pageMap[page] = lruList.begin();
        }
    }

    void displayCache() {
        for (int page : lruList) {
            cout << page << " ";
        }
        cout << endl;
    }
};

int main() {
    // Capacity of the cache
    int capacity = 4;
    LRUCache cache(capacity);

    // Page reference string
    int pages[] = {1, 2, 3, 1, 4, 5, 2, 1, 5};

    for (int page : pages) {
        cache.referPage(page);
        cout << "Page " << page << " is referenced. Cache: ";
        cache.displayCache();
    }

    return 0;
}
