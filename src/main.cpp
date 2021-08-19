// Copyright (C) 2021 GPL 3 and higher by Ingo Höft,  <Ingo@Hoeft-online.de>
// Redistribution only with this Copyright remark. Last modified: 2021-08-16

#include "pthread.h"
#include <iostream>
#include <chrono>
#include <thread>

const int WAIT = 4;

void* start_routine(void*) {
    // Will wait until greeting
    std::this_thread::sleep_for(std::chrono::seconds(WAIT));
    std::cout << "Hello World from thread :-)" << std::endl;
    return(0);  // calls pthread_exit()
}

int main() {
    pthread_t thread;
    int rc;

    // returns immediately, the greeting will come WAIT seconds later
    rc = pthread_create(&thread, NULL, &start_routine, NULL);
    std::cout << "DEBUG: return code from pthread_create() is: " << rc << std::endl;

    if (rc) {
        std::cerr << "Error! unable to create thread, " << rc << std::endl;
        exit(-1);
    }

    // Of course we habe to wait a bit longer than WAIT seconds.
    // Otherwise the main program will finish before the thread ends.
    // Fiddling with different WAIT times is only to see what happens.
    // For production code you should use pthread_join() to wait until
    // the thread finished.
    std::this_thread::sleep_for(std::chrono::seconds(WAIT+1));

    return(0);  // This will terminate all running threads from this process
}
