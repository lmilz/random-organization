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
#include <memory>
#include <cmath>
#include <algorithm>

#include "Shape.hpp"
#include "Vec.hpp"

/**
 * @brief Enumeration of available boundary condition types
 */
enum class BoundaryTypes
{
    Hardwall,  ///< Particles stop at boundary
    Periodic,  ///< Particles wrap around
    Reflective ///< Particles bounce back
};

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
    void apply(Shape& particle, double width, double height) const override {
        Vec pos = getPosition(particle);
        
        double x = std::fmod(pos.x(), width);
        double y = std::fmod(pos.y(), height);
        
        if (x < 0.0) x += width;
        if (y < 0.0) y += height;

        setPosition(particle, Vec(x, y));
    }
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
    void apply(Shape& particle, double width, double height) const override {
        Vec pos = getPosition(particle);
        setPosition(particle, Vec(reflect(pos.x(), width), reflect(pos.y(), height)));
    }

   private:
    /**
     * @brief Reflect one value within the domain [0, max]
     * @param value Reflected value
     * @param max Maximal value
     * @return Reflected value within the domain [0, max]4
     */
    static double reflect(double value, double max)
    {
        if (value < 0.0) return -value;
        if (value > max) return max - (value - max);
        return value;
    }
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
    void apply(Shape& particle, double width, double height) const override {
        Vec pos = getPosition(particle);
        setPosition(particle, Vec(std::clamp(pos.x(), 0.0, width), std::clamp(pos.y(), 0.0, height)));
    }
};

/**
 * @brief Factory for creating boundary conditions
 *
 * Creates boundary instances based on the specified type.
 */
class BoundaryType
{
   public:
    /**
     * @brief Factory method to create boundary conditions
     * @param type The boundary type to create
     * @return A boundary variant
     */
    static std::unique_ptr<Boundary> create(BoundaryTypes type)
    {
        switch (type) {
            case BoundaryTypes::Periodic:
                return std::make_unique<PeriodicBoundary>();
            case BoundaryTypes::Reflective:
                return std::make_unique<ReflectiveBoundary>();
            case BoundaryTypes::Hardwall:
                return std::make_unique<HardwallBoundary>();
        }
    }
};

#endif  // BOUNDARY_H
