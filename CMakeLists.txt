cmake_minimum_required(VERSION 2.8.9)

project( ServerClientTest )

set(CMAKE_BUILD_TYPE Debug)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(ServerClient)

# add the executable
add_executable(simple_server simple_server_main.cpp)
add_executable(simple_client simple_client_main.cpp)

set ( PROJECT_LINK_LIBS ServerClient )
link_directories( ServerClient )

include_directories(ServerClient/Include)

target_link_libraries(simple_server ${PROJECT_LINK_LIBS})
target_link_libraries(simple_client ${PROJECT_LINK_LIBS})
