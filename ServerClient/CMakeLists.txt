cmake_minimum_required(VERSION 2.8.9)

project(ServerClient)

set(CMAKE_BUILD_TYPE Debug)
set(INSTALL_NAME_DIR ${CMAKE_CURRENT_BINARY_DIR})

#Bring the headers into the project
include_directories(include)
include_directories(${LOGGER_INCLUDE_DIR})

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Sources/*.cpp")

#Generate the static library from the sources
add_library(ServerClient STATIC ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS ServerClient DESTINATION ${INSTALL_NAME_DIR}/lib)
 
