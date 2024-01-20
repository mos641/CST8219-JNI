cmake_minimum_required(VERSION 3.1)
project(MyCPPLibrary)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")

add_library(MyCPPLibrary SHARED JavaMenu.cpp)

target_include_directories(MyCPPLibrary PRIVATE 
	"D:\\Program Files\\Java\\jdk-16.0.2\\include"
	"D:\\Program Files\\Java\\jdk-16.0.2\\include\\win32")
