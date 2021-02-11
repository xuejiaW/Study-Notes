echo %1
cd %1

IF "%2" == "run" ( 
    "C:\Program Files\Git\bin\sh.exe" --login -i -c "mingw32-make run"
    goto end
)

IF "%2" == "all" ( 
    "C:\Program Files\Git\bin\sh.exe" --login -i -c "mingw32-make all"
    goto end
)

IF "%2" == "clean" ( 
    "C:\Program Files\Git\bin\sh.exe" --login -i -c "mingw32-make clean"
    goto end
)

"C:\Program Files\Git\bin\sh.exe" --login -i -c "mingw32-make run"

:end