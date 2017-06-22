cmake_minimum_required(VERSION 3.7)
project(GenericList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp EscapeRoomWrapper.cpp EscapeRoomWrapper.h EscapeRoomWrapper.h EscapeRoom.h EscapeRoom.c Enigma.h Enigma.cpp Exceptions.h)
add_executable(GenericList ${SOURCE_FILES})