@echo off
:: Touch 在 Windows 下的简单实现
:: https://helloacm.com
 
setlocal
set CreateFiles=True
 
:start
    if %1.==. goto :end
    if "%1"=="-c" (
        set CreateFiles=False
        shift
        goto :start
    )
    if exist "%1" (
        copy /b "%1" +,, > nul
    ) else (
        if "%CreateFiles%"=="True" (
            type nul > "%1" 
        )       
    )
    shift
    goto start
 
:end
endlocal
