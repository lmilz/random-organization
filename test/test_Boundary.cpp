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

#include "Boundary.hpp"
#include "ShapeType.hpp"

// =========================================
// PeriodicBoundary Tests
// =========================================

TEST(PeriodicBoundaryTest, ParticleInsideBounds)
{
    PeriodicBoundary boundary;
    Shape particle = CircleData(Vec(5.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(PeriodicBoundaryTest, ParticleExitsRight)
{
    PeriodicBoundary boundary;
    Shape particle = CircleData(Vec(12.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 2.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(PeriodicBoundaryTest, ParticleExitsLeft)
{
    PeriodicBoundary boundary;
    Shape particle = CircleData(Vec(-3.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 7.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(PeriodicBoundaryTest, ParticleExitsTop)
{
    PeriodicBoundary boundary;
    Shape particle = CircleData(Vec(5.0, 15.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(PeriodicBoundaryTest, ParticleExitsBottom)
{
    PeriodicBoundary boundary;
    Shape particle = CircleData(Vec(5.0, -2.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 8.0);
}

TEST(PeriodicBoundaryTest, ParticleExitsCorner)
{
    PeriodicBoundary boundary;
    Shape particle = CircleData(Vec(12.0, -3.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 2.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 7.0);
}

TEST(PeriodicBoundaryTest, ParticleExactlyOnBoundary)
{
    PeriodicBoundary boundary;
    Shape particle = CircleData(Vec(10.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 0.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

// =========================================
// ReflectiveBoundary Tests
// =========================================

TEST(ReflectiveBoundaryTest, ParticleInsideBounds)
{
    ReflectiveBoundary boundary;
    Shape particle = CircleData(Vec(5.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(ReflectiveBoundaryTest, ParticleExitsRight)
{
    ReflectiveBoundary boundary;
    Shape particle = CircleData(Vec(12.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 8.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(ReflectiveBoundaryTest, ParticleExitsLeft)
{
    ReflectiveBoundary boundary;
    Shape particle = CircleData(Vec(-3.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 3.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(ReflectiveBoundaryTest, ParticleExitsTop)
{
    ReflectiveBoundary boundary;
    Shape particle = CircleData(Vec(5.0, 14.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 6.0);
}

TEST(ReflectiveBoundaryTest, ParticleExitsBottom)
{
    ReflectiveBoundary boundary;
    Shape particle = CircleData(Vec(5.0, -4.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 4.0);
}

TEST(ReflectiveBoundaryTest, ParticleExitsCorner)
{
    ReflectiveBoundary boundary;
    Shape particle = CircleData(Vec(12.0, -2.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 8.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 2.0);
}

// =========================================
// HardwallBoundary Tests
// =========================================

TEST(HardwallBoundaryTest, ParticleInsideBounds)
{
    HardwallBoundary boundary;
    Shape particle = CircleData(Vec(5.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(HardwallBoundaryTest, ParticleExitsRight)
{
    HardwallBoundary boundary;
    Shape particle = CircleData(Vec(12.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 10.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(HardwallBoundaryTest, ParticleExitsLeft)
{
    HardwallBoundary boundary;
    Shape particle = CircleData(Vec(-3.0, 5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 0.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 5.0);
}

TEST(HardwallBoundaryTest, ParticleExitsTop)
{
    HardwallBoundary boundary;
    Shape particle = CircleData(Vec(5.0, 15.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 10.0);
}

TEST(HardwallBoundaryTest, ParticleExitsBottom)
{
    HardwallBoundary boundary;
    Shape particle = CircleData(Vec(5.0, -5.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 5.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 0.0);
}

TEST(HardwallBoundaryTest, ParticleExitsCorner)
{
    HardwallBoundary boundary;
    Shape particle = CircleData(Vec(15.0, -3.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 10.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 0.0);
}

TEST(HardwallBoundaryTest, ParticleAtOrigin)
{
    HardwallBoundary boundary;
    Shape particle = CircleData(Vec(0.0, 0.0), 1.0);

    boundary.apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 0.0);
    EXPECT_DOUBLE_EQ(getPosition(particle).y(), 0.0);
}

// =========================================
// Polymorphism Tests
// =========================================

TEST(BoundaryPolymorphism, ApplyViaBasePointer)
{
    std::unique_ptr<Boundary> boundary = std::make_unique<HardwallBoundary>();
    Shape particle = CircleData(Vec(15.0, 5.0), 1.0);

    boundary->apply(particle, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(getPosition(particle).x(), 10.0);
}
