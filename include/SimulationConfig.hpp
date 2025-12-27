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
#include "ShapeType.hpp"

/**
 * @brief Configuration parameters for simulaton
 *
 * This structure contains all parameters that control the simulation behavior.
 * All parameters have sensible default values.
 */
struct SimulationConfig {
    ShapeTypes type;         ///< Type of particle (circle, rectangle, square)
    uint16_t numParticles;   ///< Number of particles
    double areaWidth;        ///< Width of the simulation domain
    double areaHeight;       ///< Height of the simulation domain
    double maxDisplacement;  ///< Maximum displacement
    uint16_t maxIterations;  ///< Maximum number of iterations
    bool periodicBoundary;   ///< Periodic boundary conditions
    uint32_t seed;           ///< Seed for random number generator

    SimulationConfig()
        : type(ShapeTypes::Circle),
          numParticles(10),
          areaWidth(100.0),
          areaHeight(100.0),
          maxDisplacement(1.0),
          maxIterations(10000),
          periodicBoundary(true),
          seed(std::random_device{}())
    {
    }
};

class SimulationConfiguration
{
    SimulationConfig config;

   public:
    SimulationConfiguration& withParticles(uint16_t count)
    {
        config.numParticles = count;
        return *this;
    }

    SimulationConfiguration& withArea(double width, double height)
    {
        config.areaWidth = width;
        config.areaHeight = height;
        return *this;
    }

    SimulationConfiguration& withMaxDisplacement(double displacement)
    {
        config.maxDisplacement = displacement;
        return *this;
    }

    SimulationConfiguration& withShapeType(ShapeTypes type)
    {
        config.type = type;
        return *this;
    }

    SimulationConfiguration& withPeriodicBoundary(bool periodic = true)
    {
        config.periodicBoundary = periodic;
        return *this;
    }

    SimulationConfiguration& withMaxIterations(uint16_t iterations)
    {
        config.maxIterations = iterations;
        return *this;
    }

    SimulationConfiguration& withSeed(uint32_t seed)
    {
        config.seed = seed;
        return *this;
    }

    SimulationConfig build() const
    {
        validate();
        return config;
    }

   private:
    void validate() const
    {
        if (config.numParticles == 0)
            throw std::invalid_argument("Need at least one particle");
        if (config.areaWidth <= 0 || config.areaHeight <= 0)
            throw std::invalid_argument("Area must be positive");
        if (config.maxIterations == 0)
            throw std::invalid_argument("Need at least one iteration");
    }
};

#endif  // SIMULATIONCONFIG_H
