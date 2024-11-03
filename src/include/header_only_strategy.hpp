#pragma once
#include "project_strategy.hpp"
#include <fstream>

class HeaderOnlyLibraryStrategy : public ProjectStrategy {
public:
    std::vector<ProjectQuestion> getSpecificQuestions() const override {
        return {
            {
                "cpp_standard",
                "Which C++ standard would you like to use?",
                {"11", "14", "17", "20", "23"},
                true,
                "17"  // Default to C++17 as it's widely supported
            },
            {
                "namespace",
                "What NAMESPACE would you like to use for your library?",
                {},  // Empty options means free-form text
                false,
                std::nullopt  // No default namespace, will use project name if empty
            }
        };
    }

    void createCMakeLists(
        const std::filesystem::path& projectPath, 
        const std::string& projectName,
        const std::map<std::string, std::string>& answers) const override;

    void createProjectStructure(
        const std::filesystem::path& projectPath,
        [[maybe_unused]] const std::map<std::string, std::string>& answers) const override;

private:
    void createNamespaceHeader(
        const std::filesystem::path& projectPath,
        const std::string& namespace_name) const;
};
