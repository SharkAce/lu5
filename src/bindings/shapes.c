#include "shapes.h"

#include "../window.h"

#include <lauxlib.h>
#include <math.h>
#define PI 3.14159265358979323846

int circle(lua_State *L) {
    double x = lua_tonumber(L, 1);  
    double y = lua_tonumber(L, 2);  
    double d = lua_tonumber(L, 3);  

    float radius = d / 2.0f;
    float angleStep = 2 * PI / LU5_CIRCLE_SEGMENTS;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    
    for (int i = 0; i <= LU5_CIRCLE_SEGMENTS; i++) {
        float angle = angleStep * i;
        float x_offset = radius * cos(angle);
        float y_offset = radius * sin(angle);

        glVertex2f(x + x_offset, y + y_offset);
    }

    glEnd();

    return 0;
}

int square(lua_State *L)
{
    double x = lua_tonumber(L, 1);  
    double y = lua_tonumber(L, 2);  
    double s = lua_tonumber(L, 3);  

    float x2 = x + s;
    float y2 = y + s;

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x2, y);
        glVertex2f(x2, y2);
        glVertex2f(x, y2);
    glEnd(); 

    return 0;
}

int rect(lua_State *L) {
    double x = lua_tonumber(L, 1);  
    double y = lua_tonumber(L, 2);  
    double w = lua_tonumber(L, 3);  

    double h = w;
    if (lua_gettop(L) > 3) {
        h = lua_tonumber(L, 4);
    }  

    float x2 = x + w;
    float y2 = y + h;

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x2, y);
        glVertex2f(x2, y2);
        glVertex2f(x, y2);
    glEnd(); 

    return 0;
}

int line(lua_State *L) 
{
    double x1 = lua_tonumber(L, 1);
    double y1 = lua_tonumber(L, 2);
    double x2 = lua_tonumber(L, 3);
    double y2 = lua_tonumber(L, 4);

    int segments = 20;  // More segments = rounder circle
    float angleStep = (2 * PI) / segments;
    float radius = (float)lu5.style.strokeWeight / 2.0f;

    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = x1 + cos(angle) * radius;
        float y = y1 + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x2, y2);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = x2 + cos(angle) * radius;
        float y = y2 + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();


    return 0;
}

int text(lua_State *L)
{
    const char *str = luaL_checkstring(L, 1);
    if (!str) {
        luaL_error(L, "Expected a string argument");
        return 0;
    }

    double x = lua_tonumber(L, 2);
    double y = lua_tonumber(L, 3);

    luaL_error(L, "TODO: Implement text.\t text(\"%s\", %f, %f);", str, x, y);
    return 0;
}

int point(lua_State *L)
{
    double x = lua_tonumber(L, 1);
    double y = lua_tonumber(L, 2);

    luaL_error(L, "TODO: Implement point.\t point(%f, %f);", x, y);
    return 0;
}

int quad(lua_State *L)
{
    double x1 = lua_tonumber(L, 1);
    double y1 = lua_tonumber(L, 2);
    // ... more arguments
    // refer to https://p5js.org/reference/#/p5/quad

    luaL_error(L, "TODO: Implement quad.\t quad(%f, %f, ...more args);", x1, y1);
    return 0;
}

int triangle(lua_State *L)
{
    double x1 = lua_tonumber(L, 1);
    double y1 = lua_tonumber(L, 2);
    // ... more arguments
    // refer to https://p5js.org/reference/#/p5/triangle

    luaL_error(L, "TODO: Implement triangle.\t triangle(%f, %f, ...more args);", x1, y1);
    return 0;
}

int ellipse(lua_State *L)
{
    double x = lua_tonumber(L, 1);
    double y = lua_tonumber(L, 2);
    // ... more arguments
    // refer to https://p5js.org/reference/#/p5/ellipse

    luaL_error(L, "TODO: Implement ellipse.\t ellipse(%f, %f, ...more args);", x, y);
    return 0;
}


int arc(lua_State *L)
{
    double x = lua_tonumber(L, 1);
    double y = lua_tonumber(L, 2);
    // ... more arguments
    // refer to https://p5js.org/reference/#/p5/arc

    luaL_error(L, "TODO: Implement arc.\t arc(%f, %f, ...more args);", x, y);
    return 0;
}
