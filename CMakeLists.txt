cmake_minimum_required(VERSION 3.26.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(NNF) 
add_library(NNF src/tensor.cpp src/loss.cpp)

target_include_directories(NNF PUBLIC $(PROJECT_SOURCE_DIR)include)

include(FetchContent)

FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tensorTest tests/tensor_test.cpp)
add_executable(lossTest tests/loss_test.cpp)

target_link_libraries(tensorTest GTest::gtest_main)
target_link_libraries(tensorTest NNF)
target_include_directories(tensorTest PUBLIC $(PROJECT_SOURCE_DIR)include)

target_link_libraries(lossTest GTest::gtest_main)
target_link_libraries(lossTest NNF)
target_include_directories(lossTest PUBLIC $(PROJECT_SOURCE_DIR)include)

include(GoogleTest)
gtest_discover_tests(tensorTest lossTest)
