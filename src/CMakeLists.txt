set(This JsonKit)

file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc")
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")

add_library(${This} STATIC ${SRC_FILES} ${HEADER_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${This} PROPERTY CXX_STANDARD 20)
endif ()

target_include_directories(${This} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${This} PRIVATE Utf8)
target_link_libraries(${This} PRIVATE StringExtensions)
