# Copyright (C) 2021 GPL 3 and higher by Ingo Höft,  <Ingo@Hoeft-online.de>
# Redistribution only with this Copyright remark. Last modified: 2021-08-16

cmake_minimum_required(VERSION 3.18)

project(PTHREADSWINLIN VERSION 2
        DESCRIPTION "Proof of concept building pthreads on MS Windows and Linux"
        HOMEPAGE_URL "https://github.com/ingo-h/pthreadsWinLin")


if(WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/include/pthreads4w
    )

    add_executable(main-static ${PROJECT_SOURCE_DIR}/src/main.cpp
    )
    target_link_libraries(main-static
            ${PROJECT_SOURCE_DIR}/lib/static/libpthreadVC3.lib
            -NODEFAULTLIB:LIBCMT
    )

    add_executable(main-shared ${PROJECT_SOURCE_DIR}/src/main.cpp
    )
    target_link_libraries(main-shared
            ${PROJECT_SOURCE_DIR}/lib/shared/pthreadVC3.lib
    )

else()

    # Other supported operating systems provide pthreads. We only have to tell
    # that it should be used.

    find_package(Threads REQUIRED)
    if(Threads_FOUND)
        add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp)
        target_link_libraries(main pthread)
    endif()

endif()
