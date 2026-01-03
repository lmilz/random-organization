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
 * @file Simulation.hpp
 * @brief Main simulation engine for Random organization.
 *
 * This file contains the simulation class that controls the iterative process of overlap resolution
 * through random displacements.
 *
 * The algorithm:
 * 1. Initialize particles randomly in the domain
 * 2. Find all overlapping pairs
 * 3. Displace overlapping particles randomly (limited)
 * 4. Apply boundary conditions
 * 5. Repeat until no overlaps or max iterations reached
 */

#ifndef SIMULATION_H
#define SIMULATION_H

// Includes
#include <memory>
#include <vector>

#include "Boundary.hpp"
#include "Shape.hpp"
#include "ShapeType.hpp"
#include "SimulationConfig.hpp"

/**
 * @brief Main class for particle packing simulation
 *
 * This class manages the particles and executes the iterative algorithm for resolving overlaps.
 *
 * Workflow:
 * 1. Initialization
 * 2. Simulation
 * 3. Evaluation
 */
class Simulation
{
   public:
    /**
     * @brief Constructor
     *
     * Initializes the simulation with the given configuration parameters.
     *
     * @param cfg Configuration parameters (optional)
     */
    explicit Simulation(const SimulationConfig& cfg = SimulationConfig());

    /**
     * @brief Executes the simulation (until convergence or max iterations)
     */
    void run();

    /**
     * @brief Outputs information about all particles
     *
     * Outputs for each particle:
     * - Index
     * - Type (Circle, Squre, Rectangle)
     * - Position (x, y)
     * - Shape information
     */
    void printParticles() const;

   private:
    std::vector<Shape> particles_;                      ///< All particles in the simulation
    SimulationConfig config_;                           ///< Configuration parameters
    std::mt19937 rng_;                                  ///< Random number generator
    std::uniform_real_distribution<double> angleDist_;  ///< Distribution for angles [0, 2pi]
    std::uniform_real_distribution<double>
        distDist_;                        ///< Distribution for distances [0, maxDisplacement]
    uint16_t currentIteration_;           ///< Current iteration
    std::unique_ptr<Boundary> boundary_;  ///< Boundary condition handler

    /**
     * @brief Initializes N random particles
     *
     * Creates the desired number of particles with random positions.
     * The particles are uniformly distributed in the area.
     *
     * @param num Number of particles to create
     *
     * @note Circles are placed randomly and will likely overlap initially.
     */
    void initParticles(uint16_t num);

    /**
     * @brief Finds alls overlapping particle pairs
     *
     * Iterates through all possible particle pairs and checks for overlap.
     *
     * @return Vector of pairs (i, j) where particles i and j overlap
     *
     * @note Complexity O(n**2)
     * @noteEach pair is returned only once (i < j)
     */
    std::vector<std::pair<size_t, size_t>> findOverlaps() const;

    /**
     * @brief Displaces a pair of particles randomly
     *
     * This is the core of the Random Organization algorithm:
     * - Random direction (uniform on unit circle)
     * - Random distance (uniform [0, maxDisplacement])
     * - Application of boundary condition after displacement
     *
     * @param i Index of the first overlapping particle
     * @param j Index of the second overlapping particle
     */
    void randomPush(Shape& particle1, Shape& particle2);

    /**
     * @brief Applies boundary conditions to a particle
     *
     * Depending on configuration, either periodic boundary conditions or hard walls are used.
     *
     * @param particle The particle to which boundary conditions are applied
     */
    void applyBoundaryConditions(Shape& particle);
};

#endif  // SIMULATION_H
