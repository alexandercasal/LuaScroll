/********************************************************
* FILE        : luascroll.h
* AUTHOR      : Alexander Casal
* DESCRIPTION : Read and parse data from a lua script (.lua)
*               Data can be easily retrieved using at(key);
*               where 'key' is the table path to the data.
*
*               EXAMPLE: int windowWidth = myScript.at<int>("window.size.x");
*******************************************************/
#ifndef _LUASCROLL_H
#define _LUASCROLL_H
#include "luaexeption.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include <memory>
#include <string>
#include <cassert>

namespace LSE
{
	// Redirect Lua from terminating at a lua_panic error and throw exception instead
	int sendError(lua_State * state);

	/*-------------------------------------------------------
	* CLASS       : LuaScroll
	* DESCRIPTION : Opens a .lua script file and retrieves the
	*               specified data
	* METHODS     : LuaScroll(string)              - Initializes Lua and opens the script
	*               LuaScroll(&LuaScroll)          - Opens the same Lua script in a new LuaScroll
	*               ~LuaScroll()                   - Clean up memory
	*               setFile                        - Open and read from a new Lua script
	*               getFile                        - Returns the file name of the current Lua script
	*               at                             - Returns the value stored in a particular table value
	*               =                              - Assigns a LuaScroll object the same script file
	*               
	*               get                            - Internal. Returns the value stored in a variable with the specified type
	*--------------------------------------------------------*/
	class LuaScroll
	{
	public:
		LuaScroll(const std::string fileName);
		LuaScroll(const LuaScroll & rhs);
		~LuaScroll();

		void setFile(const std::string fileName);
		std::string getFile() const;

		template <typename T>
		T at(std::string key);

		LuaScroll & operator=(const LuaScroll & rhs);

	private:
		bool addToStack(const int tableNum, const std::string subKey);
		template <typename T>
		T get();

		std::unique_ptr<lua_State, void(*)(lua_State *)> m_luaState;
		std::string m_fileName;
	};
	#include "luascroll.inl"
}

#endif // end _LUASCROLL_H