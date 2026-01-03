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
 * @file Boundary.hpp
 * @brief Boundary condition handlers for particle simulation
 *
 * Defines abstract boundary interface and concrete implementations for different boundary behavior
 * (periodic, reflective, hardwall)
 */

#ifndef BOUNDARY_H
#define BOUNDARY_H

// Includes
#include <cmath>

#include "Shape.hpp"
#include "Vec.hpp"

/**
 * @brief Abstract base class for boundary conditions
 *
 * Boundary conditions determine how particles behave when they reach the edge of the area.
 */
class Boundary
{
   public:
    virtual ~Boundary() = default;

    /**
     * @brief Apply boundary condition to a particle
     * @param particle The particle to constrain
     * @param width Area width
     * @param height Area height
     */
    virtual void apply(Shape& particle, double width, double height) const = 0;
};

/**
 * @brief Periodic boundary condition
 *
 * Particles exiting one side reappear on the opposite side.
 * Useful for simulating infinite systems without edge effects.
 */
class PeriodicBoundary : public Boundary
{
   public:
    /**
     * @copydoc Boundary::apply()
     */
    void apply(Shape& particle, double width, double height) const override {}
};

/**
 * @brief Reflective boundary condition
 *
 * Particles bounce back when hitting the boundary, preserving momentum in the perpendicular
 * direction.
 */
class ReflectiveBoundary : public Boundary
{
   public:
    /**
     * @copydoc Boundary::apply()
     */
    void apply(Shape& particle, double width, double height) const override {}
};

/**
 * @brief Hardwall boundary condition
 *
 * Particles are stopped at the boundary edge. Position is clamped to remain within the area.
 */
class HardwallBoundary : public Boundary
{
   public:
    /**
     * @copydoc Boundary::apply()
     */
    void apply(Shape& particle, double width, double height) const override {}
};

#endif  // BOUNDARY_H
