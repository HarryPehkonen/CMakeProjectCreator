cmake_minimum_required(VERSION 3.14)
project(cmake_project_creator VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define source files
set(SOURCES
    src/src/main.cpp
    src/src/cmake_project_creator.cpp
    src/src/header_only_strategy.cpp
    src/src/question_asker.cpp
)

# Define header files
set(HEADERS
    src/include/cmake_project_creator.hpp
    src/include/project_strategy.hpp
    src/include/project_question.hpp
    src/include/question_asker.hpp
    src/include/header_only_strategy.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

# Enable warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Add testing support
enable_testing()
# TODO: Add tests when they are implemented
