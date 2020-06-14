cmake_minimum_required(VERSION 3.15)
project(oflauncher_stainless)

set(CMAKE_CXX_STANDARD 17)

add_executable(oflauncher_stainless src/main.cpp src/gui/OFSGui.cpp src/gui/OFSGui.h src/net/OFSNet.cpp src/net/OFSNet.h)