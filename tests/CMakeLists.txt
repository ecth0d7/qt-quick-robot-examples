cmake_minimum_required(VERSION 3.21)
project(qt_examples_tests LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Test)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
set(EXAMPLE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../qt_classroom" CACHE PATH "Directory containing the examples to test")
set(panel "${EXAMPLE_ROOT}/02_robot_panel")
qt_add_executable(robot_panel_test
    robot_panel_test.cpp
    "${panel}/RobotState.h" "${panel}/RobotState.cpp" "${panel}/resources.qrc")
target_include_directories(robot_panel_test PRIVATE "${panel}")
target_link_libraries(robot_panel_test PRIVATE
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::Test)
enable_testing()
add_test(NAME robot_panel COMMAND robot_panel_test)
set_tests_properties(robot_panel PROPERTIES TIMEOUT 30)
