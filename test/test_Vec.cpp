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
#include <sstream>          

#include "Vec.hpp"

// Test: Default constructor initializes vector to (0, 0)
TEST(Vec_TestGroup, DefaultConstructor)
{
    // Create a Vec object using the default constructor
    Vec v;

    // Verify that the components are initialized to zero
    EXPECT_DOUBLE_EQ(v.x(), 0.0); 
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
}

// Test: Parameterized constructor correctly initializes vector components
TEST(Vec_TestGroup, ParameterizedConstructor)
{
    // Create a Vec3 object with specific values
    Vec v(1.0, 2.0);

    // Verify that the components match the provided values
    EXPECT_DOUBLE_EQ(v.x(), 1.0); 
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
}

// Test: Vector addition
TEST(Vec_TestGroup, VectorAddition)
{
    // Create two vectors
    Vec a(1.0, 2.0);
    Vec b(4.0, 5.0);

    // Perform vector addition
    Vec c = a + b;

    // Check that the resulting vector is the correct sum
    EXPECT_DOUBLE_EQ(c.x(), 5.0); 
    EXPECT_DOUBLE_EQ(c.y(), 7.0);    
}

// Test: Vector subtraction
TEST(Vec_TestGroup, VectorSubtraction)
{
    // Create two vectors
    Vec a(1.0, 2.0);
    Vec b(4.0, 5.0);

    // Perform vector subtraction
    Vec c = a - b;

    // Check that the resulting vector is the correct difference
    EXPECT_DOUBLE_EQ(c.x(), -3.0); 
    EXPECT_DOUBLE_EQ(c.y(), -3.0);  
}

// Test: Scalar multiplication
TEST(Vec_TestGroup, ScalarMultiplication)
{
    // Create a vector
    Vec a(1.0f, 2.0f);

    // Multiply the vector by a scalar
    Vec c = a*5.0f;

    // Check that each component is scaled correctly
    EXPECT_DOUBLE_EQ(c.x(), 5.0); 
    EXPECT_DOUBLE_EQ(c.y(), 10.0);   
}

// Test: Magnitude (length) of a vector
TEST(Vec_TestGroup, Magnitude)
{
    // Create a vector
    Vec vec(3.0, 4.0);

    // Compute the magnitude
    double result = vec.magnitude();

    // Verify that the magnitude is correct
    EXPECT_DOUBLE_EQ(result, 5.0);  // Magnitude of (3, 4) should be 5 (3^2 + 4^2 = 25, sqrt(25) = 5)
}

// Test: Normalization of a vector
TEST(Vec_TestGroup, Normalize)
{
    // Create a vector
    Vec vec(3.0, 4.0);

    // Normalize the vector
    Vec result = vec.normalize();

    // Verify that the normalized vector has unit length and correct components
    EXPECT_DOUBLE_EQ(result.x(), 0.6);  // 3 / 5 = 0.6
    EXPECT_DOUBLE_EQ(result.y(), 0.8);  // 4 / 5 = 0.8

    // Verify the magnitude of the normalized vector is 1
    EXPECT_DOUBLE_EQ(result.magnitude(), 1.0);
}
