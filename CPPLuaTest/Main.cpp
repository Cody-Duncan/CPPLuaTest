#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "lua.hpp"
#include "LuaScript.h"

using namespace std;


/// <summary>
/// Messages the user "Press any key to continue"
/// </summary>
void pressKey()
{
    system("PAUSE");
}


/// <summary>
/// Gets the current date and time in YYYY-MM-DD.HH:mm:ss format
/// </summary>
/// <returns>current date and time</returns>
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y-%B-%d.%X", &tstruct);

    return buf;
}

int main(int argc, char **argv)
{
    int err;

    
    FILE* logFile = fopen("errorLog.txt", "a");
    fprintf(logFile, "Starting Log: %s\n", currentDateTime().c_str());

    LuaScript script(logFile);

    err = script.initialize("test.lua");
    if(!err)
    {
        cout << script.callVoidFunctionInt("lFunction") << endl;
        script.close();
    }

    

    fclose(logFile);
    pressKey();
}