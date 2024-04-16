#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if the current state is safe or not
bool isSafe(vector<vector<int>>& max, vector<vector<int>>& allocated, vector<int>& available, vector<int>& work, vector<bool>& finish) {
    int n = max.size(); // Number of processes

    bool safe = false;
    bool canAllocate;

    // Repeat until all processes are finished
    for (int i = 0; i < n; ++i) {
        if (!finish[i]) {
            canAllocate = true;

            // Check if the current process can be allocated with current available resources
            for (int j = 0; j < available.size(); ++j) {
                if (max[i][j] - allocated[i][j] > available[j]) {
                    canAllocate = false;
                    break;
                }
            }

            // If the current process can be allocated, allocate resources and mark it as finished
            if (canAllocate) {
                finish[i] = true;
                for (int j = 0; j < available.size(); ++j) {
                    available[j] += allocated[i][j];
                }
                work = available;
                safe = true;
            }
        }
    }

    // Check if all processes are finished
    for (bool f : finish) {
        if (!f) {
            safe = false;
            break;
        }
    }

    return safe;
}

// Function to implement Banker's algorithm
bool bankersAlgorithm(vector<vector<int>>& max, vector<vector<int>>& allocated, vector<int>& available) {
    int n = max.size(); // Number of processes
    int m = available.size(); // Number of resources

    vector<int> work = available; // Copy of available resources
    vector<bool> finish(n, false); // Vector to track finished processes

    // Check if the current state is safe or not
    bool safe = isSafe(max, allocated, available, work, finish);

    return safe;
}

int main() {
    int n, m; // n: number of processes, m: number of resources
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    vector<vector<int>> max(n, vector<int>(m)); // Maximum demand of each process
    vector<vector<int>> allocated(n, vector<int>(m)); // Currently allocated resources for each process
    vector<int> available(m); // Available resources

    // Input maximum demand of each process
    cout << "Enter maximum demand of each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < m; ++j) {
            cin >> max[i][j];
        }
    }

    // Input currently allocated resources for each process
    cout << "Enter currently allocated resources for each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < m; ++j) {
            cin >> allocated[i][j];
        }
    }

    // Input available resources
    cout << "Enter available resources: ";
    for (int j = 0; j < m; ++j) {
        cin >> available[j];
    }

    // Check if the current state is safe using Banker's algorithm
    bool safe = bankersAlgorithm(max, allocated, available);

    if (safe) {
        cout << "The current state is safe.\n";
    } else {
        cout << "The current state is unsafe.\n";
    }

    return 0;
}
