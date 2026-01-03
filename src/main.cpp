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
 * @file main.cpp
 * @brief Demostration program for simulation
 *
 * This progra:wm demostrates various scenarios of of random organization.
 *
 * Usage:
 * @code
 * ./simulation         # All scenarios
 * ./simulation circles # Only circles
 * @endcode
 */

// Includes
#include <string>

#include "Logger.hpp"
#include "ShapeType.hpp"
#include "Boundary.hpp"
#include "Simulation.hpp"
#include "SimulationConfig.hpp"

/**
 * @brief Demostrates circle packing with low density
 */
static void runCirclesSimulation()
{
    auto& logger = Logger::getInstance();
    logger.separator();
    logger.info("=== Circle Packing Simulation ===");
    logger.separator();
    logger.blank();

    auto config = SimulationConfiguration()
                      .withShapeType(ShapeTypes::Circle)
                      .withParticles(50)
                      .withArea(50, 50)
                      .withMaxDisplacement(0.5)
                      .withMaxIterations(5000)
                      .withBoundaryType(BoundaryTypes::Hardwall)
                      .build();

    Simulation sim(config);

    sim.run();
    sim.printParticles();
}

/**
 * @brief Demostrates circle packing with low density
 */
static void runRectanglesSimulation()
{
    auto& logger = Logger::getInstance();
    logger.separator();
    logger.info("=== Rectangle Packing Simulation ===");
    logger.separator();
    logger.blank();

    auto config = SimulationConfiguration()
                      .withShapeType(ShapeTypes::Rectangle)
                      .withParticles(50)
                      .withArea(50, 50)
                      .withMaxDisplacement(0.5)
                      .withMaxIterations(5000)
                      .withPeriodicBoundary(true)
                      .build();

    Simulation sim(config);

    sim.run();
}

/**
 * @brief Demostrates circle packing with low density
 */
static void runSquaresSimulation()
{
    auto& logger = Logger::getInstance();
    logger.separator();
    logger.info("=== Square Packing Simulation ===");
    logger.separator();
    logger.blank();

    auto config = SimulationConfiguration()
                      .withShapeType(ShapeTypes::Square)
                      .withParticles(50)
                      .withArea(50, 50)
                      .withMaxDisplacement(0.5)
                      .withMaxIterations(5000)
                      .withPeriodicBoundary(true)
                      .build();

    Simulation sim(config);

    sim.run();
}

int main(int argc, char* argv[])
{
    std::string const log_file = (argc > 2) ? argv[2] : "output.log";
    auto& logger = Logger::getInstance(log_file);

    logger.separator();
    logger.info("Random Organization Simulation");
    logger.separator();
    logger.blank();

    if (argc > 1) {
        std::string const mode(argv[1]);

        if (mode == "circles") {
            runCirclesSimulation();
        }
        else if (mode == "rectangles") {
            runRectanglesSimulation();
        }
        else if (mode == "squares") {
            runSquaresSimulation();
        }
        else {
            logger.error("Unknown mode: ", mode);
            logger.info("Available modes: circles, rectangles and squares");
            return 1;
        }
    }
    else {
        runCirclesSimulation();
    }

    logger.blank();
    logger.separator();
    logger.info("All simulations completed. Results saved to ", log_file);
    logger.separator();

    return 0;
}
