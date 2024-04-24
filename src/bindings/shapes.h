#ifndef __LU5_SHAPE_BINDINGS__
#define __LU5_SHAPE_BINDINGS__

#include <lua.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

#define LU5_CIRCLE_SEGMENTS 36
/**
 * Draw a circle to the opengl context
 * 
 * @param L  
 *
 * @param x The x position of the circle's center 
 * @param y The y position of the circle's center
 * @param d The diameter of the circle
 *
 * @return int 
 */
int circle(lua_State *L);

/**
 * Draw a rectangle to the opengl context
 * 
 * @param L  
 *
 * @param x The x position of the reactangle's top left corner
 * @param y The y position of the reactangle's top left corner
 * @param w The width
 * @param h The height
 *
 * @return int 
 */
int rect(lua_State *L);

/**
 * Draw a square to the opengl context
 * 
 * @param L  
 *
 * @param x The x position of the square's top left corner
 * @param y The y position of the square's top left corner
 * @param s The size of the square's sides
 *
 * @return int 
 */
int square(lua_State *L);

/**
 * Draw a line to the opengl context
 * 
 * @param L 
 * @return int 
 */
int line(lua_State *L);

/**
 * Draw text on the opengl context
 * 
 * @param L
 *
 * @param s Text string
 * @param x position of the text
 * @param y position of the text
 * @return int 
 */
int text(lua_State *L);

/**
*/ 
int point(lua_State *L);

/**
*/ 
int arc(lua_State *L);

/**
*/ 
int ellipse(lua_State *L);

/**
*/ 
int triangle(lua_State *L);

/**
*/ 
int quad(lua_State *L);

#endif
