# LuaScroll
I'm planning on using Lua for the configuration files in a game I'm working on. LuaScroll allows me to easily access data from the Lua script and import it into my C++ code. Currently all it does is grab a single value from a Lua variable. This includes accessing variables within a table.

As I learn more about Lua and its C API, I'll be adding more features as needed.

#Usage
LuaScroll accesses variables similarly to how the Lua interpreter accesses them. Take the following script for example:
`Window = {
   Size = {
      x = 500
    }
  }`

In the Lua interpreter I would type: `'Window.Size.x'` to get the value 500.
Similarly, using the LuaScroll class I can access it like so: `int windowWidth = scroll.at<int>("Window.Size.x");`

#Dependencies
LuaScroll uses Lua 5.3.1 (http://www.lua.org/).

Documentation on Lua can be found here:
http://www.lua.org/manual/5.3/

#License
The zlib/libpng License

Copyright (c) 2015 Alexander Casal

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
