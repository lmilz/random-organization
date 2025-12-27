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

#ifndef VEC_H
#define VEC_H

#include <iostream>

class Vec
{
   public:
    // Default constructor: Initializes all components (x, y) to 0.0.
    Vec()
    {
        v[0] = 0.0;
        v[1] = 0.0;
    }

    // Parameterized constructor: Initializes the vector components with the given values.
    // @param x: Value for the x component.
    // @param y: Value for the y component.
    Vec(double x, double y)
    {
        v[0] = x;
        v[1] = y;
    }

    // Getter for the x component of the vector.
    // @return: The x component of the vector.
    double X() const;

    // Getter for the y component of the vector.
    // @return: The y component of the vector.
    double Y() const;

    // Operator overloading for vector addition.
    // @param other: The vector to be added to this vector.
    // @return: A new vector that is the result of the addition.
    Vec operator+(const Vec& vec) const;

    // Operator overloading for vector subtraction.
    // @param other: The vector to be subtracted from this vector.
    // @return: A new vector that is the result of the subtraction.
    Vec operator-(const Vec& vec) const;

    // Operator overloading for scalar multiplication.
    // @param scalar: The scalar value by which the vector is multiplied.
    // @return: A new vector that is the result of the scalar multiplication.
    Vec operator*(double scalar) const;

    // Computes the magnitude (length) of the vector.
    // @return: A double value representing the magnitude of the vector.
    double Magnitude() const;

    // Normalizes the vector, i.e., scales it so that its length is 1.
    // If the vector is a zero vector, the same zero vector is returned.
    // @return: A new vector that is normalized.
    Vec Normalize() const;

   private:
    double v[2];  // Private member for the vector components v[0] = x and v[1] = y.
};

#endif  // VEC_H
