#pragma once
#include "project_strategy.hpp"
#include <memory>

class CMakeProjectCreator {
public:
    explicit CMakeProjectCreator(std::unique_ptr<ProjectStrategy> strategy)
        : m_strategy(std::move(strategy)) {}

    // Get all questions (common + strategy-specific)
    std::vector<ProjectQuestion> getAllQuestions() const;

    void createProject(
        const std::filesystem::path& projectPath, 
        const std::string& projectName,
        const std::map<std::string, std::string>& answers);

private:
    std::unique_ptr<ProjectStrategy> m_strategy;

    // Common questions for all project types
    std::vector<ProjectQuestion> getCommonQuestions() const;

    void createReadme(
        const std::filesystem::path& projectPath, 
        const std::string& projectName,
        const std::map<std::string, std::string>& answers) const;
        
    void createGitignore(const std::filesystem::path& projectPath) const;
};
