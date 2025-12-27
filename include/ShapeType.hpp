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

#ifndef SHAPETYPE_H
#define SHAPETYPE_H

#include <memory>

#include "Shape.hpp"
#include "Vec.hpp"

/**
 * @brief Enumeration of avaiblable shape types
 */
enum class ShapeTypes
{
    Circle,
    Rectangle,
    Square
};

/**
 * @brief Factory for creating shapes
 *
 * Creates shape instances based on the specified type.
 */
class ShapeType
{
   public:
    /**
     * @brief Create a shape of the specified type
     * @param type The Type of the shape to create
     * @param pos Initial position
     * @param size1 Primary size (radius for circle, width for rectangle, side for squre)
     * @param size2 Secondary size (height for rectangle, ignored for others)
     * @return A Shape variant containing the created shape
     */
    static std::unique_ptr<Shape> create(ShapeTypes type,
                                         const Vec& pos,
                                         double size1 = 1.0,
                                         double size2 = 1.0)
    {
        switch (type) {
            case ShapeTypes::Circle:
                return std::make_unique<Circle>(pos, size1);
            case ShapeTypes::Rectangle:
                return std::make_unique<Rectangle>(pos, size1, size2);
            case ShapeTypes::Square:
                return std::make_unique<Square>(pos, size1);
        }
        throw std::invalid_argument("Unknown shape type");
    }
};

#endif  // SHAPETYPE_H
