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
 * @file Vec.hpp
 * @brief 2D vector mathematics utility class
 *
 * Provides a simple 2D vector class with basic operations
 * (addition, subtraction, scalar multiplication, magnitude, normalization).
 */

#ifndef VEC_H
#define VEC_H

// Includes
#include <array>
#include <cmath>

class Vec
{
   public:
    /**
     * @brief Default constructor: Initializes all components (x, y) to 0.0
     */
    constexpr Vec()
        : v_{0.0, 0.0}
    {
    }

    /**
     * @brief Parameterized constructor: Initializes the vector components with the given values
     * @param x: Value for the x component
     * @param y: Value for the y component
     */
    constexpr Vec(double x, double y)
        : v_{x, y}
    {
    }

    /**
     * @brief Getter for the x component of the vector
     * @return: The x component of the vector
     */
    [[nodiscard]] constexpr double x() const { return v_[0]; }

    /**
     * @brief Getter for the y component of the vector
     * @return: The y component of the vector
     */
    [[nodiscard]] constexpr double y() const { return v_[1]; }

    /**
     * @brief Operator overloading for vector addition
     * @param other: The vector to be added to this vector
     * @return: A new vector that is the result of the addition
     */
    [[nodiscard]] constexpr Vec operator+(const Vec& vec) const
    {
        return {v_[0] + vec.x(), v_[1] + vec.y()};
    }

    /**
     * Operator overloading for vector subtraction
     * @param other: The vector to be subtracted from this vector
     * @return: A new vector that is the result of the subtraction
     */
    [[nodiscard]] constexpr Vec operator-(const Vec& vec) const
    {
        return {v_[0] - vec.x(), v_[1] - vec.y()};
    }

    /**
     * @brief Operator overloading for scalar multiplication
     * @param scalar: The scalar value by which the vector is multiplied
     * @return: A new vector that is the result of the scalar multiplication
     */
    [[nodiscard]] constexpr Vec operator*(double scalar) const
    {
        return {v_[0] * scalar, v_[1] * scalar};
    }

    /**
     * @brief Computes the magnitude (length) of the vector
     * @return: A double value representing the magnitude of the vector
     */
    [[nodiscard]] double magnitude() const { return std::sqrt((v_[0] * v_[0]) + (v_[1] * v_[1])); }

    /**
     * @brief Normalizes the vector, i.e., scales it so that its length is 1
     *
     * If the vector is a zero vector, the same zero vector is returned
     *
     * @return: A new vector that is normalized
     */
    [[nodiscard]] Vec normalize() const
    {
        const double kmag = magnitude();
        if (kmag == 0.0) {
            return {};
        }

        return *this * (1.0 / kmag);
    }

   private:
    std::array<double, 2> v_;  ///< Vector components
};

#endif  // VEC_H
