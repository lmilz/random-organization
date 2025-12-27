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
 * @file Logger.h
 * @brief Thread-safe singleton logger with multiple log levels
 *
 * It supports multiple log levels (DEBUG, INFO, WARNING, ERROR) and writes to both console and file
 * simultaneouosly.
 *
 * Design Pattern: Singleton
 *
 * Usage:
 * @code
 * Logger::getInstance().info("Information");
 * Logger::getInstance().debug("Appname", appname);
 * Logger::getInstance().error("Failure");
 * @endcode
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>

/**
 * @brief Log severity levels
 *
 * Defines the severity of log messages. Messages below the current log level will be filtered out.
 */
enum class LogLevel
{
    DEBUG,    ///< Detailed informagtion for debugging
    INFO,     ///< General informational messages
    WARNING,  ///< Warning messages for potentially problem
    ERROR     ///< Error messages for failures
};

/**
 * @brief Thread-safe singleton logger
 *
 * This class implements a thread-safe logger using the singleton design pattern.
 * It supports multiple log levels and can write to both console and file.
 *
 * Features:
 * - Thread-safe (uses std::mutex)
 * - Multiple log levels (DEBUG, INFO, WARNING, ERROR)
 * - Dual output (console + file)
 * - Automatic timestamps
 * - Variadic templates for flexible message formatting
 */
class Logger
{
   public:
    /**
     * @brief Get singleton instance
     *
     * Returns the single instance of the Logger.
     * Thread-safe in C++11 and later.
     *
     * @returns Reference to the singleton Logger instance
     */
    static Logger& getInstance(const std::string& filename = "output.log")
    {
        static Logger instance(filename);
        return instance;
    }

    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    /**
     * @brief Destructor
     *
     * Writes a footer and closes the log file.
     */
    ~Logger()
    {
        if (logFile.is_open()) {
            log(LogLevel::INFO, "=== Logging finished ===");
            logFile.close();
        }
    }

    /**
     * @brief Log a debug message
     *
     * Variadic template allows logging multiple arguments.
     *
     * @tparam Args Variadic template arguments
     * @param args Arguments to log
     *
     * Example:
     * @code
     * logger.debug("Age: ", 42, " PI: ", 3.13);
     * @endcode
     */
    template <typename... Args>
    void debug(Args&&... args)
    {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::DEBUG, oss.str());
    }

    /**
     * @brief Log a info message
     *
     * Variadic template allows logging multiple arguments.
     *
     * @tparam Args Variadic template arguments
     * @param args Arguments to log
     *
     * Example:
     * @code
     * logger.info("Age: ", 42, " PI: ", 3.13);
     * @endcode
     */
    template <typename... Args>
    void info(Args&&... args)
    {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::INFO, oss.str());
    }

    /**
     * @brief Log a warning message
     *
     * Variadic template allows logging multiple arguments.
     *
     * @tparam Args Variadic template arguments
     * @param args Arguments to log
     *
     * Example:
     * @code
     * logger.debug("Age: ", 42, " PI: ", 3.13);
     * @endcode
     */
    template <typename... Args>
    void warning(Args&&... args)
    {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::WARNING, oss.str());
    }

    /**
     * @brief Log a error message
     *
     * Variadic template allows logging multiple arguments.
     *
     * @tparam Args Variadic template arguments
     * @param args Arguments to log
     *
     * Example:
     * @code
     * logger.debug("Age: ", 42, " PI: ", 3.13);
     * @endcode
     */
    template <typename... Args>
    void error(Args&&... args)
    {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::ERROR, oss.str());
    }

    /**
     * @brief Set the minimum log level
     *
     * Messages below this level will be filtered out.
     *
     * @param level The new minimum log level
     */
    void setLogLevel(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logMutex);
        currentLogLevel = level;
    }

    /**
     * @brief Enable or disable console output
     *
     * @param enable true to enable console output, false to disable
     */
    void setConsoleOutput(bool enable)
    {
        std::lock_guard<std::mutex> lock(logMutex);
        logToConsole = enable;
    }

    /**
     * @brief Write a separator line to the log
     *
     * Useful for visually separating different sections.
     */
    void separator()
    {
        log(LogLevel::INFO, "=======================================================");
    }

    /**
     * @brief Write a blank line to the log
     */
    void blank() { log(LogLevel::INFO, ""); }

   private:
    std::ofstream logFile;     ///< Output file stream for logging
    std::mutex logMutex;       ///< Mutex for thread-safe logging
    LogLevel currentLogLevel;  ///< Current minimum log level
    bool logToConsole;         ///< Whether to also log to console

    /**
     * @brief Private constructor (singleton pattern)
     *
     * Opens the log file and sets default configuration.
     *
     * @param filename Name of the log file
     * @param level Minimum log level to record
     * @param console Whether to also output to console
     */
    Logger(const std::string& filename = "output.log",
           LogLevel level = LogLevel::INFO,
           bool console = true)
        : currentLogLevel(level), logToConsole(console)
    {
        logFile.open(filename, std::ios::out | std::ios::trunc);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file: " + filename);
        }

        // Write header
        log(LogLevel::INFO, "=== Logging started ===");
    }

    /**
     * @brief Get current timestamp as string
     * @return Formatted timestamp string (YY-MM-DD HH:MM:S)
     */
    std::string getCurrentTimestamp() const
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::stringstream timestring;

        timestring << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

        return timestring.str();
    }

    /**
     * @brief Get log level as string
     * @param level The log level
     * @return String representation of the log level
     */
    std::string levelToString(LogLevel level) const
    {
        switch (level) {
            case LogLevel::DEBUG:
                return "[DEBUG]   ";
            case LogLevel::INFO:
                return "[INFO]    ";
            case LogLevel::WARNING:
                return "[WARNING] ";
            case LogLevel::ERROR:
                return "[ERROR]   ";
            default:
                return "[UNKNOWN] ";
        }
    }

    /**
     * @brief Core logging function
     *
     * Writes a log message to file and optionally console.
     * This function is thread-safe.
     *
     * @param level Severity level of the message
     * @param message The message to log
     */
    void log(LogLevel level, const std::string& message)
    {
        if (level < currentLogLevel)
            return;  // Filter out messages below current log level

        std::lock_guard<std::mutex> lock(logMutex);

        std::string logLine = getCurrentTimestamp() + " " + levelToString(level) + " " + message;

        // Write to file
        if (logFile.is_open()) {
            logFile << logLine << std::endl;
            logFile.flush();  // Ensure immediate write
        }

        // Write to console
        if (logToConsole) {
            std::cout << logLine << std::endl;
        }
    }
};

#endif  // LOGGER_H
