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
 * @file SimulationConfig.hpp
 */

#ifndef SIMULATIONCONFIG_H
#define SIMULATIONCONFIG_H

// Includes
#include <random>

#include "ShapeType.hpp"

/**
 * @brief Configuration parameters for simulaton
 *
 * This structure contains all parameters that control the simulation behavior.
 * All parameters have sensible default values.
 */
struct SimulationConfig
{
    ShapeTypes type;         ///< Type of particle (circle, rectangle, square)
    uint16_t num_particles;  ///< Number of particles
    double area_width;       ///< Width of the simulation domain
    double area_height;      ///< Height of the simulation domain
    double max_displacement;  ///< Maximum displacement
    uint16_t max_iterations;  ///< Maximum number of iterations
    bool periodic_boundary;   ///< Periodic boundary conditions
    uint32_t seed;           ///< Seed for random number generator

    SimulationConfig()
        : type(ShapeTypes::Circle)
        , num_particles(10)
        , area_width(100.0)
        , area_height(100.0)
        , max_displacement(1.0)
        , max_iterations(10000)
        , periodic_boundary(true)
        , seed(std::random_device{}())
    {
    }
};

class SimulationConfiguration
{
    SimulationConfig config_;

   public:
    SimulationConfiguration& withParticles(uint16_t count)
    {
        config_.num_particles = count;
        return *this;
    }

    SimulationConfiguration& withArea(double width, double height)
    {
        config_.area_width = width;
        config_.area_height = height;
        return *this;
    }

    SimulationConfiguration& withMaxDisplacement(double displacement)
    {
        config_.max_displacement = displacement;
        return *this;
    }

    SimulationConfiguration& withShapeType(ShapeTypes type)
    {
        config_.type = type;
        return *this;
    }

    SimulationConfiguration& withPeriodicBoundary(bool periodic = true)
    {
        config_.periodic_boundary = periodic;
        return *this;
    }

    SimulationConfiguration& withMaxIterations(uint16_t iterations)
    {
        config_.max_iterations = iterations;
        return *this;
    }

    SimulationConfiguration& withSeed(uint32_t seed)
    {
        config_.seed = seed;
        return *this;
    }

    SimulationConfig build() const
    {
        validate();
        return config_;
    }

   private:
    void validate() const
    {
        if (config_.num_particles == 0) {
            throw std::invalid_argument("Need at least one particle");
        }
        if (config_.area_width <= 0 || config_.area_height <= 0) {
            throw std::invalid_argument("Area must be positive");
        }
        if (config_.max_iterations == 0) {
            throw std::invalid_argument("Need at least one iteration");
        }
    }
};

#endif  // SIMULATIONCONFIG_H
