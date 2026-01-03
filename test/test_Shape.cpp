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

#include <cmath>

#include <gtest/gtest.h>

#include "Shape.hpp"

// =========================================
// Circle-Circle collision test
// =========================================

TEST(CircleCollisionTest, TouchingCircles)
{
    auto c1 = CircleData(Vec(0.0, 0.0), 5.0);
    auto c2 = CircleData(Vec(10.0, 0.0), 5.0);

    EXPECT_FALSE(overlaps(c1, c2));
}

TEST(CircleCollisionTest, OverlappingCircles)
{
    auto c1 = CircleData(Vec(0.0, 0.0), 5.0);
    auto c2 = CircleData(Vec(8.0, 0.0), 5.0);

    EXPECT_TRUE(overlaps(c1, c2));
}

TEST(CircleCollisionTest, SeparatedCircles)
{
    auto c1 = CircleData(Vec(0.0, 0.0), 5.0);
    auto c2 = CircleData(Vec(20.0, 0.0), 5.0);

    EXPECT_FALSE(overlaps(c1, c2));
}

TEST(CircleCollisionTest, ConcentricCircles)
{
    auto c1 = CircleData(Vec(0.0, 0.0), 5.0);
    auto c2 = CircleData(Vec(0.0, 0.0), 3.0);

    EXPECT_TRUE(overlaps(c1, c2));
}

// =========================================
// Rectangle-Rectangle collision test
// =========================================

TEST(RectangleCollisionTest, TouchingRectangles)
{
    auto r1 = RectangleData(Vec(0.0, 0.0), 10.0, 10.0);
    auto r2 = RectangleData(Vec(10.0, 0.0), 10.0, 10.0);
    EXPECT_FALSE(overlaps(r1, r2));
}

TEST(RectangleCollisionTest, OverlappingRectangles)
{
    auto r1 = RectangleData(Vec(0.0, 0.0), 10.0, 10.0);
    auto r2 = RectangleData(Vec(8.0, 0.0), 10.0, 10.0);
    EXPECT_TRUE(overlaps(r1, r2));
}

TEST(RectangleCollisionTest, SeparatedRectangles)
{
    auto r1 = RectangleData(Vec(0.0, 0.0), 10.0, 10.0);
    auto r2 = RectangleData(Vec(20.0, 0.0), 10.0, 10.0);
    EXPECT_FALSE(overlaps(r1, r2));
}

TEST(RectangleCollisionTest, ContainedRectangle)
{
    auto r1 = RectangleData(Vec(0.0, 0.0), 20.0, 20.0);
    auto r2 = RectangleData(Vec(0.0, 0.0), 5.0, 5.0);
    EXPECT_TRUE(overlaps(r1, r2));
}
