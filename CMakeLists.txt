cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp List.h List.cpp Exceptions.h tests.cpp Enigma.cpp Enigma.h EscapeRoom.c EscapeRoom.h
        EscapeRoomWrapper.cpp EscapeRoomWrapper.h)
add_executable(untitled ${SOURCE_FILES})