#ifndef VECTOR2_H
#define VECTOR2_H

#include "Application/Details/Logger.h"


template<class R>
concept Number = std::is_integral_v<R> || std::is_floating_point_v<R>;

template<typename T>
T parse(const std::string_view str) {
    T value = {};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
    if (ec != std::errc() || ptr != str.data() + str.size()) {
        Log("Failed to parse: " + std::string(str));
    }
    return value;
}

template<Number T>
class Vector2
{
public:
    template<class R>
    using CommonValue = std::common_type_t<R, T>;

    template<class R>
    using CommonVector = Vector2<CommonValue<R>>;

    static inline constexpr const char* formatI = "[{:>6}; {:>6}]";
    static inline constexpr const char* formatR = "[{:>6.1f}; {:>6.1f}]";
    static inline const std::regex pattern { R"(\[\s*(-?\d+(?:\.\d+)?)\s*;\s*(-?\d+(?:\.\d+)?)\s*\])" };

public:
    Vector2() = default;
    template <class U>
    Vector2(T x, U y)
    : x(x)
    , y(y)
    { }

    Vector2(const Vector2&) = default;
    Vector2(Vector2&&) = default;

    Vector2(std::string_view serialized)
    {
        std::cmatch match;
        if (!std::regex_match(serialized.begin(), serialized.end(), match, pattern)) {
            Log("Malformed vector string: " + std::string(serialized), Logger::Verbosity::WARNING);
        }

        x = parse<T>(match[1].str());
        y = parse<T>(match[2].str());
    }

    // Useful functions
    double Length() const
    {
        return sqrt(x * x + y * y);
    }

    bool IsZero(float eps = 1e-5) const
    {
        return x * x + y * y < eps * eps;
    }

    Vector2 Unit(double len = 0.0) const
    {
        len = len == 0.0 ? len : Length();
        return Vector2(x / len, y / len);
    }

    template<class R>
    CommonVector<R> Dot(Vector2<R> other) const
    {
        return CommonVector<R>(x * other.x, y * other.y);
    }

    template<class R>
    double AngleRadTo(Vector2<R> other) const
    {
        return acos(Dot(other) / (Length() * other.Length()));
    }

    template<class R>
    double AngleDegreeTo(Vector2<R> other) const
    {
        return angleRadTo(other) / M_PI * 180;
    }

    Vector2& Clamp(double min, double max)
    {
        double len = Length();
        double clamped = std::clamp(len, min, max);
        if (clamped < len)
        {
            *this = Unit(len) * min;
        } else if (clamped > len)
        {
            *this = Unit(len) * max;
        }

        return *this;
    }


    // Operators
    Vector2& operator=(const Vector2&) = default;
    Vector2& operator=(Vector2&&) = default;

    template<class R>
    Vector2& operator=(const Vector2<R>& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    template<class R>
    Vector2& operator=(Vector2<R>&& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    Vector2 operator -() const
    {
        return { -x, -y };
    }

    template<class R>
    CommonVector<R> operator+(const Vector2<R> rhs) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    template<class R>
    CommonVector<R> operator-(const Vector2<R> rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    template<class R>
    CommonVector<R> operator*(const Vector2<R> rhs) const
    {
        return { x * rhs.x, y * rhs.y };
    }

    template<class R>
    CommonVector<R> operator/(const Vector2<R> rhs) const
    {
        return { x / rhs.x, y / rhs.y };
    }


    template<class R>
    CommonVector<R> operator*(const R rhs) const
    {
        return { x * rhs, y * rhs };
    }

    template<class R>
    CommonVector<R> operator/(R rhs) const
    {
        return { x / rhs, y / rhs };
    }

    template<class R>
    operator Vector2<R>() const
    {
        return Vector2<R>(static_cast<R>(x), static_cast<R>(y));
    }

    template<typename R>
    bool operator==(const Vector2<R>& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    template<class R>
    Vector2 operator+=(Vector2<R> rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<class R>
    Vector2 operator-=(Vector2<R> rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<class R>
    Vector2 operator*=(Vector2<R> rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    template<class R>
    Vector2 operator*=(R value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    template<class R>
    Vector2 operator/=(Vector2<R> rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    inline operator std::string() const
    {
        if constexpr (std::is_integral_v<T>)
        {
            return std::format(formatI, x, y);
        } else
        {
            return std::format(formatR, x, y);
        }
    }

public:
    T x = 0, y = 0;
};

template<class T, class R>
Vector2<T>::CommonVector<R> operator-(const R lhs, Vector2<T> rhs)
{
    return rhs - lhs;
}

template<class T, class R>
Vector2<T>::CommonVector<R> operator*(const R lhs, Vector2<T> rhs)
{
    return rhs * lhs;
}

template<class T, class R>
Vector2<T>::CommonVector<R> operator/(const R lhs, Vector2<T> rhs)
{
    return rhs / lhs;
}

template <class T>
struct std::formatter<Vector2<T>> {
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const Vector2<T>& v, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{}", std::string(v));
    }
};


using Vector2u = Vector2<unsigned>;
using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;


namespace rfl {
    template<class T>
    struct Reflector<Vector2<T>> {
        using ReflType = std::string;

        static Vector2<T> to(const ReflType& vString) noexcept {
            return {vString};
        }

        static ReflType from(const Vector2<T>& v) {
            return std::string(v);
        }
    };
}


#endif //VECTOR2_H
