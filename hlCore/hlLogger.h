#pragma once


#ifndef LOGGER_H
#define LOGGER_H

#include "Common.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <deque>
#include <optional>


class CORE_API Logger {

public:

    enum class LogLevel {

        Error,
        Warning,
        Info,
        Debug,
        Input,
        Clear,
        Destroy,
        Save,
        Load

    };

    struct LogEntry {

        LogLevel level;
        std::string message;
    };

    Logger();

    ~Logger();

    template <typename T = std::optional<std::string>>

    void Log(LogLevel level, const std::string& message, const T& value = std::nullopt) {
        LogEntry entry;
        entry.level = level;

        if (level == LogLevel::Error || level == LogLevel::Warning) {
            std::ostringstream locationInfo;
            locationInfo << "File: " << __FILE__ << ", Line: " << __LINE__;
            entry.message = locationInfo.str() + " | Description: " + message;
        }
        else {
            entry.message = message;
        }

        if constexpr (std::is_same_v<T, std::optional<std::string>>) {
            if (value.has_value()) {
                entry.message += "| Value: " + *value;
            }
        }
        else if constexpr (std::is_arithmetic_v<T> || std::is_same_v<T, bool>) {
            entry.message += "| Value: " + ConvertToString(value);
        }

        logs.push_back(entry);

        while (logs.size() > maxLogCount) {
            logs.pop_front();
        }

        switch (level) {
        case LogLevel::Error:
            std::cerr << "Error: " << entry.message << std::endl;
            break;
        case LogLevel::Warning:
            std::cerr << "Warning: " << entry.message << std::endl;
            break;
        case LogLevel::Info:
            std::cout << "Info: " << entry.message << std::endl;
            break;
        case LogLevel::Debug:
            std::cout << "Debug: " << entry.message << std::endl;
            break;
        case LogLevel::Input:
            std::cout << "Input: " << entry.message << std::endl;
            break;
        case LogLevel::Clear:
            std::cout << "Clear: " << entry.message << std::endl;
            break;
        case LogLevel::Destroy:
            std::cout << "Destroy: " << entry.message << std::endl;
            break;
        }

        std::ofstream logFile("log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << entry.message << std::endl;
            logFile.close();
        }
    }

    const std::deque<LogEntry>& GetLogs() const {
        return logs;
    }

private:

    std::deque<LogEntry> logs;
    const size_t maxLogCount = 100;

    template <typename U>
    std::string ConvertToString(const U& value) {
        return std::to_string(value);
    }
};


template <>
inline std::string Logger::ConvertToString<std::string>(const std::string& value) {
    return value;
}

#endif