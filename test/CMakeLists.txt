project(Google_Tests)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# adding the Google_Tests_run target
add_executable(libGraphVis_Tests
        ${SOURCE_FILES}
        ../source/GraphViz.cpp
        ../source/Dot.cpp
        ../source/Image.cpp
)

add_library(libGraph STATIC IMPORTED)
set_property(TARGET libGraph PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/library/libGraph/libGraph.a)

target_link_libraries(libGraphVis_Tests libGraph gtest gtest_main)

#
##
#
########
#
##
#

###################
#					#
#    Google Test	#
#					#
###################



include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#
##
#
########
#
##
#