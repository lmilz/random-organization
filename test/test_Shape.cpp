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

#include <gtest/gtest.h>
#include <cmath>        

#include "Shape.hpp"

// =========================================
// Circle-Circle collision test
// =========================================

TEST(CircleCollisionTest, TouchingCircles) {
    Circle c1(Vec(0.0, 0.0), 5.0);
    Circle c2(Vec(10.0, 0.0), 5.0);

    EXPECT_FALSE(c1.overlaps(c2));
}

TEST(CircleCollisionTest, OverlappingCircles) { 
    Circle c1(Vec(0.0, 0.0), 5.0);
    Circle c2(Vec(8.0, 0.0), 5.0);

    EXPECT_TRUE(c1.overlaps(c2));
}

TEST(CircleCollisionTest, SeparatedCircles) {
    Circle c1(Vec(0.0, 0.0), 5.0);
    Circle c2(Vec(20.0, 0.0), 5.0);

    EXPECT_FALSE(c1.overlaps(c2));
}

TEST(CircleCollisionTest, ConcentricCircles) {
    Circle c1(Vec(0.0, 0.0), 5.0);
    Circle c2(Vec(0.0, 0.0), 3.0);

    EXPECT_TRUE(c1.overlaps(c2));
}

// =========================================
// Rectangle-Rectangle collision test
// =========================================

TEST(RectangleCollisionTest, TouchingRectangles) {
    Rectangle r1(Vec(0.0, 0.0), 10.0, 10.0);
    Rectangle r2(Vec(10.0, 0.0), 10.0, 10.0);
    EXPECT_FALSE(r1.overlaps(r2));
}

TEST(RectangleCollisionTest, OverlappingRectangles) {
    Rectangle r1(Vec(0.0, 0.0), 10.0, 10.0);
    Rectangle r2(Vec(8.0, 0.0), 10.0, 10.0);
    EXPECT_TRUE(r1.overlaps(r2));
}

TEST(RectangleCollisionTest, SeparatedRectangles) {
    Rectangle r1(Vec(0.0, 0.0), 10.0, 10.0);
    Rectangle r2(Vec(20.0, 0.0), 10.0, 10.0);
    EXPECT_FALSE(r1.overlaps(r2));
}

TEST(RectangleCollisionTest, ContainedRectangle) {
    Rectangle r1(Vec(0.0, 0.0), 20.0, 20.0);
    Rectangle r2(Vec(0.0, 0.0), 5.0, 5.0);
    EXPECT_TRUE(r1.overlaps(r2));
}
