#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::string StringFromWstring(std::wstring wstring);
std::wstring WstringFromString(std::string string);

std::string ReadTextFile(const fs::path& filePath);