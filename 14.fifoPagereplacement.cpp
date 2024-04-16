#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int fifoPageReplacement(int pages[], int n, int capacity) {
    queue<int> fifoQueue; // Queue to store pages in the order of their arrival
    unordered_set<int> pageSet; // Set to keep track of pages currently in the cache
    int pageFaults = 0;

    for (int i = 0; i < n; ++i) {
        // If the page is not in the cache
        if (pageSet.find(pages[i]) == pageSet.end()) {
            // If the cache is full, remove the oldest page
            if (fifoQueue.size() == capacity) {
                int oldestPage = fifoQueue.front();
                fifoQueue.pop();
                pageSet.erase(oldestPage);
            }

            // Add the new page to the cache
            fifoQueue.push(pages[i]);
            pageSet.insert(pages[i]);

            pageFaults++;
        }
    }

    return pageFaults;
}

int main() {
    // Page reference string
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    // Capacity of the cache
    int capacity = 4;

    // Number of pages
    int n = sizeof(pages) / sizeof(pages[0]);

    // Calculate the number of page faults using FIFO page replacement algorithm
    int pageFaults = fifoPageReplacement(pages, n, capacity);

    cout << "Number of page faults using FIFO page replacement algorithm: " << pageFaults << endl;

    return 0;
}
