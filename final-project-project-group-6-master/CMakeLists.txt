cmake_minimum_required(VERSION 3.10)
project(Store-Inventory-System)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(testLogin
  src/main.cpp 
  src/Login.cpp
  src/UIManager.cpp
  src/products.cpp
  src/FileManager.cpp
  src/Cart.cpp
  src/Inventory.cpp
)

add_subdirectory(tests)
