cmake_minimum_required(VERSION 3.14)
project(GeoApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets Sql Test)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/app.cpp
    src/main_window.cpp
    src/db_manager.cpp
    src/api_manager.cpp
)

set(HEADERS
    include/app.h
    include/main_window.h
    include/db_manager.h
    include/api_manager.h
)

set(TEST_SOURCES
    test/db_test.cpp
    test/api_test.cpp
)

add_executable(GeoApp ${SOURCES} ${HEADERS})

add_executable(TestDB test/db_test.cpp src/db_manager.cpp include/db_manager.h)
add_executable(TestAPI test/api_test.cpp src/api_manager.cpp include/api_manager.h)
add_executable(TestUI test/ui_test.cpp src/main_window.cpp include/main_window.h)

target_link_libraries(GeoApp
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
)

target_link_libraries(TestDB
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Test
)

target_link_libraries(TestAPI
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Test
)

target_link_libraries(TestUI
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Test
)


set_target_properties(GeoApp PROPERTIES AUTOMOC TRUE)

enable_testing()

add_test(NAME TestAPI COMMAND TestAPI)
add_test(NAME TestDB COMMAND TestDB)
add_test(NAME TestUI COMMAND TestUI)

set_tests_properties(TestAPI PROPERTIES LABELS "api")
set_tests_properties(TestDB PROPERTIES LABELS "db")
set_tests_properties(TestUI PROPERTIES LABELS "ui")
