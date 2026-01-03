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

#include "Simulation.hpp"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numbers>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "Logger.hpp"
#include "Shape.hpp"
#include "ShapeType.hpp"
#include "SimulationConfig.hpp"
#include "Vec.hpp"

Simulation::Simulation(const SimulationConfig& cfg)
    : config(cfg)
    , rng(cfg.seed)
    , angleDist(0.0, 2.0 * std::numbers::pi)
    , distDist(0, cfg.maxDisplacement)
    , currentIteration(0)
{
    initParticles(cfg.numParticles);
}

void Simulation::Run()
{
    currentIteration = 0;
    auto& logger = Logger::getInstance();

    logger.info("Starting simulation with ", particles.size(), " particles");
    logger.info("Area: ", config.areaWidth, "x", config.areaHeight);
    logger.blank();

    // Main loop
    while (currentIteration < config.maxIterations) {
        auto overlaps = findOverlaps();
        logger.info("Iteration ", currentIteration, ": ", overlaps.size(), " overlaps");

        if (overlaps.empty()) {
            break;
        }

        for (const auto& [i, j] : overlaps) {
            randomPush(particles[i], particles[j]);
        }

        currentIteration++;
    }

    auto final_overlaps = findOverlaps();
    logger.blank();
    logger.info("Simulation finished!");
    logger.info("Total iterations: ", currentIteration);
    if (final_overlaps.empty()) {
        logger.info("SUCCESS: No overlaps remaining!");
    }
    else {
        logger.info("System could not resolve all overlaps.");
        logger.info("Final overlaps: ", final_overlaps.size());
    }
}

void Simulation::printParticles() const
{
    auto& logger = Logger::getInstance();
    logger.blank();
    logger.info("Particle position:");
    for (size_t i = 0; i < particles.size(); i++) {
        Vec const pos = getPosition(particles[i]);
        std::string const type_name = getTypeName(particles[i]);
        logger.info(i, ": ", type_name, " at (", pos.X(), ", ", pos.Y(), ")");
    }
}

void Simulation::initParticles(uint16_t num)
{
    std::uniform_real_distribution<double> x_dist(0.0, config.areaWidth);
    std::uniform_real_distribution<double> y_dist(0.0, config.areaHeight);

    particles.reserve(num);
    for (uint16_t index = 0; index < num; index++) {
        Vec const pos(x_dist(rng), y_dist(rng));
        particles.push_back(ShapeType::create(config.type, pos));
    }
}

std::vector<std::pair<size_t, size_t>> Simulation::findOverlaps() const
{
    std::vector<std::pair<size_t, size_t>> overlap_pairs;

    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i + 1; j < particles.size(); j++) {
            if (overlaps(particles[i], particles[j])) {
                overlap_pairs.emplace_back(i, j);
            }
        }
    }

    return overlap_pairs;
}

void Simulation::randomPush(Shape& particle1, Shape& particle2)
{
    // Random direction
    double const angle = angleDist(rng);
    Vec const direction(std::cos(angle), std::sin(angle));

    // Random distance
    double const distance = distDist(rng);

    Vec const displacement = direction * distance;
    move(particle1, displacement);
    move(particle2, displacement * (-1.0));
}
