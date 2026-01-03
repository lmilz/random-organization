// MIT License
//
// Copyright (c) 2025 Lars Milz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/**
 * @file: Shape.hpp
 * @brief Geometric shapes for Random Organization Simulation
 *
 * This header defines geometric shapes using std::variant for type-safe collision detection without
 * inheritance hierarchy.
 */

#ifndef SHAPE_H
#define SHAPE_H

// Includes
#include <stdexcept>
#include <string>
#include <variant>

#include "Vec.hpp"

/**
 * @brief Data structure for Circles
 *
 * Represents a circle defined by its center position and radius
 */
struct CircleData
{
    Vec position;   ///< Center point of the circle
    double radius;  ///< Radius of the circle

    /**
     * @brief Constructor for CircleData
     * @param pos Center position
     * @param r Radius (must be > 0)
     */
    CircleData(const Vec& pos, double r)
        : position(pos)
        , radius(r)
    {
        if (r <= 0.0) {
            throw std::invalid_argument("Circle radius must be > 0!");
        }
    }
};

/**
 * @brief Data structure for Rectangles
 *
 * Represents a rectangle defined by its center position, width and height.
 */
struct RectangleData
{
    Vec position;   ///< Center point of the rectangle
    double width;   ///< Width of the rectangle
    double height;  ///< Height of the rectangle

    /**
     * @brief Constructor for RectangleData
     * @param pos Center position
     * @param w Width (must be > 0)
     * @param h Height (must be > 0)
     */
    RectangleData(const Vec& pos, double w, double h)
        : position(pos)
        , width(w)
        , height(h)
    {
        if (w <= 0.0 || h <= 0.0) {
            throw std::invalid_argument("Area of rectangle must be positive!");
        }
    }
};

/**
 * @brief Data structure for Squares
 *
 * Represents a square defined by its center position and size.
 */
struct SquareData
{
    Vec position;  ///< Center point of the rectangle
    double size;   ///< Side length of the square

    /**
     * @brief Constructor for SquareData
     * @param pos Center position
     * @param s Size (must be > 0)
     */
    SquareData(const Vec& pos, double s)
        : position(pos)
        , size(s)
    {
        if (size <= 0.0) {
            throw std::invalid_argument("Area of square must be positive!");
        }
    }
};

/**
 * @brief Type-safe container for all shape types
 *
 * A shape can hold one of: CircleData, RectangleData, or SquareData.
 * Use std::visit to operate on the contained type.
 */
using Shape = std::variant<CircleData, RectangleData, SquareData>;

/**
 * @brief Handler for collision detection between all shape type combinations
 *
 * This struct provides operator() overloads for same shape collisions.
 * TODO: Overlap between Circle and Rectangle
 */
struct OverlapHandler
{
    /**
     * @brief Check overlap between two circles
     * @param a First circle
     * @param b Second Circle
     * @return true if circles overlap
     */
    bool operator()(const CircleData& a, const CircleData& b) const
    {
        const Vec kdiff = a.position - b.position;
        double const distance = kdiff.magnitude();

        return distance < (a.radius + b.radius);
    }

    /**
     * @brief Check overlap between two rectangles
     * @param a First rectangle
     * @param b Second rectangle
     * @return true if rectangles overlap
     */
    bool operator()(const RectangleData& a, const RectangleData& b) const
    {
        return a.position.x() < b.position.x() + b.width
               && a.position.x() + a.width > b.position.x()
               && a.position.y() < b.position.y() + b.height
               && a.position.y() + a.height > b.position.y();
    }

    /**
     * @brief Check overlap between two squares
     * @param a First square
     * @param b Second square
     * @return true if squares overlap
     */
    bool operator()(const SquareData& a, const SquareData& b) const
    {
        return a.position.x() < b.position.x() + b.size && a.position.x() + a.size > b.position.x()
               && a.position.y() < b.position.y() + b.size
               && a.position.y() + a.size > b.position.y();
    }

    /**
     * @brief Check overlap between circle and rectangle
     * TODO: Implementation
     * @param c Circle
     * @param r Rectangle
     * @return true if shapes overlap
     */
    bool operator()(const CircleData& /*c*/, const RectangleData& /*r*/) const { return false; }

    /**
     * @brief Check overlap between rectangle and circle (symmetric)
     */
    bool operator()(const RectangleData& r, const CircleData& c) const { return (*this)(c, r); }

    /**
     * @brief Check overlap between circle and square
     */
    bool operator()(const CircleData& c, const SquareData& s) const
    {
        // Convert square to rectangle and reuse logic
        RectangleData const rect(s.position, s.size, s.size);
        return (*this)(c, rect);
    }

    /**
     * @brief Check overlap between square and circle (symmetric)
     */
    bool operator()(const SquareData& s, const CircleData& c) const { return (*this)(c, s); }

    /**
     * @brief Check overlap between rectangle and square
     */
    bool operator()(const RectangleData& r, const SquareData& s) const
    {
        RectangleData const rect(s.position, s.size, s.size);
        return (*this)(r, rect);
    }

    /**
     * @brief Check overlap between square and rectangle (symmetric)
     */
    bool operator()(const SquareData& s, const RectangleData& r) const { return (*this)(r, s); }
};

/**
 * @brief Check if two shapes overlap
 * @param a First shape
 * @param b Second shape
 * @return true if shapes overlap, false otherwise
 */
[[nodiscard]] inline bool overlaps(const Shape& a, const Shape& b)
{
    return std::visit(OverlapHandler{}, a, b);
}

/**
 * @brief Get the position of a shape
 * @param s The shape
 * @return Position vector of the shape's center
 */
[[nodiscard]] inline Vec getPosition(const Shape& s)
{
    return std::visit([](const auto& shape) { return shape.position; }, s);
}

/**
 * @brief Set the position of a shape
 * @param s The shape
 * @param pos New position
 */
inline void setPosition(Shape& s, const Vec& pos)
{
    std::visit([&pos](auto& shape) { shape.position = pos; }, s);
}

/**
 * @brief Move a shape by a displacement vector
 * @param s The shape to move
 * @param delta Displacement vector
 */
inline void move(Shape& s, const Vec& delta)
{
    std::visit([&delta](auto& shape) { shape.position = shape.position + delta; }, s);
}

/**
 * @brief Get the type name of a shape as string
 * @param s The shape
 * @return "Circle", "Rectangle", or "Square"
 */
[[nodiscard]] inline std::string getTypeName(const Shape& s)
{
    return std::visit(
        [](const auto& shape) -> std::string {
            using T = std::decay_t<decltype(shape)>;
            if constexpr (std::is_same_v<T, CircleData>) {
                return "Circle";
            }
            else if constexpr (std::is_same_v<T, RectangleData>) {
                return "Rectangle";
            }
            else {
                return "Square";
            }
        },
        s);
}

#endif  // SHAPE_H
