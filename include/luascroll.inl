/********************************************************
* FILE        : luascroll.inl
* AUTHOR      : Alexander Casal
* DESCRIPTION : Read and parse data from a lua script (.lua)
*               Data can be easily retrieved using at(key);
*               where 'key' is the table path to the data.
*
*               EXAMPLE: int windowWidth = myScript.at<int>("window.size.x");
*******************************************************/

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : at
* DESCRIPTION : Returns the value stored in a particular table value
*--------------------------------------------------------*/
template <typename T>
T LSE::LuaScroll::at(std::string key)
{
	assert(!key.empty());

	unsigned int posStart = 0;
	unsigned int posEnd = 0;
	unsigned int tableNum = 0;
	std::string subKey;

	for (auto it = key.begin(); it != key.end(); ++it)
	{
		if (*it == '.')
		{
			subKey = key.substr(posStart, (posEnd - posStart));
			if (!addToStack(tableNum, subKey))
			{
				return false;
			}

			++tableNum;
			++posEnd;
			posStart = posEnd;
			continue;
		}

		++posEnd;
	}

	subKey = key.substr(posStart, (posEnd - posStart));
	if (!addToStack(tableNum, subKey))
	{
		return 0;
	}

	T value = get<T>();
	lua_pop(m_luaState.get(), lua_gettop(m_luaState.get()));
	return value;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : returnType<>
* DESCRIPTION : Trying to get an unsupported type will result
*               in returning 0
*--------------------------------------------------------*/
template <typename T>
T LSE::LuaScroll::get()
{
	return 0;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : returnType<bool>
* DESCRIPTION : Returns the bool stored in a lua variable
*--------------------------------------------------------*/
template <>
inline bool LSE::LuaScroll::get()
{
	bool value = (lua_toboolean(m_luaState.get(), -1) != 0);
	lua_pop(m_luaState.get(), 1);
	return value;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : returnType<int>
* DESCRIPTION : Returns the int stored in a lua variable
*--------------------------------------------------------*/
template <>
inline int LSE::LuaScroll::get()
{
	int value = static_cast<int>(lua_tointeger(m_luaState.get(), -1));
	lua_pop(m_luaState.get(), 1);
	return value;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : returnType<float>
* DESCRIPTION : Returns the float stored in a lua variable
*--------------------------------------------------------*/
template <>
inline float LSE::LuaScroll::get()
{
	float value = static_cast<float>(lua_tonumber(m_luaState.get(), -1));
	lua_pop(m_luaState.get(), 1);
	return value;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : returnType<double>
* DESCRIPTION : Returns the double stored in a lua variable
*--------------------------------------------------------*/
template <>
inline double LSE::LuaScroll::get()
{
	double value = static_cast<double>(lua_tonumber(m_luaState.get(), -1));
	lua_pop(m_luaState.get(), 1);
	return value;
}

/*-------------------------------------------------------
* CLASS       : LuaScroll
* METHOD      : returnType<string>
* DESCRIPTION : Returns the string stored in a lua variable
*--------------------------------------------------------*/
template <>
inline std::string LSE::LuaScroll::get()
{
	std::string value = static_cast<std::string>(lua_tostring(m_luaState.get(), -1));
	lua_pop(m_luaState.get(), 1);
	return value;
}