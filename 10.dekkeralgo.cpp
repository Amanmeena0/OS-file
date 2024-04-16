#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

const int NUM_THREADS = 2;

bool flag[2];
int turn = 0;
sem_t sem;

void process(int id) {
    for (int i = 0; i < 5; ++i) {
        sem_wait(&sem);
        flag[id] = true;
        while (flag[1 - id]) {
            if (turn == 1 - id) {
                flag[id] = false;
                while (turn != id) {}
                flag[id] = true;
            }
        }
        sem_post(&sem);
        
        // Critical section
        cout << "Thread " << id + 1 << " is in critical section.\n";
        turn = 1 - id;
        flag[id] = false;
    }
}

int main() {
    sem_init(&sem, 0, 1);
    thread threads[NUM_THREADS];
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i] = thread(process, i);
    }
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
    }
    
    sem_destroy(&sem);
    
    return 0;
}
