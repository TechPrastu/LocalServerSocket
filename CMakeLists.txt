cmake_minimum_required(VERSION 2.8.9)

project(ServerClientTest)

set(CMAKE_BUILD_TYPE Debug)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(simple_server simple_server_main.cpp)
add_executable(simple_client simple_client_main.cpp)

set(PROJECT_LINK_LIBS ServerClient)
set(INSTALL_NAME_DIR ${CMAKE_CURRENT_BINARY_DIR}/install)

link_directories(ServerClient)

include_directories(ServerClient/Include)

set(LOGGER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/Logger)

target_link_libraries(simple_server ${PROJECT_LINK_LIBS})
target_link_libraries(simple_client ${PROJECT_LINK_LIBS})

execute_process(COMMAND git submodule update -f)

find_path(LOGGER_INCLUDE_DIR ...)

if((NOT LOGGER_INCLUDE_DIR) OR (NOT EXISTS ${LOGGER_INCLUDE_DIR}))
    # we couldn't find the header files for Logger or they don't exist
    message("Unable to find Logger")

    # we have a submodule setup for Logger, assume it is under external/Logger now we need to clone this submodule
    execute_process(COMMAND git submodule update --init -- external/Logger WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    # also install it
    install(DIRECTORY ${LOGGER_INCLUDE_DIR}/include DESTINATION ${INSTALL_NAME_DIR}/include)

    # for convenience setup a target
    add_library(Logger INTERFACE)
    target_include_directories(Logger INTERFACE
                               $<BUILD_INTERFACE:${LOGGER_INCLUDE_DIR}>
                               $<INSTALL_INTERFACE:${INSTALL_NAME_DIR}>)

    # need to export target as well
    #install(TARGETS Logger EXPORT my_export_set DESTINATION ${INSTALL_NAME_DIR})
else()
    include_directories(${LOGGER_INCLUDE_DIR})
endif()

add_subdirectory(ServerClient)
