#include "cmake_project_creator.hpp"
#include <fstream>
#include <filesystem>

std::vector<ProjectQuestion> CMakeProjectCreator::getAllQuestions() const {
    auto questions = getCommonQuestions();
    auto specific = m_strategy->getSpecificQuestions();
    questions.insert(questions.end(), specific.begin(), specific.end());
    return questions;
}

void CMakeProjectCreator::createProject(
    const std::filesystem::path& projectPath, 
    const std::string& projectName,
    const std::map<std::string, std::string>& answers) 
{
    if (!std::filesystem::exists(projectPath)) {
        std::filesystem::create_directories(projectPath);
    }

    m_strategy->createProjectStructure(projectPath, answers);
    m_strategy->createCMakeLists(projectPath, projectName, answers);
    createGitignore(projectPath);
    createReadme(projectPath, projectName, answers);
}

std::vector<ProjectQuestion> CMakeProjectCreator::getCommonQuestions() const {
    return {
        {
            "description",
            "Provide a brief description of your project:",
            {},
            false,
            std::nullopt  // No default description
        },
        {
            "license",
            "Choose a license for your project:",
            {"Unlicense", "MIT", "Apache-2.0", "GPL-3.0", "BSD-3-Clause"},
            true,
            "Unlicense"  // Default to Unlicense
        }
    };
}

void CMakeProjectCreator::createReadme(
    const std::filesystem::path& projectPath, 
    const std::string& projectName,
    const std::map<std::string, std::string>& answers) const 
{
    std::ofstream readme(projectPath / "README.md");
    readme << "# " << projectName << "\n\n";
    
    if (answers.count("description")) {
        readme << answers.at("description") << "\n\n";
    }
    
    readme << "## Building\n\n"
           << "```bash\n"
           << "mkdir build && cd build\n"
           << "cmake ..\n"
           << "cmake --build .\n"
           << "```\n";

    // Add license section
    const auto& license = answers.at("license");
    readme << "\n## License\n\n";
    if (license == "Unlicense") {
        readme << "This is free and unencumbered software released into the public domain. "
              << "See the UNLICENSE file for details.\n";
        
        // Create UNLICENSE file
        std::ofstream unlicense(projectPath / "UNLICENSE");
        unlicense << R"(This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
)";
    } else if (license == "MIT") {
        // Create MIT LICENSE file
        std::ofstream mit_license(projectPath / "LICENSE");
        mit_license << "MIT License\n\n"
                   << "Copyright (c) " << std::chrono::system_clock::now().time_since_epoch().count() 
                   << "\n\n"
                   << R"(Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
)";
        readme << "This project is licensed under the MIT License. "
              << "See the LICENSE file for details.\n";
    } else {
        readme << "This project is licensed under the " 
              << license << " License.\n";
        // Note: Other license files could be added here in a similar way
    }
}

void CMakeProjectCreator::createGitignore(const std::filesystem::path& projectPath) const {
    std::ofstream gitignore(projectPath / ".gitignore");
    gitignore << "# Build directories\n"
              << "build/\n"
              << "cmake-build-*/\n\n"
              << "# IDE specific files\n"
              << "*.user\n"
              << ".vscode/\n"
              << ".idea/\n"
              << "*.swp\n"
              << "*.swo\n\n"
              << "# Compiled Object files\n"
              << "*.slo\n"
              << "*.lo\n"
              << "*.o\n"
              << "*.obj\n\n"
              << "# Precompiled Headers\n"
              << "*.gch\n"
              << "*.pch\n\n"
              << "# Compiled Dynamic libraries\n"
              << "*.so\n"
              << "*.dylib\n"
              << "*.dll\n\n"
              << "# Compiled Static libraries\n"
              << "*.lai\n"
              << "*.la\n"
              << "*.a\n"
              << "*.lib\n\n"
              << "# Executables\n"
              << "*.exe\n"
              << "*.out\n"
              << "*.app\n";
}
