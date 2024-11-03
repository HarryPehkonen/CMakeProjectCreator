#pragma once
#include "project_question.hpp"
#include <string>
#include <memory>
#include <filesystem>
#include <vector>
#include <map>

class ProjectStrategy {
public:
    virtual ~ProjectStrategy() = default;
    
    // Get questions specific to this project type
    virtual std::vector<ProjectQuestion> getSpecificQuestions() const = 0;
    
    // Create project with answers
    virtual void createCMakeLists(
        const std::filesystem::path& projectPath, 
        const std::string& projectName,
        const std::map<std::string, std::string>& answers) const = 0;
        
    virtual void createProjectStructure(
        const std::filesystem::path& projectPath,
        const std::map<std::string, std::string>& answers) const = 0;
};
