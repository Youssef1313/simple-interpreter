cmake_minimum_required(VERSION 3.13)
project(simple_interpreter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")


add_executable(simple_interpreter main.cpp Statements/AssignmentStatement.cpp Statements/AssignmentStatement.h FileReader.cpp FileReader.h Parser/Parser.cpp Parser/Parser.h Parser/StatementValidator.cpp Parser/StatementValidator.h Parser/StatementType.h Evaluation/ExpressionEvaluator.cpp Evaluation/ExpressionEvaluator.h Interpretation.cpp Interpretation.h Statements/Statement.cpp Statements/Statement.h Collections/Stack.h)

