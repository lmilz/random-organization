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
#include "SimulationConfig.hpp"

// =========================================
// Circle Data
// =========================================

TEST(CircleArgument, CircleArea)
{
    EXPECT_THROW(CircleData(Vec(0.0, 0.0), -5.0), std::invalid_argument);
}

// =========================================
// Rectangle Data
// =========================================

TEST(RectangleArgument, RectangleWidth)
{
    EXPECT_THROW(RectangleData(Vec(0.0, 0.0), -5.0, 3.0), std::invalid_argument);
}

TEST(RectangleArgument, RectangleHeight)
{
    EXPECT_THROW(RectangleData(Vec(0.0, 0.0), 5.0, -3.0), std::invalid_argument);
}

// =========================================
// Square Data
// =========================================

TEST(SquareArgument, SquareArea)
{
    EXPECT_THROW(SquareData(Vec(0.0, 0.0), -5.0), std::invalid_argument);
}

// =========================================
// Simulation Configuration
// =========================================

TEST(SimConfigArgument, NumParticles)
{
    EXPECT_THROW(SimulationConfiguration().withParticles(0).build(), std::invalid_argument);
}

TEST(SimConfigArgument, MaxIterations)
{
    EXPECT_THROW(SimulationConfiguration().withMaxIterations(0).build(), std::invalid_argument);
}

TEST(SimConfigArgument, AreaWidth)
{
    EXPECT_THROW(SimulationConfiguration().withArea(-3.0, 5.0).build(), std::invalid_argument);
}

TEST(SimConfigArgument, AreaHeight)
{
    EXPECT_THROW(SimulationConfiguration().withArea(3.0, -5.0).build(), std::invalid_argument);
}
