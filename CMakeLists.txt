cmake_minimum_required(VERSION 3.24)
project(testsaperaaaa)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers /usr/include D:/SFML-2.5.1/include)

add_executable(testsaperaaaa main.cpp Cell.cpp Cell.h MineCell.cpp MineCell.h NumberCell.cpp NumberCell.h Board.cpp Board.h Game.cpp Game.h)
