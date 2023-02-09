cmake_minimum_required(VERSION 3.21)
project(CLionProjects)

set(CMAKE_CXX_STANDARD 14)

include_directories(A2_SimpleNavigator_v1.0-1/src)
include_directories(A2_SimpleNavigator_v1.0-1/src/helpers)
include_directories(A2_SimpleNavigator_v1.0-1/src/Interface)
include_directories(A2_SimpleNavigator_v1.0-1/src/Tsm)

add_executable(CLionProjects
        helpers/matrix.cc
        helpers/matrix.h
        helpers/s21_queue.cc
        helpers/s21_queue.h
        helpers/s21_stack.cc
        helpers/s21_stack.h
        main.cc
        s21_graph_algorithms.cc
        s21_graph_algorithms.h
        Interface/Interface.cc
        Interface/Interface.h
        s21_graph.cc
        s21_graph.h
        Tsm/TsmAbstract.h
        Tsm/TsmAntAlgorithm.cc
        Tsm/TsmAntAlgorithm.h
        Tsm/TsmBranchAndBound.cc
        Tsm/TsmBranchAndBound.h
        Tsm/TsmBruteForce.cc
        Tsm/TsmBruteForce.h
        )
