// Copyright (C) 2021 GPL 3 and higher by Ingo Höft,  <Ingo@Hoeft-online.de>
// Redistribution only with this Copyright remark. Last modified: 2021-08-16

#include "pthread.h"
#include <iostream>

// comment/uncomment next line to select the program version to oompile
#define WAIT_THREAD 4
#define WAIT_MAIN 5

#ifdef WAIT_THREAD
#include <chrono>
#include <thread>

// Version with delays to wait for finish of the thread
//-----------------------------------------------------
// This version uses simple time delays to "manage" execution of the thread.
// This keep things as simple as possible. If in doubt with threading you should
// start with this version. You can also see what happens if you set WAIT_MAIN
// lower than WAIT_THREAD.
void* start_routine(void*) {
    // Will wait until greeting
    std::this_thread::sleep_for(std::chrono::seconds(WAIT_THREAD));
    std::cout << "Hello World from thread :-)" << std::endl;
    return (0); // calls pthread_exit()
}

int main() {
    pthread_t thread;
    int rc;

    // returns immediately, the greeting will come WAIT_THREAD seconds later
    rc = pthread_create(&thread, NULL, &start_routine, NULL);
    std::cout << "DEBUG: return code from pthread_create() is: " << rc
              << std::endl;

    if (rc) {
        std::cerr << "Error! unable to create thread, " << rc << std::endl;
        exit(-1);
    }

    // Of course we have to wait a bit longer than WAIT_THREAD seconds.
    // Otherwise the main program will finish before the thread ends.
    // Fiddling with different wait times is only to see what happens.
    // For production code you should use pthread_join() to wait until
    // the thread finished. Check the other program version below.
    std::this_thread::sleep_for(std::chrono::seconds(WAIT_MAIN));

    return (0); // This will terminate all running threads from this process
}

#else  // ifdef WAIT_THREAD

// Version with using pthread_join() to wait for finish of the thread
//-------------------------------------------------------------------
// This is the normal way to wait for a thread to finish.
void* start_routine(void*) {
    std::cout << "Hello World from thread :-)" << std::endl;
    return ((void*)0); // calls pthread_exit()
}

int main() {
    pthread_t thread;
    int rc;
    void* retval;

    // returns immediately
    rc = pthread_create(&thread, NULL, &start_routine, NULL);
    std::cout << "DEBUG: return code from pthread_create() is: " << rc
              << std::endl;
    if (rc != 0) {
        std::cerr << "Error! unable to create thread, " << rc << std::endl;
        exit(1);
    }

    rc = pthread_join(thread, &retval);
    if (rc != 0) {
        std::cerr << "Error! Unable to join thread with rc=" << rc << std::endl;
        exit(1);
    }
    if (retval != NULL) {
        std::cerr << "Error! Thread failed with retval=" << retval << std::endl;
        exit(1);
    }

    return (0); // This will terminate all running threads from this process
}
#endif // ifdef WAIT_THREAD
