#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareBurstTime(const Process& p1, const Process& p2) {
    return p1.burstTime < p2.burstTime;
}

void SJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

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

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << " arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << i + 1 << " burst time: ";
        cin >> processes[i].burstTime;
        processes[i].id = i + 1;
    }

    SJF(processes);

    // Output the schedule
    cout << "\nSJF Scheduling:\n";
    cout << "ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.id << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
             << process.completionTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << endl;
    }

    return 0;
}
