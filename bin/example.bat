@echo off
setlocal ENABLEDELAYEDEXPANSION
if not "%1" == "" goto :%1

start "Thread 1" /b %~nx0 thread1
start "Thread 2" /b %~nx0 thread2

:main #main
    set counter_1=0
    set counter_2=0
    BAThreads global counter_1 -f
    BAThreads global counter_2 -f
    :loop
        call :updateThread main
    if not !counter_1! GTR 19 (
        if not !counter_2! GTR 29 goto :loop
    )
    echo Finished at %counter_1% and !counter_2!
exit /b

:thread1 #thread
    call :updateThread thread1
    for /L %%i in (1,1,20) do (
        set /a counter_1+=1
        BAThreads global counter_1 -f
        echo Thread 1: Counter = !counter_1!
    )
echo Finished Thread 1 at !counter_1!
taskkill /fi "WindowTitle eq Thread 1" >NUL 2>&1
goto :EOF

:thread2 #thread
    call :updateThread thread2
    for /L %%i in (1,1,30) do (
        set /a counter_2+=1
        BAThreads global counter_2 -f
        echo Thread 2: Counter = !counter_2!
    )
    echo Finished Thread 2 at !counter_2!
taskkill /fi "WindowTitle eq Thread 2" >NUL 2>&1
goto :EOF

:updateThread <thread name>
    for /f "delims=" %%a in ('BAThreads update') DO (
        %%a
    )
goto :EOF



pause > NUL