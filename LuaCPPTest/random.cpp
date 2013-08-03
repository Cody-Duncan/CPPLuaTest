#include "random.h"


int luaopen_DiceRand(lua_State* L)
{
    luaL_newlib( L, diceRandLib );
    return 1;
}