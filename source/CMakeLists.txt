file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(GraphViz STATIC
        ${SOURCE_FILES}
)


add_library(libGraph STATIC IMPORTED)
set_property(TARGET libGraph PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/library/libGraph/libGraph.a)

target_link_libraries(GraphViz PRIVATE libGraph)