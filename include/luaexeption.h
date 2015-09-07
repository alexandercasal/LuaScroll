/********************************************************
* FILE        : luaexception.h
* AUTHOR      : Alexander Casal
* DESCRIPTION : Throw Lua errors as a LuaException (runtime_error)
*******************************************************/
#ifndef _LUAEXCEPTION_H
#define _LUAEXCEPTION_H
#include <stdexcept>

namespace LSE
{
	class LuaException : public std::runtime_error
	{
	public:
		LuaException(const char * msg) : std::runtime_error(msg) {}
	};
}

#endif // end _LUAEXCEPTION_H