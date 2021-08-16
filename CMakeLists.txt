# Copyright (C) 2021 GPL 3 and higher by Ingo Höft, <Ingo@Hoeft-online.de>
# Redistribution only with this Copyright remark. Last modified: 2021-08-16

cmake_minimum_required(VERSION 3.18)

project(PTHREADSWINLIN VERSION 1
        DESCRIPTION "Proof of concept building pthreads on MS Windows and Linux"
        HOMEPAGE_URL "https://github.com/ingo-h/pthreadsWinLin")


include_directories(${PROJECT_SOURCE_DIR}/include/pthreads4w
)

add_executable(main-static ${PROJECT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(main-static
        ${PROJECT_SOURCE_DIR}/lib/static/libpthreadVC3.lib
        -__PTW32_STATIC_LIB
        -NODEFAULTLIB:LIBCMT
)

add_executable(main-shared ${PROJECT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(main-shared
        ${PROJECT_SOURCE_DIR}/lib/shared/pthreadVC3.lib
)
