#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

struct CompareRemainingTime {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.remainingTime > p2.remainingTime;
    }
};

void SRTF(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;
    priority_queue<Process, vector<Process>, CompareRemainingTime> pq;

    while (completed < n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                pq.push(processes[i]);
            }
        }

        if (pq.empty()) {
            currentTime++;
            continue;
        }

        Process currentProcess = pq.top();
        pq.pop();

        currentProcess.remainingTime--;

        currentTime++;

        if (currentProcess.remainingTime == 0) {
            completed++;

            currentProcess.completionTime = currentTime;
            currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
            currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;

            processes[currentProcess.id - 1] = currentProcess;
        } else {
            pq.push(currentProcess);
        }
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
        processes[i].remainingTime = processes[i].burstTime;
    }

    SRTF(processes);

    // Output the schedule
    cout << "\nSRTF Scheduling:\n";
    cout << "ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.id << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
             << process.completionTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << endl;
    }

    return 0;
}
