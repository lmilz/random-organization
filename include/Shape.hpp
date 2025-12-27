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
 * This header defines abstract and concrete geometric shapes used in the simulation.
 * Supports circles, squares and rectangles with collision detection.
 */

#ifndef SHAPE_H
#define SHAPE_H

// Includes
#include <cmath>
#include <memory>

#include "Vec.hpp"

/**
 * @brief Abstract base class for all geometric shapes
 *
 * This class defines the interface for all geometric shapes in the simulaton.
 */
class Shape
{
   public:
    /**
     * @brief Constructor
     * @param pos Initial position (center of the shape)
     */
    Shape(Vec pos) : position(pos) {}
    /// Virtual destructor for polymorphic classes
    virtual ~Shape() = default;

    /**
     * @brief Returns the current position
     * @return Position of the shape's center
     */
    Vec getPosition() const { return position; }

    /**
     * @brief Sets the position
     * @param pos New Position
     */
    void setPosition(Vec& pos) { position = pos; }

    /**
     * @brief Moves the shape relatively
     * @param delta Displacement vector
     */
    void move(Vec& delta) { position = position + delta; }

    /**
     * @brief Checks if this shape overlaps with another
     *
     * This method performs a precise collision check considering the specific geometries of both
     * shapes.
     *
     * @param other The other shape
     * @return true if the shapes overlap, false otherwise
     */
    virtual bool overlaps(const Shape& other) const = 0;

   protected:
    Vec position;  ///< Center point of the shape
};

/**
 * @brief Circular particle
 *
 * Represents a circle with position and radius. Collision detection is based on the distance
 * between centers.
 */
class Circle : public Shape
{
   public:
    /**
     * @brief Constructor for circle
     * @param pos Position of the center point
     * @param r Radius (must be > 0)
     */
    Circle(Vec pos, double r);

    /**
     * @brief Returns the radius
     * @return Circle radius
     */
    double getRadius() const { return radius; }

    /// @copydoc Shape::overlaps()
    bool overlaps(const Shape& other) const override;

   private:
    double radius;  ///< Radius of the circle
};

/**
 * @brief Rectangle particle
 *
 * Represents a rectangle aligned parallel to the coordinate axes.
 * Position is the center, width and height define the extent.
 */
class Rectangle : public Shape
{
   public:
    /**
     * @brief Constructor for rectangle
     * @param pos Position of the center point
     * @param w Width (must be > 0)
     * @param h Height (must be > 0)
     */
    Rectangle(Vec pos, double w, double h);

    /**
     * @brief Returns width of the rectangle
     * @return Rectangle width
     */
    double getWidth() const { return width; }

    /**
     * @brief Returns height of the rectangle
     * @return Rectangle height
     */
    double getHeight() const { return height; }

    /// @copydoc Shape::overlaps()
    bool overlaps(const Shape& other) const override;

   protected:
    double width;   ///< Width of the rectangle
    double height;  ///< Height of the rectangle
};

/**
 * @brief Squares as a special case of rectangle
 *
 * A square is a rectangle where width = height.
 */
class Square : public Rectangle
{
   public:
    /**
     * @brief Constructor for square
     * @param pos Position of the center point
     * @param size Side length (must be > 0)
     */
    Square(Vec pos, double size) : Rectangle(pos, size, size) {}
};

#endif  // SHAPE_H
