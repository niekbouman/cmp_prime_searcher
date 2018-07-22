cmake_minimum_required (VERSION 2.8)

project (searcher)

set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++  -Weverything  -pedantic -Wno-sign-conversion -Wno-sign-compare -Wno-c++98-compat -Wno-range-loop-analysis -Wno-shorten-64-to-32 -Wno-padded -Wno-comma -Wno-conversion -Wno-weak-vtables")

# for production code: remove debugging stuff:
add_definitions(-DNDEBUG)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
find_package(GMP REQUIRED)
find_package(FLINT REQUIRED)

include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/include" "${FLINT_INCLUDE_DIR}" "${GMP_INCLUDES}")
add_executable(searcher searcher.cpp congruences.cpp related.cpp)
target_link_libraries (searcher ${FLINT_LIBRARIES})

