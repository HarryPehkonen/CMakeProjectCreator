#include "header_only_strategy.hpp"
#include <fstream>

void HeaderOnlyLibraryStrategy::createCMakeLists(
    const std::filesystem::path& projectPath, 
    const std::string& projectName,
    const std::map<std::string, std::string>& answers) const 
{
    std::ofstream cmake(projectPath / "CMakeLists.txt");
    
    // Get C++ standard from answers or default to 17
    const auto& cpp_std = answers.count("cpp_standard") ? 
        answers.at("cpp_standard") : "17";
        
    // Get namespace or use project name as default
    const auto& namespace_name = answers.count("namespace") ? 
        answers.at("namespace") : projectName;
    
    cmake << "cmake_minimum_required(VERSION 3.14)\n\n"
         << "project(" << projectName << " VERSION 1.0)\n\n"
         << "add_library(" << projectName << " INTERFACE)\n"
         << "target_compile_features(" << projectName << " INTERFACE cxx_std_" << cpp_std << ")\n"
         << "target_include_directories(" << projectName << " INTERFACE\n"
         << "    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>\n"
         << "    $<INSTALL_INTERFACE:include>\n"
         << ")\n\n";
         
    // Add header template if namespace was provided
    if (!namespace_name.empty()) {
        createNamespaceHeader(projectPath, namespace_name);
    }
}

void HeaderOnlyLibraryStrategy::createProjectStructure(
    const std::filesystem::path& projectPath,
    [[maybe_unused]] const std::map<std::string, std::string>& answers) const 
{
    std::filesystem::create_directories(projectPath / "include");
    std::filesystem::create_directories(projectPath / "examples");
    std::filesystem::create_directories(projectPath / "tests");
}

void HeaderOnlyLibraryStrategy::createNamespaceHeader(
    const std::filesystem::path& projectPath,
    const std::string& namespace_name) const 
{
    const std::string filename = namespace_name + ".hpp";
    std::ofstream header(projectPath / "include" / filename);
    header << "#pragma once\n\n"
           << "namespace " << namespace_name << " {\n\n"
           << "// Your code here\n\n"
           << "} // namespace " << namespace_name << "\n";
}
