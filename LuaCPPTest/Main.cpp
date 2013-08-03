#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "lua.hpp"
#include "LuaScript.h"
#include "random.h"

using namespace std;

/// <summary>
/// Gets the current date and time in YYYY-MM-DD.HH:mm:ss format
/// </summary>
/// <returns>current date and time</returns>
const string currentDateTime() 
{
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

    //create log file
    FILE* logFile = fopen("errorLog.txt", "a");
    fprintf(logFile, "Starting Log: %s\n", currentDateTime().c_str());

    //create lua script
    LuaScript script(logFile);

    //run lua script
    script.loadLua();
    script.openLibrary("DiceRand", luaopen_DiceRand);

    err = script.runScript("test.lua");

    //close it if initialized succesfully
    if(!err)
    {
        script.close();
    }

    //close log file
    fclose(logFile);

    system("PAUSE");
}