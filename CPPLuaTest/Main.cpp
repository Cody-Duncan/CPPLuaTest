#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include "lua.hpp"

using namespace std;

lua_State *L;  //global lya state pointer

void pressKey()
{
	system("PAUSE");
}

int initLua(const char* filename)
{
    int err = 0;

    L = luaL_newstate(); //use this for lua 5.2.1
    luaL_openlibs(L);

    std::cerr << "-- Loading file: " << filename << std::endl;
    err = luaL_loadfile(L, filename);

    if ( err==0 ) 
    {
      // execute Lua program
      err = lua_pcall(L, 0, LUA_MULTRET, 0);
    }

    return err;
}

void luaCall()
{
    lua_getglobal(L, "lFunction"); //put function onto stack
    lua_call(L, 0, 0);             //call function
}

void disposeLua()
{
    lua_close(L);
}

int main(int argc, char **argv)
{
    int err;

    

    initLua("test.lua");
    luaCall();
	disposeLua();

	pressKey();
}