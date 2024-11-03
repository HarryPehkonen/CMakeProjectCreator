#include "question_asker.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

std::map<std::string, std::string> QuestionAsker::askQuestions(
    const std::vector<ProjectQuestion>& questions) 
{
    std::map<std::string, std::string> answers;
    
    for (const auto& question : questions) {
        std::string answer = askQuestion(question);
        
        // If answer is empty but there's a default, use the default
        if (answer.empty() && question.default_value) {
            answer = *question.default_value;
        }
        
        // Only store non-empty answers
        if (!answer.empty() || question.required) {
            answers[question.id] = answer;
        }
    }
    
    return answers;
}

std::string QuestionAsker::askQuestion(const ProjectQuestion& question) {
    while (true) {
        // Display question and options
        std::cout << "\n" << question.question << "\n";
        
        if (!question.options.empty()) {
            displayOptions(question.options, question.default_value);
        } else if (question.default_value) {
            std::cout << "(Default: " << *question.default_value << ")\n";
        }
        
        // If not required and has default, allow empty input
        std::cout << (!question.required ? "[Press Enter for default] " : "");
        std::cout << "> ";
        
        std::string answer;
        std::getline(std::cin, answer);
        
        // Trim whitespace
        answer.erase(0, answer.find_first_not_of(" \t\n\r\f\v"));
        answer.erase(answer.find_last_not_of(" \t\n\r\f\v") + 1);
        
        // Handle empty input
        if (answer.empty()) {
            if (!question.required || question.default_value) {
                return ""; // Will be replaced with default if it exists
            }
            std::cout << "This question requires an answer.\n";
            continue;
        }
        
        // Validate against options if they exist
        if (!question.options.empty() && !isValidOption(answer, question.options)) {
            std::cout << "Please select a valid option.\n";
            continue;
        }
        
        return answer;
    }
}

void QuestionAsker::displayOptions(
    const std::vector<std::string>& options,
    const std::optional<std::string>& default_value) 
{
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << (i + 1) << ") " << options[i];
        if (default_value && options[i] == *default_value) {
            std::cout << " (Default)";
        }
        std::cout << "\n";
    }
}

bool QuestionAsker::isValidOption(
    const std::string& answer,
    const std::vector<std::string>& options) 
{
    // Check if the answer matches any option exactly
    if (std::find(options.begin(), options.end(), answer) != options.end()) {
        return true;
    }
    
    // Check if the answer is a valid number
    try {
        size_t num = std::stoul(answer);
        return num >= 1 && num <= options.size();
    } catch (...) {
        return false;
    }
}

std::string QuestionAsker::getDefaultStr(const std::optional<std::string>& default_value) {
    return default_value ? " [" + *default_value + "]" : "";
}
