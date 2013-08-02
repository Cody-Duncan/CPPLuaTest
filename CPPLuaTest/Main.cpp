#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "lua.hpp"

using namespace std;

lua_State *L;  //global lya state pointer
FILE* logFile;


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
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%B-%d.%X", &tstruct);

    return buf;
}

static int report (lua_State *L, int status) {
    const char *msg;
    if (status) 
    {
        msg = lua_tostring(L, -1);                          //get the error message pushed on
        if (msg == NULL) 
            msg = "(error with no message)"; 
        fprintf(stderr, "status=%d, %s\n", status, msg);
        fprintf(logFile, "status=%d, %s\n", status, msg);
        lua_pop(L, 1);                                      //get rid of error message from stack
    }
    return status;
}

/// <summary>
/// Initializes lua_State object, opens and runs script file.
/// </summary>
/// <param name="filename">The filename.</param>
/// <returns>0 if successful, other values for errors</returns>
int initLua(const char* filename)
{
    int err = 0;

    L = luaL_newstate(); //use this for lua (version > 5.1) to create lua_State object
    luaL_openlibs(L);    //open standard lua libraries

    std::cerr << "-- Loading file: " << filename << std::endl;
    err = luaL_loadfile(L, filename);
    report(L, err);

    if ( err == 0 ) 
    {
        // execute Lua program
        err = lua_pcall(L, 0, LUA_MULTRET, 0);
        report(L, err);
    }

    return err;
}


void luaCall()
{
    lua_getglobal(L, "lFunction"); //put function onto stack
    lua_call(L, 0, 0);             //call function
}

/// <summary>
/// Disposes of lua_State object
/// </summary>
void disposeLua()
{
    lua_close(L);
}

int main(int argc, char **argv)
{
    int err;

    logFile = fopen("errorLog.txt", "a");
    fprintf(logFile, "Starting Log: %s\n", currentDateTime().c_str());

    err = initLua("test.lua");
    if(!err)
    {
        luaCall();
        disposeLua();
    }

    fclose(logFile);
    pressKey();
}