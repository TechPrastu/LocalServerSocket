cmake_minimum_required(VERSION 2.8.9)

project(ServerClient)

set(CMAKE_BUILD_TYPE Debug)

#Bring the headers into the project
include_directories(include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Sources/*.cpp")

#Generate the static library from the sources
add_library(ServerClient STATIC ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS ServerClient DESTINATION /usr/lib)