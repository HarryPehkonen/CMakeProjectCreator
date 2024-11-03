#pragma once
#include <string>
#include <vector>
#include <optional>

struct ProjectQuestion {
    std::string id;
    std::string question;
    std::vector<std::string> options;  // Empty for free-form text
    bool required;
    std::optional<std::string> default_value; // New: default value if any
};
