#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Vector2.h"

template<class T>
struct Rect
{
    using Vector2 = Vector2<T>;

    Rect(Vector2 topLeft, Vector2 size)
    : pos(topLeft)
    , size(size)
    { }

    Rect() = default;
    Rect(const Rect&) = default;
    Rect(Rect&&) = default;

    // Y directed to down
    template<class U>
    bool IntersectAABB(Rect<U> other) const
    {
        float aX1 = pos.x;
        float aX2 = pos.x + size.x;
        float bX1 = other.pos.x;
        float bX2 = other.pos.x + other.size.x;

        float aY1 = pos.y;
        float aY2 = pos.y + size.y;
        float bY1 = other.pos.y;
        float bY2 = other.pos.y + other.size.y;

        return aX1 < bX2 &&
               aX2 > bX1 &&
               aY1 < bY2 &&
               aY2 > bY1;
    }

    Vector2 GetCenter() const
    {
        return pos + size / 2.0f;
    }

    Vector2 pos{ }; // top left
    Vector2 size{ };
};

template<class T, class U>
bool CheckBottomTopIntersect(const Rect<T>& prev, const Rect<T>& cur, const Rect<U>& target)
{
    return prev.pos.y + prev.size.y <= target.pos.y                 &&
           prev.pos.x               <= target.pos.x + target.size.x &&
           prev.pos.x + prev.size.x >= target.pos.x;
}

using RectI = Rect<int>;
using RectF = Rect<float>;
using RectD = Rect<double>;
using RectU = Rect<unsigned>;


#endif //RECTANGLE_H
