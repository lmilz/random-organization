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
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE W:uARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/**
 * @file Shape.cpp
 * @brief Implementation of Shape classes
 */

#include "Shape.hpp"

Circle::Circle(Vec pos, double r) : Shape(pos), radius(r)
{
}

Rectangle::Rectangle(Vec pos, double w, double h) : Shape(pos), width(w), height(h)
{
}

bool Circle::overlaps(const Shape& other) const
{
    const Circle* otherCircle = dynamic_cast<const Circle*>(&other);

    Vec diff = position - otherCircle->getPosition();
    double distance = diff.Magnitude();

    return distance < (radius + otherCircle->getRadius());
}

bool Rectangle::overlaps(const Shape& other) const
{
    const Rectangle* otherRectangle = dynamic_cast<const Rectangle*>(&other);

    return (position.X() < otherRectangle->getPosition().X() + otherRectangle->getWidth()
            && position.X() + width > otherRectangle->getPosition().X()
            && position.Y() < otherRectangle->getPosition().Y() + otherRectangle->getHeight()
            && position.Y() + height > otherRectangle->getPosition().Y());
}
