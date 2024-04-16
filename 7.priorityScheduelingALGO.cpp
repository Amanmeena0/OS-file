#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool comparePriority(const Process& p1, const Process& p2) {
    return p1.priority > p2.priority;
}

void PriorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        int maxPriorityIdx = i;
        for (int j = i + 1; j < n && processes[j].arrivalTime <= currentTime; ++j) {
            if (processes[j].priority > processes[maxPriorityIdx].priority) {
                maxPriorityIdx = j;
            }
        }

        swap(processes[i], processes[maxPriorityIdx]);

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter arrival time, burst time, and priority for each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << " arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << i + 1 << " burst time: ";
        cin >> processes[i].burstTime;
        cout << "Process " << i + 1 << " priority: ";
        cin >> processes[i].priority;
        processes[i].id = i + 1;
    }

    PriorityScheduling(processes);

    // Output the schedule
    cout << "\nPriority Scheduling:\n";
    cout << "ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.id << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
             << process.priority << "\t\t" << process.completionTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << endl;
    }

    return 0;
}
