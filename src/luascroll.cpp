/********************************************************
* FILE        : luascroll.cpp
* AUTHOR      : Alexander Casal
* DESCRIPTION : Read and parse data from a lua script (.lua)
*               Data can be easily retrieved using at(key);
*               where 'key' is the table path to the data.
*
*               EXAMPLE: int windowWidth = myScript.at<int>("window.size.x");
*******************************************************/
#include "luascroll.h"

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : Constructor
* DESCRIPTION : Initializes Lua and opens the script
*--------------------------------------------------------*/
LSE::LuaScroll::LuaScroll(const std::string fileName)
	: m_fileName(fileName)
	, m_luaState(luaL_newstate(), lua_close)
{
	lua_atpanic(m_luaState.get(), LSE::sendError);

	if (luaL_dofile(m_luaState.get(), m_fileName.c_str()))
	{
		sendError(m_luaState.get());
	}

	luaL_openlibs(m_luaState.get());
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : Copy Constructor
* DESCRIPTION : Opens the same Lua script in a new LuaScroll
*--------------------------------------------------------*/
LSE::LuaScroll::LuaScroll(const LSE::LuaScroll & rhs)
	: m_fileName(rhs.m_fileName)
	, m_luaState(luaL_newstate(), lua_close)
{
	lua_atpanic(m_luaState.get(), LSE::sendError);

	if (luaL_dofile(m_luaState.get(), m_fileName.c_str()))
	{
		sendError(m_luaState.get());
	}

	luaL_openlibs(m_luaState.get());
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : Destructor
* DESCRIPTION : Clean up memory
*--------------------------------------------------------*/
LSE::LuaScroll::~LuaScroll()
{
	// empty
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : setFile
* DESCRIPTION : Open and read from a new Lua script
*--------------------------------------------------------*/
void LSE::LuaScroll::setFile(const std::string fileName)
{
	assert(!fileName.empty());
	m_fileName = fileName;

	if (luaL_dofile(m_luaState.get(), m_fileName.c_str()))
	{
		sendError(m_luaState.get());
	}
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : getFile
* DESCRIPTION : Returns the file name of the current Lua script
*--------------------------------------------------------*/
std::string LSE::LuaScroll::getFile() const
{
	return m_fileName;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : Assignment Operator
* DESCRIPTION : Assigns a LuaScroll object the same script file
*--------------------------------------------------------*/
LSE::LuaScroll & LSE::LuaScroll::operator=(const LSE::LuaScroll & rhs)
{
	setFile(rhs.getFile());
	return *this;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : addToStack
* DESCRIPTION : Add a table value to the Lua stack and
*               determine if it's a valid value
*--------------------------------------------------------*/
bool LSE::LuaScroll::addToStack(const int tableNum, const std::string subKey)
{
	if (tableNum == 0)
	{
		// push first table onto the Lua stack
		lua_getglobal(m_luaState.get(), subKey.c_str());
	}
	else
	{
		// push sub table onto the Lua stack
		lua_getfield(m_luaState.get(), -1, subKey.c_str());
	}

	if (lua_isnoneornil(m_luaState.get(), -1))
	{
		// Non-existant value or invalid key
		lua_pop(m_luaState.get(), 1);
		return false;
	}

	return true;
}

/*-------------------------------------------------------
* METHOD      : sendError
* DESCRIPTION : Redirect Lua from terminating at a lua_panic error and call exception instead
*--------------------------------------------------------*/
int LSE::sendError(lua_State * state)
{
	std::string errorMessage = "Lua Error: ";
	errorMessage.append(lua_tostring(state, -1));
	lua_pop(state, 1);
	throw LSE::LuaException(errorMessage.c_str());
	return 0;
}