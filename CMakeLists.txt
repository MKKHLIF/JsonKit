cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

project("json_kit")

enable_testing()


find_package(Git QUIET)

if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Option to enable/disable submodule updates
    option(GIT_SUBMODULE "Check submodules during build" ON)

    if (GIT_SUBMODULE)
        # Update submodules recursively
        execute_process(
                COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMODULE_RESULT
        )

        if (NOT GIT_SUBMODULE_RESULT EQUAL 0)
            message(FATAL_ERROR "Error updating submodules: ${GIT_SUBMODULE_RESULT}")
        endif ()
    endif ()
endif ()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/gtest/CMakeLists.txt"
        OR NOT EXISTS "${PROJECT_SOURCE_DIR}/external/utf8/CMakeLists.txt"
        OR NOT EXISTS "${PROJECT_SOURCE_DIR}/external/utils/CMakeLists.txt")
    message(FATAL_ERROR "Missing submodules! Please initialize and update submodules.")
endif ()

add_subdirectory(external/gtest)
add_subdirectory(external/utf8)
add_subdirectory(external/utils)

add_subdirectory("src")
add_subdirectory("tests")
