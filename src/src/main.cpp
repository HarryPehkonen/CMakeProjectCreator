#include "cmake_project_creator.hpp"
#include "header_only_strategy.hpp"
#include "question_asker.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    try {
        // Create the project creator with a header-only library strategy
        auto creator = CMakeProjectCreator(
            std::make_unique<HeaderOnlyLibraryStrategy>()
        );
        
        std::string projectName;
        std::filesystem::path projectPath;

        // Handle command line arguments if provided
        if (argc >= 3) {
            projectName = argv[1];
            projectPath = argv[2];
        } else {
            // Ask for project name and path
            std::cout << "Project name: ";
            std::getline(std::cin, projectName);
            
            std::cout << "Project path: ";
            std::string pathStr;
            std::getline(std::cin, pathStr);
            projectPath = pathStr;
        }
        
        // Get and ask all questions
        auto questions = creator.getAllQuestions();
        auto answers = QuestionAsker::askQuestions(questions);
        
        // Create the project with the collected answers
        creator.createProject(projectPath, projectName, answers);
        
        std::cout << "\nProject created successfully at: " 
                  << std::filesystem::absolute(projectPath) << "\n";
                  
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
