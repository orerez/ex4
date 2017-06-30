cmake_minimum_required(VERSION 3.7)
project(new_ex4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp  Enigma.h Enigma.cpp Exceptions.h EscapeRoom.c EscapeRoom.h EscapeRoomWrapper.cpp
        EscapeRoomWrapper.h List.cpp List.h ScaryRoom.cpp ScaryRoom.h kidsRoom.h kidsRoom.cpp Company.h Company.cpp Tests.cpp)
add_executable(new_ex4 ${SOURCE_FILES})