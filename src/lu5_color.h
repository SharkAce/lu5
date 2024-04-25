#ifndef __COLOR_ARGS_H__
#define __COLOR_ARGS_H__

#include <lua.h>
#include <stdint.h>

#define LU5_RGBA(sr,sg,sb,sa) (lu5_color){ .r=sr, .g=sg, .b=sb, .a=sa }

typedef union
{
	uint32_t hexadecimal;
	uint8_t bytearray[4];

	struct 
	{
		uint8_t a;
		uint8_t b;
		uint8_t g;
		uint8_t r; 
	};
} lu5_color;

typedef struct {
    const char *name;
    lu5_color color;
} lu5_labeled_color;

lu5_color lu5_args_to_color(lua_State *L);

#define LU5_COLOR_COUNT 7
extern lu5_labeled_color lu5_known_colors[LU5_COLOR_COUNT]; 


#endif
