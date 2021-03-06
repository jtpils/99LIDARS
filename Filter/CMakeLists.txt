cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(filter)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(OpenMP)
if(OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(${dbscan})
link_directories(${dbscan})

add_executable(filter filter.cpp dbscan/clusters.cpp dbscan/clusters.h dbscan/dbscan.cpp dbscan/dbscan.h dbscan/kdtree2.cpp dbscan/kdtree2.hpp dbscan/utils.cpp dbscan/utils.h)

include_directories(${include})
link_directories(${include})
target_link_libraries (filter ${PCL_LIBRARIES})

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(filter_truth)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(${dbscan})
link_directories(${dbscan})

add_executable(filter_truth filter_truth.cpp dbscan/clusters.cpp dbscan/clusters.h dbscan/dbscan.cpp dbscan/dbscan.h dbscan/kdtree2.cpp dbscan/kdtree2.hpp dbscan/utils.cpp dbscan/utils.h)

target_link_libraries (filter_truth ${PCL_LIBRARIES})
