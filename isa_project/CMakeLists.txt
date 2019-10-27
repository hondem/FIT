cmake_minimum_required(VERSION 3.12)
project(isa_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(isa_project main.cpp utils/arg_parser.cpp utils/arg_parser.h utils/exceptions.h utils/exceptions.cpp network.cpp network.h)