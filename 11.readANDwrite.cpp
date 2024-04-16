#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

const int NUM_READERS = 3;
const int NUM_WRITERS = 2;

sem_t mutex, rw_mutex;
int readers_count = 0;

void reader(int id) {
    while (true) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);
        
        // Reading section
        cout << "Reader " << id << " is reading." << endl;
        
        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        // Sleep for a random time to simulate reading time
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    }
}

void writer(int id) {
    while (true) {
        sem_wait(&rw_mutex);
        
        // Writing section
        cout << "Writer " << id << " is writing." << endl;
        
        sem_post(&rw_mutex);

        // Sleep for a random time to simulate writing time
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    thread readers[NUM_READERS], writers[NUM_WRITERS];
    
    for (int i = 0; i < NUM_READERS; ++i) {
        readers[i] = thread(reader, i + 1);
    }
    
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers[i] = thread(writer, i + 1);
    }
    
    for (int i = 0; i < NUM_READERS; ++i) {
        readers[i].join();
    }
    
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers[i].join();
    }
    
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    
    return 0;
}
