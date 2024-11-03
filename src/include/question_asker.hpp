#pragma once
#include "project_question.hpp"
#include <map>
#include <string>

class QuestionAsker {
public:
    static std::map<std::string, std::string> askQuestions(
        const std::vector<ProjectQuestion>& questions);

private:
    static std::string askQuestion(const ProjectQuestion& question);
    static void displayOptions(const std::vector<std::string>& options, 
                             const std::optional<std::string>& default_value);
    static bool isValidOption(const std::string& answer, 
                            const std::vector<std::string>& options);
    static std::string getDefaultStr(const std::optional<std::string>& default_value);
};
