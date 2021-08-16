// Copyright (C) 2021 GPL 3 and higher by Ingo Höft,  <Ingo@Hoeft-online.de>
// Redistribution only with this Copyright remark. Last modified: 2021-08-16

#include "pthread.h"
#include <iostream>
// #include <chrono>
// #include <thread>


void* start_routine(void*) {
    std::cout << "Hello World from thread :-)" << std::endl;
//    pthread_exit(NULL);
    return(0);  // calls pthread_exit()
}

int main() {
    pthread_t thread;
    int rc;

    rc = pthread_create(&thread, NULL, &start_routine, NULL);
    std::cout << "DEBUG: return code from pthread_create() is: " << rc << std::endl;

    if (rc) {
        std::cout << "Error! unable to create thread, " << rc << std::endl;
        exit(-1);
    }

//  returns immediately on MS Windows but ...
//    std::this_thread::sleep_for(std::chrono::milliseconds(1));
//    exit(0);

//  ... to allow other threads to continue execution, the main thread should
//  terminate by calling pthread_exit() rather than exit(). But it takes
//  several seconds (about 30 sec on my bad performing virtual test machine).
//  Is it a bug? On Linux it always returns immediately.
    pthread_exit(NULL);  // last thread in process: exits program with status 0
}
