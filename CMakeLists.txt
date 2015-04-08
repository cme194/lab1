project(cme194_lab1 CXX)
cmake_minimum_required(VERSION 2.6.2)
find_package(MPI REQUIRED)

set(CMAKE_BUILD_TYPE Release)
add_definitions("-std=c++1y")
find_package(Boost COMPONENTS mpi serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable(pp ping_pong.cpp)
target_link_libraries(pp ${MPI_LIBRARIES} ${Boost_LIBRARIES})

