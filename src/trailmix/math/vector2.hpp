// math/vector2.hpp -- The Vector2 struct provides a simple way of storing and sharing 2D coordinates.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <functional>
#include <initializer_list>
#include <string>

#include "trailmix/internal/hash_combine.hpp"

namespace trailmix::math {

struct Vector2u;    // Forward declaration, for explicit conversion of Vector2 to Vector2u.

// Simple two-dimensional integer coordinate struct.
struct Vector2
{
    Vector2() : x(0), y(0) { }
    Vector2(int32_t vx, int32_t vy) : x(vx), y(vy) { }
    Vector2(std::initializer_list<int32_t> list)
    {
        auto it = list.begin();
        x = (it != list.end()) ? *it++ : 0;
        y = (it != list.end()) ? *it : 0;
    }

    Vector2     operator+(const Vector2 &other) const { return { x + other.x, y + other.y }; }
    Vector2     operator-(const Vector2 &other) const { return { x - other.x, y - other.y }; }
    Vector2     operator/(const Vector2 &other) const { return { x / other.x, y / other.y }; }
    Vector2     operator*(const Vector2 &other) const { return { x * other.x, y * other.y }; }
    Vector2     operator%(const Vector2 &other) const { return { x % other.x, y % other.y }; }
    bool        operator==(const Vector2 &other) const { return (x == other.x && y == other.y); }
    bool        operator!=(const Vector2 &other) const { return (x != other.x || y != other.y); }
    bool        operator!() const { return (x == 0 && y == 0); }
    bool        operator>(const Vector2 &other) const { return (x > other.x && y > other.y); }
    bool        operator<(const Vector2 &other) const { return (x < other.x || y < other.y); }
    explicit    operator bool() const { return (x != 0 || y != 0); }

    template<typename T> Vector2    operator/(const T other) const { return {x / other, y / other}; }
    template<typename T> Vector2    operator*(const T other) const { return {x * other, y * other}; }
    template<typename T> Vector2    operator%(const T other) const { return {x % other, y % other}; }

    explicit operator Vector2u() const noexcept;    // Allows Vector2 to static_cast into Vector2 (beware of signed -> unsigned integer conversions)

    // Allows this Vector2 to return its coordinates in string form.
    const std::string   string() const { return std::to_string(x) + "," + std::to_string(y); }

    int32_t x, y;
};

// As above, but for explicitly unsigned integer vectors.
struct Vector2u
{
    Vector2u() : x(0), y(0) { }
    Vector2u(uint32_t vx, uint32_t vy) : x(vx), y(vy) { }
    Vector2u(std::initializer_list<uint32_t> list)
    {
        auto it = list.begin();
        x = (it != list.end()) ? *it++ : 0;
        y = (it != list.end()) ? *it : 0;
    }

    Vector2u    operator+(const Vector2u &other) const { return { x + other.x, y + other.y }; }
    Vector2u    operator-(const Vector2u &other) const { return { x - other.x, y - other.y }; }
    Vector2u    operator/(const Vector2u &other) const { return { x / other.x, y / other.y }; }
    Vector2u    operator*(const Vector2u &other) const { return { x * other.x, y * other.y }; }
    Vector2u    operator%(const Vector2u &other) const { return { x % other.x, y % other.y }; }
    bool        operator==(const Vector2u &other) const { return (x == other.x && y == other.y); }
    bool        operator!=(const Vector2u &other) const { return (x != other.x || y != other.y); }
    bool        operator!() const { return (x == 0 && y == 0); }
    bool        operator>(const Vector2u &other) const { return (x > other.x && y > other.y); }
    bool        operator<(const Vector2u &other) const { return (x < other.x || y < other.y); }
    explicit    operator bool() const { return (x != 0 || y != 0); }

    template<typename T> Vector2u   operator/(const T other) const { return {x / other, y / other}; }
    template<typename T> Vector2u   operator*(const T other) const { return {x * other, y * other}; }
    template<typename T> Vector2u   operator%(const T other) const { return {x % other, y % other}; }

    // Allows implicit conversion of Vector2u into Vector2 (beware of unsigned -> signed integer conversions)
    operator Vector2() const noexcept { return { static_cast<int32_t>(x), static_cast<int32_t>(y) }; }

    // Allows this Vector2u to return its coordinates in string form.
    const std::string   string() const { return std::to_string(x) + "," + std::to_string(y); }

    uint32_t x, y;
};

}   // namespace trailmix::math

// specialise std::hash
namespace std {
using trailmix::internal::hash_combine;
template <> struct hash<trailmix::math::Vector2>
{
    std::size_t operator()(const trailmix::math::Vector2& v) const noexcept
    {
        std::size_t seed = 0;
        hash_combine(seed, std::hash<int32_t>{}(v.x));
        hash_combine(seed, std::hash<int32_t>{}(v.y));
        return seed;
    }
};
template <> struct hash<trailmix::math::Vector2u>
{
    std::size_t operator()(const trailmix::math::Vector2u& v) const noexcept
    {
        std::size_t seed = 0;
        hash_combine(seed, std::hash<uint32_t>{}(v.x));
        hash_combine(seed, std::hash<uint32_t>{}(v.y));
        return seed;
    }
};
}   // namespace std
