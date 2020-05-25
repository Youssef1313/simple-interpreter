cmake_minimum_required(VERSION 3.13)
project(simple_interpreter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif ()


add_subdirectory(lib/gtest)
include_directories(lib/gtest/googletest/include)
include_directories(lib/gtest/googlemock/include)

add_executable(simple_interpreter main.cpp Statements/AssignmentStatement.cpp Statements/AssignmentStatement.h FileReader.cpp FileReader.h Parser/Parser.cpp Parser/Parser.h Parser/StatementValidator.cpp Parser/StatementValidator.h Parser/StatementType.h Evaluation/ExpressionEvaluator.cpp Evaluation/ExpressionEvaluator.h Interpretation.cpp Interpretation.h Statements/Statement.cpp Statements/Statement.h Collections/Stack.h Collections/BST.h Collections/Heap.h Statements/IfStatement.cpp Statements/IfStatement.h Evaluation/Value.cpp Evaluation/Value.h Evaluation/Operator.h SortVariables.h)
add_executable(test_runner Tests/main.cpp Tests/EvaluationTests.cpp Evaluation/ExpressionEvaluator.cpp Evaluation/ExpressionEvaluator.h Tests/IfStatementTests.cpp Statements/IfStatement.cpp Statements/IfStatement.h Statements/Statement.cpp Statements/Statement.h Parser/Parser.cpp Parser/Parser.h Parser/StatementValidator.cpp Parser/StatementValidator.h Statements/AssignmentStatement.cpp Statements/AssignmentStatement.h Evaluation/Value.cpp Evaluation/Value.h)

target_link_libraries(test_runner gtest gtest_main)
