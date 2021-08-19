# pthreadsWinLin
Proof of concept for the main project UPnPlib to have POSIX threads on Microsoft Windows and Linux with cmake.

## Using POSIX threads on Microsoft Windows
Microsoft does not support POSIX threads so we have to use a third party library. I use the well known **pthreads4w** library that we have to install first from source. Of course I can do it by script but that isn't the exercise. I want to show how it works.

First download and provide the [pthreads4w library sources](https://sourceforge.net/projects/pthreads4w/files/latest/download). At the time when this was written, it was pthreads4w-code-v3.0.0.zip. I do it with Powershell on MS Windows with `curl`:

    PS> curl -L "https://sourceforge.net/projects/pthreads4w/files/latest/download" -o ".\pthreads4w-code.zip"
    PS> Expand-Archive -LiteralPath .\pthreads4w-code.zip -DestinationPath .\src\
    PS> Move-Item .\src\pthreads4w-code-*\ .\src\pthreads4w\

Build the library and provide its files. If in doubt look at its README.

    PS> Set-Location .\src\pthreads4w\
    PS> Copy-Item _ptw32.h,pthread.h,semaphore.h,sched.h -Destination ..\..\include\pthreads4w\
    PS> nmake realclean VC-static
    PS> Copy-Item libpthreadVC3.lib ..\..\lib\static\
    PS> nmake realclean VC
    PS> Copy-Item pthreadVC3.dll,pthreadVC3.lib -Destination ..\..\lib\shared\

If in doubt you can optional also run the test suite. Be patient, it takes some time.

    PS> Set-Location .\tests\
    PS> nmake clean VC
    PS> Set-Location ..\

Now you should be able to configure and build the (test) application. To keep things simple I have used this pathnames here so the cmake script isn't very tolerant. Check to use the same paths given here.

    PS> Set-Location ..\..\
    PS> cmake -S . -B build
    PS> cmake --build build --config Release

    PS> .\build\Release\main-static.exe
    DEBUG: return code from pthread_create() is: 0
    Hello World from thread :-)

    PS> Copy-Item .\lib\shared\pthreadVC3.dll .\build\Release\
    PS> .\build\Release\main-shared.exe
    DEBUG: return code from pthread_create() is: 0
    Hello World from thread :-)

If the shared linked program does not find its .dll it will terminate silently. If you do not see the greeting then have a look at the .ddl and ensure that the program can find it. Copying it to the programs directory or to the system directory `Windows\System32` will always do.


## Using POSIX threads on Linux
Linux supports POSIX threads out of the box. We have only to link with the shared `pthread` system library. This is configured with cmake. There is nothing else to be done. Just execute e.g. with bash from the repository source directory:

    ~$ cmake -S . -B build
    ~$ cmake --build build
    ~$ ./build/main
    DEBUG: return code from pthread_create() is: 0
    Hello World from thread :-)

<pre>
// Copyright (C) 2021 GPL 3 and higher by Ingo Höft,  &#60;Ingo&#64;Hoeft-online.de&#62;
// Redistribution only with this Copyright remark. Last modified: 2021-08-19
</pre>
