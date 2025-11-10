#pragma once
#include <string>
#include <unordered_map>
#include <optional>
#include <format>

enum class ModErrorStep {
	Unknown,
	Collecting,
    Resolving,
    Loading
};

enum class ModErrorType {
	Unknown,
    IOError,
    ParseError,
    CircularDependency,
    WrongDependencyVersion,
    MissingDependency,
    UnhandledException
};

struct ModError {
    ModErrorStep Step;
    ModErrorType Type;
    std::optional<std::string> UUID = std::nullopt;
    std::string Message;
    std::unordered_map<std::string, std::string> Data = {};

    std::string getFormattedMessage() const {
        std::string message = Message;
        size_t off = 0;
        for (const auto& [key, value] : Data) {
            auto pos = message.find(key, off);
            if (pos == std::string::npos)
                continue;
            off = pos + key.length();
            message.replace(pos, key.length(), value);
        }
        return message;
    }

    std::string toString() const {
        std::string stepStr;
        switch (Step) {
            case ModErrorStep::Unknown: 
                stepStr = "Unknown"; 
                break;
            case ModErrorStep::Collecting: 
                stepStr = "Collecting"; 
                break;
            case ModErrorStep::Resolving:
                stepStr = "Resolving"; 
                break;
            default: 
                stepStr = "N/A"; 
                break;
        }

        std::string typeStr;
        switch (Type) {
            case ModErrorType::Unknown: 
                typeStr = "Unknown"; 
                break;
            case ModErrorType::IOError:
                typeStr = "IOError"; 
                break;
            case ModErrorType::ParseError:
                typeStr = "ParseError"; 
                break;
            case ModErrorType::CircularDependency:
                typeStr = "CircularDependency"; 
                break;
            case ModErrorType::WrongDependencyVersion:
                typeStr = "WrongDependencyVersion"; 
                break;
            case ModErrorType::MissingDependency:
                typeStr = "MissingDependency"; 
                break;
            default: 
                typeStr = "N/A"; 
                break;
        }

        std::string message = std::format("ModError(Step: {}, Type: {}, UUID: {})", 
            stepStr,
            typeStr,
            UUID.value_or("N/A")
        );
        message += "\n  " + getFormattedMessage();
        return message;
    }
};