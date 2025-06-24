#pragma once

#include <ostream>
#include "raylib.h"

inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    return { v1.x + v2.x, v1.y + v2.y };
}

inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    return { v1.x - v2.x, v1.y - v2.y };
}

inline Vector2 operator*(float val, const Vector2& vec2)
{
    return { vec2.x* val, vec2.y* val };
}

inline Vector2 operator*(const Vector2& vec2, float val)
{
    return { vec2.x* val, vec2.y* val };
}

inline bool operator==(const Vector2& v1, const Vector2& v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

inline bool operator!=(const Vector2& v1, const Vector2& v2)
{
    return !(v1 == v2);
}

inline std::ostream& operator<<(std::ostream& stream, const Vector2& vec2)
{
    stream << vec2.x << ", " << vec2.y;
    return stream;
}
