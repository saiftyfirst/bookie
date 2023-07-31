cmake_minimum_required(VERSION 3.25)
project(bookie)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                ${CMAKE_BINARY_DIR}/googletest-build
                EXCLUDE_FROM_ALL)


# Set source directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

# Include directories
include_directories(${SRC_DIR})

# Set source files
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

# link main executable
file(GLOB SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/datetime/*.cpp")
file(GLOB INCLUDES "${SRC_DIR}/*.hpp" "${SRC_DIR}/datetime/*.hpp")
add_executable(bookie src/main.cpp ${SOURCES} ${INCLUDES})

# Now simply link against gtest or gtest_main as needed.
# Set test files
file(GLOB TEST_FILES "${TESTS_DIR}/*.cpp")

# Add test executable
add_executable(tests ${TEST_FILES} ${SOURCES} ${INCLUDES})
target_link_libraries(tests gtest_main)
add_test(NAME bookie_tests COMMAND tests)


