cmake_minimum_required(VERSION 3.20)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
add_subdirectory(googletest)

add_executable(test
  test.cpp 
  ../src/products.cpp
  ../src/Cart.cpp
  ../src/FileManager.cpp
  ../src/Inventory.cpp
  ../src/Login.cpp
)

target_link_libraries(test gtest gtest_main)