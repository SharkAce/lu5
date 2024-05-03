#include "loaders.h"
#include <lauxlib.h>

#include "../lu5_logger.h"
#include "../lu5_font.h"

int loadFont(lua_State *L) {
	
	const char *str = luaL_checkstring(L, 1);
	if (!str) {
		luaL_error(L, "Expected first argument to be a string");
		return 0;
	}

	if (lu5_load_font(str)) {
		luaL_error(L, "Could not find font '%s'", str);
		return 0;
	}

	return 0;
}

int loadImage(lua_State *L) {
	return 1;
}

int loadJSON(lua_State *L) {
	return 1;
}

int loadCSV(lua_State *L) {
	return 1;
}

int loadText(lua_State *L) {
	return 1;
}
