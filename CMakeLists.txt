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

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(Qt5_DIR "C:/Qt/5.14.2/mingw73_64/lib/cmake/Qt5")
# previous line vs. set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.14.2\\mingw73_64\\") ??
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}) # Credits to the comment in https://stackoverflow.com/questions/24222057/error-for-compiling-qt-gui-with-cmake-along-with-promoted-widget
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/jir_seg)

add_executable(simple_interpreter main.cpp Statements/AssignmentStatement.cpp Statements/AssignmentStatement.h FileReader.cpp FileReader.h Parser/Parser.cpp Parser/Parser.h Evaluation/ExpressionEvaluator.cpp Evaluation/ExpressionEvaluator.h Interpretation.cpp Interpretation.h Statements/Statement.cpp Statements/Statement.h Collections/Stack.h Collections/BST.h Collections/Heap.h Statements/IfStatement.cpp Statements/IfStatement.h Evaluation/Value.cpp Evaluation/Value.h Evaluation/Operator.h Statements/GotoStatement.cpp Statements/GotoStatement.h Utils/HelperMethods.cpp Utils/HelperMethods.h Utils/Constants.h MainWindow.cpp MainWindow.h mainwindow.ui codeeditor.cpp codeeditor.h highlighter.cpp highlighter.h)
add_executable(test_runner Tests/main.cpp Tests/EvaluationTests.cpp Evaluation/ExpressionEvaluator.cpp Evaluation/ExpressionEvaluator.h Tests/IfStatementTests.cpp Statements/IfStatement.cpp Statements/IfStatement.h Statements/Statement.cpp Statements/Statement.h Parser/Parser.cpp Parser/Parser.h Parser/StatementValidator.cpp Parser/StatementValidator.h Statements/AssignmentStatement.cpp Statements/AssignmentStatement.h Evaluation/Value.cpp Evaluation/Value.h Statements/GotoStatement.h Statements/GotoStatement.cpp Utils/HelperMethods.cpp Utils/HelperMethods.h)

target_link_libraries(test_runner gtest gtest_main)
target_link_libraries(simple_interpreter Qt5::Core Qt5::Widgets Qt5::Gui)