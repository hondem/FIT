cmake_minimum_required(VERSION 3.12)
project(isa_project)

set(CMAKE_CXX_STANDARD 14)

include(FindPCAP.cmake)

add_executable(isa_project main.cpp utils/arg_parser.cpp utils/arg_parser.h utils/exceptions.h utils/network.cpp utils/network.h sniffer.cpp sniffer.h relay.cpp relay.h utils/exceptions.cpp)

target_link_libraries(isa_project
        ${PCAP_LIBRARY}
        pthread
        )