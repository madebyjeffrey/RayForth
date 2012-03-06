
cmake_minimum_required(VERSION 2.8)



project(ray)


# -stdlib=libc++
# -Werror
# -Weffc++ 
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11  -g -Wall -Wextra -Wno-unused-parameter")

include_directories("include")
add_executable(ray src/geometry.cpp src/linear_algebra.cpp src/main.cpp src/lodepng.cpp)
target_link_libraries(ray)


find_package(Boost REQUIRED)

# include_directories(${BOOST_INCLUDE_DIR})
include_directories("/opt/local/include" "/usr/local/include")
target_link_libraries(ray ${BOOST_LIBRARY})

# nein! eigen
# include_directories("/opt/local/include/eigen3/")
# include_directories("/Users/iaefai/.work/eigen/")

add_executable(test tests/linear_algebra.cxx)